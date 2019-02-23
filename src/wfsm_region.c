#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_region.h"
#include "wfsm_transition.h"
#include "wfsm_state.h"

/* Begin class implementation. */
#include "wfsm_region_class.h"
#include <wondermacros/objects/x/class_start.h>
#include <wondermacros/array/dynamic_stack.h>


CONSTRUCT(wfsm_region) /* self */
{
    self->states = NULL;
    W_DEQUE_INIT(self->events, WFSM_EVENT_QUEUE_SIZE);

    self->start_state = self->current_state = NULL;
    if (!self->name)
        self->name = "default";
    self->name = strdup(self->name);
}

FINALIZE(wfsm_region) /* self */
{
    W_DYNAMIC_ARRAY_FOR_EACH(const struct wfsm_state*, state, self->states)
        W_CALL_VOID(W_OBJECT_AS(state,wfsm_state),free);

    W_DYNAMIC_ARRAY_FREE(self->states);

    W_DEQUE_FREE(self->events);
    free(self->name);
}

METHOD(wfsm_region,public,int,add_state,
    (const struct wfsm_state* state))
{
    W_DYNAMIC_ARRAY_PUSH(self->states, state);

    if (state->flags & WFSM_STATE_INITIAL) {
        if (self->start_state) {
            printf("ERROR: Multiple initial states\n");
            return 1;
        } else
            self->start_state = state;
    }

    return 0;
}

METHOD(wfsm_region,public,int,add_transition,
    (const struct wfsm_transition* transition))
{
    return W_CALL(W_OBJECT_AS(transition->start,wfsm_state),add_transition)(transition);
}

METHOD(wfsm_region,public,int,set_start,
    (struct wfsm_state* state))
{
    if (self->start_state) {
        printf("ERROR: Start state already set\n");
        return 1;
    } else
        self->start_state = state;

    return 0;
}


static inline void
exit_superstates_until_common(struct wfsm_region__private* self, const struct wfsm_state* target)
{
    W_CALL_VOID(W_OBJECT_AS(self->current_state,wfsm_state),exit);

    if (self->current_state == target)
        return;

    if (self->current_state->super) {
        self->current_state = self->current_state->super;
        exit_superstates_until_common(self, target);
    }
}

static inline void
enter_superstates_and_state(struct wfsm_region__private* self, const struct wfsm_state* target)
{
    const struct wfsm_state** superstates = NULL;
    const struct wfsm_state* state = target;
    while (state) {
        W_DYNAMIC_STACK_PUSH(superstates, state);
        state = state->super;
    }

    while (!W_DYNAMIC_STACK_IS_EMPTY(superstates)) {
        state = W_DYNAMIC_STACK_POP(superstates);
        W_CALL_VOID(W_OBJECT_AS(state,wfsm_state),enter);
        self->current_state = state;
        int transitions;
        do {
            transitions = 0;
            if (self->current_state->flags & WFSM_STATE_FINAL) {
                exit_superstates_until_common(self, NULL);
                W_CALL(W_OBJECT_AS(self->owner,wfsm),stop_by_final)(W_OBJECT_AS(self,wfsm_region),self->current_state);
            }
            if (self->current_state->auto_transition && 
                (!self->current_state->auto_transition->guard_cb || 
                 self->current_state->auto_transition->guard_cb(W_OBJECT_AS(self->current_state->auto_transition,wfsm_transition), NULL))) {
                W_CALL(self,on_transition)(self->current_state->auto_transition, NULL);
                transitions = 1;
            }
        } while (transitions);
    }

    W_DYNAMIC_STACK_FREE(superstates);
}

METHOD(wfsm_region,public,void,on_transition,
    (const struct wfsm_transition* transition, struct wfsm_event* event))
{
    /* Exit superstates until we are at the common level. */
    if (!(transition->flags & WFSM_TRANSITION_INTERNAL)) {
        exit_superstates_until_common(self, transition->target);
    }

    /* Run action of the transition if any. */
    if (transition->action_cb)
        transition->action_cb(W_OBJECT_AS(transition,wfsm_transition), event);

    /* Enter all superstates of transition->target if we are not there yet. */
    if (!(transition->flags & WFSM_TRANSITION_INTERNAL)) {
        enter_superstates_and_state(self, transition->target);
    }
}

METHOD(wfsm_region,public,int,start)
{
    if (! self->start_state)
        return 1;

    enter_superstates_and_state(self, self->start_state);

    return 0;
}

METHOD(wfsm_region,public,void,stop)
{
    // FIXME: todo
}

METHOD(wfsm_region,public,int,pop_queue)
{
    if (W_DEQUE_IS_EMPTY(self->events))
        return 0;

    struct wfsm_event event;
    W_DEQUE_POP_FRONT(self->events, event);

    printf(" Pop: %u\n", event.event);
    W_CALL(W_OBJECT_AS(self->current_state,wfsm_state),on_event)(&event);
    return 1;
}

METHOD(wfsm_region,public,int,push_event,
    (WFSM_EVENT_TYPE event, void* data))
{
    struct wfsm_event e;
    e.event = event;
    e.region = (void*) self;
    e.data = data;

    int is_full;
    W_DEQUE_PUSH_BACK(is_full, self->events, e);
    if (is_full)
        return 1;
    else
        printf(" push event: %u\n", event);
    return 0;
}

#include <wondermacros/objects/x/class_end.h>
