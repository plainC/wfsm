#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_transition.h"
#include "wfsm_state.h"
#include "wfsm_region.h"

/* Begin class implementation. */
#include "wfsm_transition_class.h"
#include <wondermacros/objects/x/class_start.h>


CONSTRUCT(wfsm_transition) /* self */
{
    W_UNUSED(self);
}

FINALIZE(wfsm_transition) /* self */
{
    W_UNUSED(self);
}

METHOD(wfsm_transition,public,void,take,
    (struct wfsm_event* event))
{
    if (self->action_cb)
        self->action_cb((void*) self,event);
}

METHOD(wfsm_transition,public,int,try_on_event,
    (struct wfsm_event* event))
{
    W_UNUSED(self);
    if (0 /* guard check */)
        return 0;

    if (self->target != self->start) {
        W_CALL_VOID(self->start,exit);
        W_CALL(self,take)(event);
        W_CALL(W_OBJECT_AS(event->region,wfsm_region),set_state)(self->target);
        W_CALL_VOID(self->target,enter);
    } else
        W_CALL(self,take)(event);

    return 1;
}

#include <wondermacros/objects/x/class_end.h>
