#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_state.h"
#include "wfsm_event.h"
#include "wfsm_session.h"
#include "wfsm_transition.h"
#include "wfsm_transition_auto.h"


/* Begin class implementation. */
#include "wfsm_transition_auto_class.h"
#include <wondermacros/objects/x/class_start.h>

CONSTRUCT(wfsm_transition_auto)
{
}

FINALIZE(wfsm_transition_auto)
{
}

METHOD(wfsm_transition_auto,public,void,take,
    (struct wfsm_event* event, struct wfsm_session* session, struct wfsm_state** statep))
{
    W_CALL(*statep,exit)(session);
    if (self->action_cb)
        self->action_cb(session, event);
    W_CALL(self->target,enter)(session, statep);
}


#include <wondermacros/objects/x/class_end.h>
