#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_state.h"
#include "wfsm_event.h"
#include "wfsm_session.h"
#include "wfsm_transition.h"
#include "wfsm_transition_auto.h"
#include "wfsm_transition_on_event.h"
#include "wfsm_transition_self.h"


/* Begin class implementation. */
#include "wfsm_state_class.h"
#include <wondermacros/objects/x/class_start.h>

CONSTRUCT(wfsm_state) {
    if (self->name)
        self->name = strdup(self->name);

    self->wfsm_state.transitions = NULL;
    self->wfsm_state.auto_transitions = NULL;
}

FINALIZE(wfsm_state) {
    free(self->name);
}

METHOD(wfsm_state,public,void,enter,
    (struct wfsm_session* session, struct wfsm_state** startp))
{
    if (*startp != W_OBJECT_AS(self,wfsm_state)) {
        struct wfsm_state* state = self->super;
        struct wfsm_state** stack = NULL;
        while (state && state != *startp) {
            W_DYNAMIC_STACK_PUSH(stack, state);
            state = W_OBJECT_AS(state->super,wfsm_state);
        }
        while (!W_DYNAMIC_STACK_IS_EMPTY(stack)) {
            state = W_DYNAMIC_STACK_POP(stack);
            if (state->on_entry_cb)
                self->on_entry_cb(session);
            *startp = state;
        }
        W_DYNAMIC_STACK_FREE(stack);
    }
    if (self->on_entry_cb)
        self->on_entry_cb(session);
    *startp = W_OBJECT_AS(self,wfsm_state);

    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_transition*, transition, self->wfsm_state.auto_transitions) {
        if (W_CALL(transition,accepted)(NULL, session)) {
            W_CALL(transition,take)(NULL, session, startp);
            return;
        }
    }
}

METHOD(wfsm_state,public,int,is_superstate_of,
    (struct wfsm_state* state))
{
    if (!state)
        return 0;

    state = W_OBJECT_AS(state->super,wfsm_state);
    while (state) {
        if (state == W_OBJECT_AS(self,wfsm_state))
            return 1;
        state = W_OBJECT_AS(state->super,wfsm_state);
    }
    return 0;
}

METHOD(wfsm_state,public,int,is_substate_of,
    (struct wfsm_state* state))
{
    if (state)
        return W_CALL(state,is_superstate_of)(W_OBJECT_AS(self,wfsm_state));
    return 0;
}

METHOD(wfsm_state,public,void,exit,
    (struct wfsm_session* session, struct wfsm_state** statep, struct wfsm_state* target))
{
    if (!W_CALL(self,is_superstate_of)(target) && self->on_exit_cb)
        self->on_exit_cb(session);

    struct wfsm_state* state = self->super;
    while (state) {
        if (!W_CALL(state,is_superstate_of)(target) && state->on_exit_cb)
            state->on_exit_cb(session);
        *statep = state;
        state = W_OBJECT_AS(state->super,wfsm_state);
    }
}

METHOD(wfsm_state,public,int,add_transition,
    (struct wfsm_transition* transition))
{
    W_CALL(transition,set_start)(W_OBJECT_AS(self,wfsm_state));
    struct wfsm_transition_on_event* tr = W_OBJECT_AS(transition,wfsm_transition_on_event);

    if (W_OBJECT_IS(transition,wfsm_transition_auto)) {
        W_DYNAMIC_ARRAY_PUSH(self->wfsm_state.auto_transitions, transition);
        return 0;
    }
    W_DYNAMIC_ARRAY_GROW_AT_LEAST(self->wfsm_state.transitions,tr->event+1);
    self->wfsm_state.transitions[tr->event] = transition;
    return 0;
}

METHOD(wfsm_state,public,void,on_event,
    (struct wfsm_event* event, struct wfsm_session* session,
     struct wfsm_state** statep))
{
    struct wfsm_transition* transition = self->wfsm_state.transitions ?
        self->wfsm_state.transitions[event->event] : NULL;

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
