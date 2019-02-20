#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_region.h"
#include "wfsm_transition.h"
#include "wfsm_state.h"

/* Begin class implementation. */
#include "wfsm_region_class.h"
#include <wondermacros/objects/x/class_start.h>


CONSTRUCT(wfsm_region) /* self */
{
    self->states = NULL;
    W_DEQUE_INIT(self->events, WFSM_EVENT_QUEUE_SIZE);
    self->transitions = NULL;
    self->start_state = self->current_state = NULL;
}

FINALIZE(wfsm_region) /* self */
{
    W_DYNAMIC_ARRAY_FOR_EACH(const struct wfsm_state*, state, self->states)
        W_CALL_VOID(W_OBJECT_AS(state,wfsm_state),free);

    W_DYNAMIC_ARRAY_FREE(self->states);

    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_transition*, transition, self->transitions)
        W_CALL_VOID(transition,free);

    W_DYNAMIC_ARRAY_FREE(self->transitions);

    W_DEQUE_FREE(self->events);
}

METHOD(wfsm_region,public,void,add_state,
    (const struct wfsm_state* state))
{
    W_DYNAMIC_ARRAY_PUSH(self->states, state);
    if (state->flags & WFSM_STATE_INITIAL) {
        if (self->start_state)
            printf("ERROR: Multiple initial states\n");
        else
            printf("Start set\n"),self->start_state = state;
    }
}

METHOD(wfsm_region,public,void,add_transition,
    (const struct wfsm_transition* transition))
{
    W_CALL(W_OBJECT_AS(transition->start,wfsm_state),add_transition)(transition);
}

METHOD(wfsm_region,public,void,set_start,
    (struct wfsm_state* state))
{
    if (self->start_state)
        printf("ERROR: Start state already set\n");
    else
        self->start_state = state;
}

METHOD(wfsm_region,public,void,set_state,
    (const struct wfsm_state* state))
{
    self->current_state = state;
    W_CALL_VOID(state,enter);
    if (self->current_state->flags & WFSM_STATE_FINAL)
        W_CALL(self->owner,stop_by_final)(self,state);
}

METHOD(wfsm_region,public,void,start)
{
    W_CALL(self,set_state)(self->start_state);
}

METHOD(wfsm_region,public,void,stop)
{
    // FIXME: todo
}

METHOD(wfsm_region,public,void,run_queue)
{
printf("Run queue: %d\n", W_DEQUE_GET_SIZE(self->events));
    while (!W_DEQUE_IS_EMPTY(self->events)) {
        struct wfsm_event event;
        W_DEQUE_POP_FRONT(self->events, event);
printf("State: %p\n", self->current_state);
        W_CALL(W_OBJECT_AS(self->current_state,wfsm_state),on_event)(&event);
    }
printf("Queue empty\n");
}

METHOD(wfsm_region,public,void,push_event,
    (WFSM_EVENT_TYPE event, void* data))
{
    struct wfsm_event e;
    e.event = event;
    e.region = (void*) self;
    e.data = data;

    int is_full;
    W_DEQUE_PUSH_BACK(is_full, self->events, e);
    if (is_full)
        printf("ERROR: Queue full\n");
    else
        printf("Added event: %u to the queue\n", event);
}

#include <wondermacros/objects/x/class_end.h>
