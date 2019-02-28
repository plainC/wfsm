#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_state_final.h"
#include "wfsm_session.h"


/* Begin class implementation. */
#include "wfsm_state_final_class.h"
#include <wondermacros/objects/x/class_start.h>

CONSTRUCT(wfsm_state_final)
{
    W_CALL_ACONSTRUCT(wfsm_state);
}

FINALIZE(wfsm_state_final)
{
    W_CALL_AFINALIZE(wfsm_state);
}

METHOD(wfsm_state_final,public,void,enter,
    (struct wfsm_session* session, struct wfsm_state** startp))
{
    W_CALL_STATIC(wfsm_state,self,enter)(session,startp);
    W_CALL_VOID(session,deactivate);
}

#include <wondermacros/objects/x/class_end.h>
