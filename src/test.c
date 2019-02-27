#include "wfsm.h"
#include "wfsm_session.h"
#include "wfsm_state.h"
#include "wfsm_state_normal.h"
#include "wfsm_event.h"

int main()
{
    struct wfsm* f = W_NEW(wfsm);

    struct wfsm_state* s = W_NEW(wfsm_state_normal, .name = "s");
    printf("name=%s\n", s->name);
    W_CALL(f,add_state)(s);

    struct wfsm_session* session = W_NEW(wfsm_session, .fsm = f);
    W_CALL(session,push_event)(W_NEW(wfsm_event, .event = 1));

    W_CALL_VOID(session,free);
    W_CALL_VOID(f,free);
}

