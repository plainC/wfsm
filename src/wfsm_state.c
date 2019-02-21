#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_state.h"
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
    W_UNUSED(self);
}

METHOD(wfsm_state,public,void,add_transition,
    (const struct wfsm_transition* transition))
{
    W_HASH_TABLE_PUSH(struct wfsm_event_map, self->events, transition->event, transition);
}

METHOD(wfsm_state,public,void,enter)
{
    if (self->entry_cb)
        self->entry_cb((void*) self);
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
    printf("event:%u\n", event->event);
    if (!self->events)
        return 0;
    W_HASH_TABLE_FOR_EACH_MATCH(struct wfsm_event_map, match, self->events, event->event) {
printf("%p\n", match);
        if (W_CALL(W_OBJECT_AS(match->value,wfsm_transition),try_on_event)(event))
            return 1;
    }
    if (self->super)
        if (W_CALL(self->super,on_event)(event))
            return 1;
    printf("Event: %u ignored in %s\n", event->event, self->name);
    return 0;
}

#include <wondermacros/objects/x/class_end.h>
