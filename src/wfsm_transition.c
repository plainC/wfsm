#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_state.h"
#include "wfsm_event.h"
#include "wfsm_session.h"
#include "wfsm_transition.h"


/* Begin class implementation. */
#include "wfsm_transition_class.h"
#include <wondermacros/objects/x/class_start.h>

METHOD(wfsm_transition,public,void,set_start,
    (struct wfsm_state* state))
{
    self->start = state;
}

METHOD(wfsm_transition,public,int,accepted,
    (struct wfsm_event* event, struct wfsm_session* session))
{
    W_UNUSED(self);
    W_UNUSED(event);
    W_UNUSED(session);
    return 1;
}

METHOD(wfsm_transition,public,void,take,
    (struct wfsm_event* event, struct wfsm_session* session, struct wfsm_state** statep))
{
    W_UNUSED(self);
    W_UNUSED(event);
    W_UNUSED(session);
    W_UNUSED(statep);

    printf("Take\n");
}

#include <wondermacros/objects/x/class_end.h>
