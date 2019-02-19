#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_transition.h"

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

METHOD(wfsm_transition,public,void,take)
{
    W_UNUSED(self);
}

#include <wondermacros/objects/x/class_end.h>
