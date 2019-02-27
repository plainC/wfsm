#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm_session.h"
#include "wfsm_event.h"
#include "wfsm_state.h"


/* Begin class implementation. */
#include "wfsm_session_class.h"
#include <wondermacros/objects/x/class_start.h>

CONSTRUCT(wfsm_session)
{
    W_DEQUE_INIT(self->wfsm_session.events, 3 /* ^ 2 = 8 */);
}

FINALIZE(wfsm_session)
{
    W_DEQUE_FOR_EACH(struct wfsm_event*, event, self->wfsm_session.events) {
        W_CALL_VOID(event,free);
    }

    W_DEQUE_FREE(self->wfsm_session.events);
}

METHOD(wfsm_session,public,void,push_event,
    (struct wfsm_event* event))
{
    int is_full=0;
    W_DEQUE_PUSH_BACK(is_full,self->wfsm_session.events,event);
    if (is_full)
        printf("Error\n");
}

METHOD(wfsm_session,public,int,pop_event)
{
    if (W_DEQUE_IS_EMPTY(self->wfsm_session.events))
        return 1;

    struct wfsm_event* event;
    W_DEQUE_POP_FRONT(self->wfsm_session.events,event);

    W_DYNAMIC_ARRAY_FOR_EACH_PTR(struct wfsm_state*,state,self->wfsm_session.states) {
        W_CALL(*state,on_event)(event,W_OBJECT_AS(self,wfsm_session),state);
    }

    return 0;
}

#include <wondermacros/objects/x/class_end.h>
