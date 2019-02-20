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
    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_state*, state, self->states)
        W_CALL_VOID(state,free);

    W_DYNAMIC_ARRAY_FREE(self->states);

    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_transition*, transition, self->transitions)
        W_CALL_VOID(transition,free);

    W_DYNAMIC_ARRAY_FREE(self->transitions);

    W_DEQUE_FREE(self->events);
}

METHOD(wfsm_region,public,void,add_state,
    (const struct wfsm_state* state))
{
    W_UNUSED(self);
    W_UNUSED(state);
}

METHOD(wfsm_region,public,void,add_transition,
    (const struct wfsm_transition* transition))
{
    W_CALL(transition->start,add_transition)(transition);
}

METHOD(wfsm_region,public,void,set_start,
    (struct wfsm_state* state))
{
    self->start_state = state;
}

METHOD(wfsm_region,public,void,start)
{
printf("Started:%p\n", self->start_state);
    self->current_state = self->start_state;
}

METHOD(wfsm_region,public,void,run_queue)
{
printf("Run queue\n");
    while (!W_DEQUE_IS_EMPTY(self->events)) {
        struct wfsm_event event;
        W_DEQUE_POP_FRONT(self->events, event);
printf("State: %p\n", self->current_state);
        W_CALL(self->current_state,on_event)(&event);
    }
}

METHOD(wfsm_region,public,void,push_event,
    (WFSM_EVENT_TYPE event, void* data))
{
    struct wfsm_event e;
    e.event = event;
    e.data = data;

    int is_full;
    W_DEQUE_PUSH_BACK(is_full, self->events, e);
}

#include <wondermacros/objects/x/class_end.h>
