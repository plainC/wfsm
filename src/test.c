#include "wfsm.h"
#include "wfsm_session.h"
#include "wfsm_state.h"
#include "wfsm_state_normal.h"
#include "wfsm_state_initial.h"
#include "wfsm_transition.h"
#include "wfsm_transition_auto.h"
#include "wfsm_transition_self.h"
#include "wfsm_transition_normal.h"
#include "wfsm_event.h"
#include <wondermacros/misc/unused.h>

#define S_FUNC(type,name) \
void name ## _ ## type(struct wfsm_session* session) \
{ \
    W_UNUSED(session); \
    printf(# name " " # type "\n"); \
}

#define A_FUNC(name) \
void name ## _action(struct wfsm_session* session, struct wfsm_event* event) \
{ \
    W_UNUSED(session); \
    W_UNUSED(event); \
    printf(# name " action\n"); \
}

S_FUNC(entry,s1)
S_FUNC(entry,s2)
S_FUNC(entry,s3)
S_FUNC(entry,s3sub)
S_FUNC(exit,s1)
S_FUNC(exit,s2)
S_FUNC(exit,s3)
S_FUNC(exit,s3sub)
A_FUNC(auto)
A_FUNC(self)
A_FUNC(normal)
A_FUNC(to_sub)
A_FUNC(to_s2)

int main()
{
    struct wfsm* f = W_NEW(wfsm);

    struct wfsm_event* e1 = W_CALL(f,add_event_type)(W_NEW(wfsm_event, .name = "E1"));
    struct wfsm_event* e2 = W_CALL(f,add_event_type)(W_NEW(wfsm_event, .name = "E2"));
    struct wfsm_event* e3 = W_CALL(f,add_event_type)(W_NEW(wfsm_event, .name = "E3"));
    printf("%d %d %d\n", e1->event, e2->event, e3->event);

    struct wfsm_state* s1 = W_NEW(wfsm_state_initial, .name = "s1", .on_entry_cb=s1_entry, .on_exit_cb=s1_exit);
    struct wfsm_state* s2 = W_NEW(wfsm_state_normal, .name = "s2", .on_entry_cb=s2_entry, .on_exit_cb=s2_exit);
    struct wfsm_state* s3 = W_NEW(wfsm_state_normal, .name = "s3", .on_entry_cb=s3_entry, .on_exit_cb=s3_exit);
    struct wfsm_state* s3sub = W_NEW(wfsm_state_normal, .name = "s3sub", .on_entry_cb=s3sub_entry, .on_exit_cb=s3sub_exit, .super = s3);

    W_CALL(s1,add_transition)(W_NEW(wfsm_transition_auto, .target=s2, .action_cb = auto_action));
    W_CALL(s2,add_transition)(W_NEW(wfsm_transition_self, .event = e1->event, .action_cb = self_action));
    W_CALL(s2,add_transition)(W_NEW(wfsm_transition_normal, .event = e2->event, .target = s3, .action_cb = normal_action));
    W_CALL(s3,add_transition)(W_NEW(wfsm_transition_normal, .event = e3->event, .target = s3sub, .action_cb = to_sub_action));
    W_CALL(s3sub,add_transition)(W_NEW(wfsm_transition_normal, .event = e1->event, .target = s2, .action_cb = to_s2_action));

    W_CALL(f,add_state)(s1);
    W_CALL(f,add_state)(s2);
    W_CALL(f,add_state)(s3);

    struct wfsm_session* session = W_NEW(wfsm_session, .fsm = f);
    W_CALL(session,push_event)(e1);
    W_CALL(session,push_event)(e2);
    W_CALL(session,push_event)(e3);
    W_CALL(session,push_event)(e1);
    while (!W_CALL_VOID(session,pop_event));


    W_CALL_VOID(session,free);
    W_CALL_VOID(f,free);
}

