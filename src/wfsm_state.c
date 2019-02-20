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
    const struct wfsm_transition* transition)
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

METHOD(wfsm_state,public,void,on_event,
    (struct wfsm_event* event))
{
    W_UNUSED(self);
    W_UNUSED(event);
    printf("%u\n", event->event);
    W_HASH_TABLE_FOR_EACH_MATCH(struct wfsm_event_map, match, self->events, event->event)
        W_CALL(match->value,try_on_event)(event);
}

#include <wondermacros/objects/x/class_end.h>
