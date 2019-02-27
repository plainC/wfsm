#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_state.h"
#include "wfsm_event.h"
#include "wfsm_session.h"
#include "wfsm_transition.h"
#include "wfsm_transition_self.h"


/* Begin class implementation. */
#include "wfsm_state_class.h"
#include <wondermacros/objects/x/class_start.h>

CONSTRUCT(wfsm_state) {
    if (self->name)
        self->name = strdup(self->name);

    self->wfsm_state.transitions = NULL;
}

FINALIZE(wfsm_state) {
    free(self->name);
}

METHOD(wfsm_state,public,int,add_transition,
    (struct wfsm_transition* transition))
{
    W_CALL(transition,set_start)(self);
    struct wfsm_transition_self* tr = (void*) transition;
printf("%d\n", tr->event);
    W_DYNAMIC_ARRAY_GROW_AT_LEAST(self->wfsm_state.transitions,tr->event+1);
    self->wfsm_state.transitions[tr->event] = transition;
    return 0;
}

METHOD(wfsm_state,public,void,on_event,
    (struct wfsm_event* event, struct wfsm_session* session,
     struct wfsm_state** statep))
{
    W_UNUSED(statep);

    struct wfsm_transition* transition = self->wfsm_state.transitions[event->event];
    if (!transition) {
        printf("%u ignored\n",event->event);
        return;
    }

    if (!W_CALL(transition,accepted)(event,session)) {
        printf("%u event not accepted\n", event->event);
        return;
    }

    W_CALL(transition,take)(event,session,statep);
}

#include <wondermacros/objects/x/class_end.h>
