#include "wfsm.h"
#include "wfsm_state.h"
#include "wfsm_transition.h"


#define STATES                                                             \
 ( (A) (INITIAL) (printf("In A\n");) (printf("Out of A\n");) )             \
 ( (B) (NORMAL)  (printf("In B\n");) (printf("Out of B\n");) )             \
 ( (C) (FINAL)   (printf("In C\n");) (printf("Out of C\n");) )             \

#define TRANSITIONS                                                        \
 ( (A) (12) (B) (printf("Transition 1\n");) )                              \
 ( (B) (8)  (C) (printf("Transition 2\n");) )                              \


BUILD_STATE_FUNCS(STATES)
BUILD_TRANSITION_FUNCS(TRANSITIONS)


int main()
{
    struct wfsm* fsm = W_NEW(wfsm);

    ADD_STATES(fsm, STATES);
    ADD_TRANSITIONS(fsm, TRANSITIONS);

    W_CALL_VOID(fsm,start);
    W_CALL(fsm,push_event)(12, "Foobar");
    W_CALL(fsm,push_event)(8, "Next");

    W_CALL_VOID(fsm,run_queues);

    W_CALL_VOID(fsm,free);
}

