#include "wfsm.h"
#include "wfsm_state.h"
#include "wfsm_transition.h"


#define STATES_TEST_01                                         \
 ( (A, INITIAL, printf("In A\n");, printf("Out of A\n");) )      \
 ( (B, NORMAL , printf("In B\n");, printf("Out of B\n");) )      \
 ( (C, FINAL  , printf("In C\n");, printf("Out of C\n");) )      \

#define TRANSITIONS_TEST_01                                    \
 ( (AUTO  , A, 0, B, printf("Auto transition\n"); ))             \
 ( (NORMAL, B, 8, C, printf("Transition to B\n"); ))             \

BUILD_STATE_FUNCS(STATES_TEST_01)
BUILD_TRANSITION_FUNCS(TRANSITIONS_TEST_01)

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


int main()
{
    struct wfsm* fsm = W_NEW(wfsm);

    {
        ADD_STATES(fsm, STATES_TEST_01);
        ADD_TRANSITIONS(fsm, TRANSITIONS_TEST_01);
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
}

