#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"

/* Begin class implementation. */
#include "wfsm_class.h"
#include <wondermacros/objects/x/class_start.h>


CONSTRUCT(wfsm) /* self */
{
    W_UNUSED(self);
}

FINALIZE(wfsm) /* self */
{
    W_UNUSED(self);
}

METHOD(wfsm,public,void,add_state,
    (void* region, void* state))
{
    W_UNUSED(self);
    W_UNUSED(region);
    W_UNUSED(state);
}

METHOD(wfsm,public,void,add_state_region,
        (const char* name))
{
    W_UNUSED(self);
    W_UNUSED(name);
}

METHOD(wfsm,public,void,start)
{
    W_UNUSED(self);
}

METHOD(wfsm,public,void,push_event,
    (WFSM_EVENT_TYPE event, void* data))
{
    W_UNUSED(self);
    W_UNUSED(event);
    W_UNUSED(data);
}


#include <wondermacros/objects/x/class_end.h>
