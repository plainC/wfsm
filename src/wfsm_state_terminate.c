#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_state_pseudo.h"
#include "wfsm_state_terminate.h"
#include "wfsm_region.h"
#include "wfsm_transition.h"
#include "wfsm_transition_normal.h"

/* Begin class implementation. */
#include "wfsm_state_terminate_class.h"
#include <wondermacros/objects/x/class_start.h>


CONSTRUCT(wfsm_state_terminate) /* self */
{
    self->events = NULL;
}

FINALIZE(wfsm_state_terminate) /* self */
{
    W_HASH_TABLE_FOR_EACH(struct wfsm_event_map, map, self->events) {
        W_CALL_VOID(W_OBJECT_AS(map->value,wfsm_transition),free);
    }

    W_HASH_TABLE_FREE(self->events);
}

METHOD(wfsm_state_terminate,public,void,enter,
    (struct wfsm_event* event))
{
    W_UNUSED(event);

    W_CALL(self->region,set_state)(W_OBJECT_AS(self,wfsm_state_pseudo));

    W_CALL_VOID(W_OBJECT_AS(self->region->owner,wfsm),terminate);
}

#include <wondermacros/objects/x/class_end.h>
