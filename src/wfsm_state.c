#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_state.h"
#include "wfsm_event.h"
#include "wfsm_session.h"


/* Begin class implementation. */
#include "wfsm_state_class.h"
#include <wondermacros/objects/x/class_start.h>

CONSTRUCT(wfsm_state) {
    if (self->name)
        self->name = strdup(self->name);
}

FINALIZE(wfsm_state) {
    free(self->name);
}

METHOD(wfsm_state,public,void,on_event,
    (struct wfsm_event* event, struct wfsm_session* session,
         struct wfsm_state** statep))
{
    W_UNUSED(self);
    W_UNUSED(session);
    W_UNUSED(statep);
    W_UNUSED(event);
}

#include <wondermacros/objects/x/class_end.h>
