#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_state.h"
#include "wfsm_event.h"
#include "wfsm_session.h"
#include "wfsm_transition.h"
#include "wfsm_transition_self.h"


/* Begin class implementation. */
#include "wfsm_transition_self_class.h"
#include <wondermacros/objects/x/class_start.h>

CONSTRUCT(wfsm_transition_self)
{
}

FINALIZE(wfsm_transition_self)
{
}

METHOD(wfsm_transition_self,public,void,take,
    (struct wfsm_event* event, struct wfsm_session* session, struct wfsm_state** statep))
{
    W_CALL(*statep,exit)(session,statep,self->start);
    if (self->action_cb)
        self->action_cb(session, event);
    W_CALL(*statep,enter)(session, statep);
}


#include <wondermacros/objects/x/class_end.h>
