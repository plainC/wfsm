#include "wfsm.h"
#include "wfsm_state.h"
#include "wfsm_transition.h"
#include "wfsm_transition_self.h"
#include "wfsm_transition_internal.h"

/*

#define STATES_TEST_01                                           \
 ( (A, INITIAL, printf("In A\n");, printf("Out of A\n");) )      \
 ( (B, NORMAL , printf("In B\n");, printf("Out of B\n");) )      \
 ( (C, NORMAL , printf("In C\n");, printf("Out of C\n");) )      \
 ( (D, FINAL  , printf("In D\n");, printf("Out of D\n");) )      \

#define TRANSITIONS_TEST_01                                      \
 ( (AUTO  , A, 0, B, printf("Auto transition 1\n"); ))           \
 ( (AUTO  , B, 0, C, printf("Auto transition 2\n"); ))           \
 ( (NORMAL, C, 8, D, printf("Transition fro C to D\n"); ))       \

BUILD_STATE_FUNCS(STATES_TEST_01)
BUILD_TRANSITION_FUNCS(TRANSITIONS_TEST_01)

#define STATES_TEST_02                                           \
 ( (A2, INITIAL, printf("In A2\n");, printf("Out of A2\n");) )      \
 ( (B2, NORMAL , printf("In B2\n");, printf("Out of B2\n");) )      \
 ( (C2, NORMAL , printf("In C2\n");, printf("Out of C2\n");) )      \
 ( (D2, FINAL  , printf("In D2\n");, printf("Out of D2\n");) )      \

#define TRANSITIONS_TEST_02                                      \
 ( (NORMAL  , A2, 3, A2, printf("Self transition\n"); ))           \
 ( (NORMAL  , A2, 8, B2, printf("Normal transition 1\n"); ))           \
 ( (INTERNAL, B2, 3, B2, printf("Internal transition\n"); ))       \
 ( (NORMAL  , B2, 8, C2, printf("Transition from B to C\n"); ))       \
 ( (NORMAL  , C2, 8, D2, printf("Transition from C to D\n"); ))       \

BUILD_STATE_FUNCS(STATES_TEST_02)
BUILD_TRANSITION_FUNCS(TRANSITIONS_TEST_02)

*/
#if 0

#define STATES_R1                                                          \
 ( (A1) (INITIAL) (printf("In r1.A\n");) (printf("Out of r1.A\n");) )      \
 ( (B1) (NORMAL)  (printf("In r1.B\n");) (printf("Out of r1.B\n");) )      \
 ( (C1) (FINAL)   (printf("In r1.C\n");) (printf("Out of r1.C\n");) )      \

#define TRANSITIONS_R1                                                     \
 ( (A1) (12) (B1) (printf("Transition r1.1\n");) )                         \
 ( (B1) (8)  (C1) (printf("Transition r1.2\n");) )                         \

#define STATES_R1Bsub                                                      \
 ( (Bs1) (NORMAL) (printf("In r1.Bs1\n");) (printf("Out r1.Bs1\n");) )     \
 ( (Bs2) (NORMAL) (printf("In r1.Bs2\n");) (printf("Out r1.Bs2\n");) )     \

#define TRANSITIONS_R1Bsub                                                 \
 ( (B1) (42) (Bs1) (printf("Transition to R1B\n");) )                      \
 ( (Bs1) (7) (Bs2) (printf("Transition to Bs2\n");) )                      \
 ( (Bs2) (5) (C1)  (printf("Transition to C1\n");) )                       \

#define STATES_R2                                                          \
 ( (A2) (INITIAL) (printf("In r2.A\n");) (printf("Out of r2.A\n");) )      \
 ( (B2) (NORMAL)  (printf("In r2.B\n");) (printf("Out of r2.B\n");) )      \
 ( (C2) (FINAL)   (printf("In r2.C\n");) (printf("Out of r2.C\n");) )      \

#define TRANSITIONS_R2                                                     \
 ( (A2) (12) (B2) (printf("Transition r2.1\n");) )                         \
 ( (B2) (8)  (C2) (printf("Transition r2.2\n");) (1) )                     \


BUILD_STATE_FUNCS(STATES_R1)
BUILD_TRANSITION_FUNCS(TRANSITIONS_R1)

BUILD_STATE_FUNCS(STATES_R2)
BUILD_TRANSITION_FUNCS(TRANSITIONS_R2)

BUILD_STATE_FUNCS(STATES_R1Bsub)
BUILD_TRANSITION_FUNCS(TRANSITIONS_R1Bsub)

#endif


void
A_enter(struct wfsm_state* self)
{
    W_UNUSED(self);
    printf("A in\n");
}

void
A_exit(struct wfsm_state* self)
{
    W_UNUSED(self);
    printf("A out\n");
}

void
A_1(struct wfsm_state* self, struct wfsm_event* e)
{
    W_UNUSED(self);
    W_UNUSED(e);
    printf("A 1 transition\n");
}

int main()
{
    struct wfsm* fsm = W_NEW(wfsm);

    struct wfsm_state* A = W_CALL(fsm,add_state)(NULL,W_NEW(wfsm_state, .name="A", .flags=WFSM_STATE_INITIAL, .entry_cb=A_enter, .exit_cb=A_exit));
    W_CALL(fsm,add_transition)(NULL,(void*)W_NEW(wfsm_transition_internal,.start = A,.event=1,.action_cb=(void*)A_1));

    W_CALL_VOID(fsm,start);
    W_CALL(fsm,push_event)(1, "Foobar");

    while (W_CALL_VOID(fsm,pop_queues))
        ;

    W_CALL_VOID(fsm,free);

#if 0
    {
        ADD_STATES(fsm, STATES_TEST_01)
        ADD_TRANSITIONS(fsm, TRANSITIONS_TEST_01)
    }

#if 0
    W_CALL(fsm,add_state_region)("R2");

    {
        ADD_STATES(fsm, STATES_R2);
        ADD_TRANSITIONS(fsm, TRANSITIONS_R2);
    }

#endif
    W_CALL_VOID(fsm,start);
    W_CALL(fsm,push_event)(12, "Foobar");
    W_CALL(fsm,push_event)(8, "Next");

    while (W_CALL_VOID(fsm,pop_queues))
        ;

    W_CALL_VOID(fsm,free);

/**/
    printf("----------------------------\n");

    fsm = W_NEW(wfsm);

    {
        ADD_STATES(fsm, STATES_TEST_02)
        ADD_TRANSITIONS(fsm, TRANSITIONS_TEST_02)
    }

    W_CALL_VOID(fsm,start);
    W_CALL(fsm,push_event)(3, "Foobar");
    W_CALL(fsm,push_event)(8, "Next");
    W_CALL(fsm,push_event)(3, "Foobar");
    W_CALL(fsm,push_event)(8, "Foobar");
    W_CALL(fsm,push_event)(8, "Foobar");

    while (W_CALL_VOID(fsm,pop_queues))
        ;

    W_CALL_VOID(fsm,free);
#endif
}

