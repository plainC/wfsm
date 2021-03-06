#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_event.h"


/* Begin class implementation. */
#include "wfsm_event_class.h"
#include <wondermacros/objects/x/class_start.h>

FINALIZE(wfsm_event)
{
}

METHOD(wfsm_event,public,void,change_id,
    (unsigned id))
{
    self->event = id;
}

#include <wondermacros/objects/x/class_end.h>
