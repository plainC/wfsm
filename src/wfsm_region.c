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
    self->transitions = NULL;
}

FINALIZE(wfsm_region) /* self */
{
    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_state*, state, self->states)
        W_CALL_VOID(state,free);

    W_DYNAMIC_ARRAY_FREE(self->states);

    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_transition*, transition, self->transitions)
        W_CALL_VOID(transition,free);

    W_DYNAMIC_ARRAY_FREE(self->transitions);
}

METHOD(wfsm_region,public,void,add_state,
    (void* state))
{
    W_UNUSED(self);
    W_UNUSED(state);
}

METHOD(wfsm_region,public,void,start)
{
    W_UNUSED(self);
}

METHOD(wfsm_region,public,void,push_event,
    (WFSM_EVENT_TYPE event, void* data))
{
    W_UNUSED(self);
    W_UNUSED(event);
    W_UNUSED(data);
}

#include <wondermacros/objects/x/class_end.h>
