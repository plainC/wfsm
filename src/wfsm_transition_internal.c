#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_transition_internal.h"
#include "wfsm_state.h"

/* Begin class implementation. */
#include "wfsm_transition_internal_class.h"
#include <wondermacros/objects/x/class_start.h>


CONSTRUCT(wfsm_transition_internal) /* self */
{
    W_UNUSED(self);
}

FINALIZE(wfsm_transition_internal) /* self */
{
    W_UNUSED(self);
}

METHOD(wfsm_transition_internal,public,int,try_on_event,
    (struct wfsm_event* event))
{
    W_UNUSED(self);

    if (self->guard_cb && !self->guard_cb(W_OBJECT_AS(self,wfsm_transition), event))
        return 0;

    if (self->action_cb)
        self->action_cb(W_OBJECT_AS(self,wfsm_transition), event);

    return 1;
}

#include <wondermacros/objects/x/class_end.h>
