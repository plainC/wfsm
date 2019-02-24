#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_state_initial.h"
#include "wfsm_region.h"
#include "wfsm_transition.h"

/* Begin class implementation. */
#include "wfsm_state_initial_class.h"
#include <wondermacros/objects/x/class_start.h>


CONSTRUCT(wfsm_state_initial) /* self */
{
    self->events = NULL;
}

FINALIZE(wfsm_state_initial) /* self */
{
    W_HASH_TABLE_FOR_EACH(struct wfsm_event_map, map, self->events) {
        W_CALL_VOID(W_OBJECT_AS(map->value,wfsm_transition),free);
    }

    W_HASH_TABLE_FREE(self->events);
}


#include <wondermacros/objects/x/class_end.h>
