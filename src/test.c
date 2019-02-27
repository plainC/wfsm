#include "wfsm.h"
#include "wfsm_session.h"
#include "wfsm_state.h"
#include "wfsm_state_normal.h"
#include "wfsm_state_initial.h"
#include "wfsm_transition_self.h"
#include "wfsm_event.h"

int main()
{
    struct wfsm* f = W_NEW(wfsm);

    struct wfsm_event* e1 = W_CALL(f,add_event_type)(W_NEW(wfsm_event, .name = "E1"));
    struct wfsm_event* e2 = W_CALL(f,add_event_type)(W_NEW(wfsm_event, .name = "E2"));
    struct wfsm_event* e3 = W_CALL(f,add_event_type)(W_NEW(wfsm_event, .name = "E3"));
    printf("%d %d %d\n", e1->event, e2->event, e3->event);

    struct wfsm_state* s = W_NEW(wfsm_state_initial, .name = "s");
    W_CALL(s,add_transition)(W_NEW(wfsm_transition_self, .event = e1->event));
    W_CALL(f,add_state)(s);

    struct wfsm_session* session = W_NEW(wfsm_session, .fsm = f);
    W_CALL(session,push_event)(e1);
    if (W_CALL_VOID(session,pop_event))
        printf("no events\n");

    W_CALL_VOID(session,free);
    W_CALL_VOID(f,free);
}

