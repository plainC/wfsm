#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_state.h"


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
    W_DYNAMIC_ARRAY_PUSH(self->states, state);

    return state;
}

METHOD(wfsm,public,struct wfsm_transition*,add_transition,
    (struct wfsm_transition* transition))
{

    return transition;
}


#include <wondermacros/objects/x/class_end.h>
