#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_state.h"
#include "wfsm_region.h"
#include "wfsm_transition.h"

/* Begin class implementation. */
#include "wfsm_state_class.h"
#include <wondermacros/objects/x/class_start.h>


CONSTRUCT(wfsm_state) /* self */
{
    self->events = NULL;
}

FINALIZE(wfsm_state) /* self */
{
    W_HASH_TABLE_FOR_EACH(struct wfsm_event_map, map, self->events)
        W_CALL_VOID(W_OBJECT_AS(map->value,wfsm_transition),free);

    W_HASH_TABLE_FREE(self->events);
}

METHOD(wfsm_state,public,int,add_transition,
    (const struct wfsm_transition* transition))
{
    if (transition->flags & WFSM_TRANSITION_AUTO) {
        if (self->auto_transition)
            return 1;
        else
            self->auto_transition = transition;
    }

    if (transition->flags & WFSM_TRANSITION_INTERNAL &&
        transition->start != transition->target)
        return 1;

    W_HASH_TABLE_PUSH(struct wfsm_event_map, self->events, transition->event, transition);

    return 0;
}

METHOD(wfsm_state,public,void,exit)
{
    if (self->exit_cb)
        self->exit_cb((void*) self);
}

METHOD(wfsm_state,public,int,on_event,
    (struct wfsm_event* event))
{
    W_UNUSED(self);
    W_UNUSED(event);

    if (!self->events)
        return 0;
    W_HASH_TABLE_FOR_EACH_MATCH(struct wfsm_event_map, match, self->events, event->event) {
//        if (!match->value->guard_cb || match->value->guard_cb(W_OBJECT_AS(match->value,wfsm_transition), event)) {
            if (W_CALL(W_OBJECT_AS(match->value,wfsm_transition),try_on_event)(event)) //W_CALL(self->region,on_transition)(match->value, event);
            return 1;
  //      }
    }
    if (self->super)
//        if (W_CALL(self->super,on_event)(event))
            return 1;

    printf(" Event: %u ignored by %s\n", event->event, self->name);

    return 0;
}

#include <wondermacros/objects/x/class_end.h>
