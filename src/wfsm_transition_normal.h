#ifndef __WFSM_TRANSITION_NORMAL_H
#define __WFSM_TRANSITION_NORMAL_H

#include "wfsm.h"
#include "wfsm_transition.h"

/* Build the header. */
#include "wfsm_transition_normal_class.h"
#include <wondermacros/objects/x/class_declare.h>

/*Unit Test*/

#ifndef W_TEST
# define W_TEST(...)
#endif

W_TEST(wfsm_transition_normal,
    struct wfsm* fsm = W_NEW(wfsm);

    struct wfsm_state* I = (void*)
        W_CALL(fsm,add_state)(NULL, (void*) W_NEW(wfsm_state_initial));
    struct wfsm_state* A = (void*)
        W_CALL(fsm,add_state)(NULL, (void*) W_NEW(wfsm_state));


    W_CALL(fsm,add_transition)(NULL, W_NEW(wfsm_transition_normal,.start=I,.event=1,.target=A));

    W_CALL_VOID(fsm,start);

    W_TEST_ASSERT(fsm->default_region->current_state == I, "fsm start failed");
    W_CALL(fsm,push_event)(1, "Event");

    while (W_CALL_VOID(fsm,pop_queues))
        ;
    W_TEST_ASSERT(fsm->default_region->current_state == A, "transition failed");

    W_CALL_VOID(fsm,free);
)

#endif
