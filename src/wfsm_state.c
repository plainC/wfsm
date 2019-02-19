#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_state.h"

/* Begin class implementation. */
#include "wfsm_state_class.h"
#include <wondermacros/objects/x/class_start.h>


CONSTRUCT(wfsm_state) /* self */
{
    W_UNUSED(self);
}

FINALIZE(wfsm_state) /* self */
{
    W_UNUSED(self);
}

METHOD(wfsm_state,public,void,enter)
{
    W_UNUSED(self);
}

METHOD(wfsm_state,public,void,exit)
{
    W_UNUSED(self);
}

#include <wondermacros/objects/x/class_end.h>
