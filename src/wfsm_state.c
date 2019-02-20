#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_state.h"

/* Begin class implementation. */
#include "wfsm_state_class.h"
#include <wondermacros/objects/x/class_start.h>


CONSTRUCT(wfsm_state) /* self */
{
    self->events = NULL;
}

FINALIZE(wfsm_state) /* self */
{
    W_UNUSED(self);
}

METHOD(wfsm_state,public,void,add_transition,
    const struct wfsm_transition* transition)
{
    W_UNUSED(self);
    W_UNUSED(transition);
}

METHOD(wfsm_state,public,void,enter)
{
    W_UNUSED(self);
}

METHOD(wfsm_state,public,void,exit)
{
    W_UNUSED(self);
}

METHOD(wfsm_state,public,void,on_event,
    (struct wfsm_event* event))
{
    W_UNUSED(self);
    W_UNUSED(event);
}

#include <wondermacros/objects/x/class_end.h>
