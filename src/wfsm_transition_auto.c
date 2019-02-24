#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_transition_auto.h"
#include "wfsm_state.h"

/* Begin class implementation. */
#include "wfsm_transition_auto_class.h"
#include <wondermacros/objects/x/class_start.h>


CONSTRUCT(wfsm_transition_auto) /* self */
{
    W_UNUSED(self);
}

FINALIZE(wfsm_transition_auto) /* self */
{
    W_UNUSED(self);
}

METHOD(wfsm_transition_auto,public,int,try_on_event,
    (struct wfsm_event* event))
{
    W_UNUSED(self);

    if (self->guard_cb && !self->guard_cb(W_OBJECT_AS(self,wfsm_transition), event))
        return 0;

//    W_CALL_VOID(self->start,exit);
    if (self->action_cb)
        self->action_cb(W_OBJECT_AS(self,wfsm_transition), event);
    W_CALL(W_OBJECT_AS(self->start,wfsm_state_pseudo),enter)(event);

printf("HH\n");
    return 1;
}

#include <wondermacros/objects/x/class_end.h>
