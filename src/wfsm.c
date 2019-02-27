#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_state.h"
#include "wfsm_state_initial.h"
#include "wfsm_event.h"


/* Begin class implementation. */
#include "wfsm_class.h"
#include <wondermacros/objects/x/class_start.h>


FINALIZE(wfsm) /* self */
{
    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_state*, state, self->states)
        W_CALL_VOID(state,free);

    W_DYNAMIC_ARRAY_FREE(self->states);
}

METHOD(wfsm,public,struct wfsm_state*,add_state,
    (struct wfsm_state* state))
{
    if (W_OBJECT_IS(state,wfsm_state_initial)) {
        W_DYNAMIC_ARRAY_PUSH(self->initial_states, state);
    }

    return state;
}

METHOD(wfsm,public,struct wfsm_transition*,add_transition,
    (struct wfsm_transition* transition))
{

    return transition;
}

METHOD(wfsm,public,struct wfsm_event*,add_event_type,
        (struct wfsm_event* event))
{
    W_DYNAMIC_ARRAY_PUSH(self->events, event);
    W_CALL(event,change_id)(W_DYNAMIC_ARRAY_SIZE(self->events)-1);

    return event;
}

#include <wondermacros/objects/x/class_end.h>
