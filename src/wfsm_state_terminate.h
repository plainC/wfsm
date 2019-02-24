#ifndef __WFSM_STATE_TERMINATE_H
#define __WFSM_STATE_TERMINATE_H

#include "wfsm.h"
#include "wfsm_state_pseudo.h"
#include "wfsm_state_initial.h"
#include "wfsm_state.h"
#include "wfsm_transition_normal.h"

/* Build the header. */
#include "wfsm_state_terminate_class.h"
#include <wondermacros/objects/x/class_declare.h>

/*Unit Test*/

#ifndef W_TEST
# define W_TEST(...)
#endif

W_TEST(wfsm_state_terminate,
    struct wfsm* fsm = W_NEW(wfsm);

    struct wfsm_state* I = (void*)
        W_CALL(fsm,add_state)(NULL, (void*) W_NEW(wfsm_state_initial));

    struct wfsm_state* T = (void*)
        W_CALL(fsm,add_state)(NULL, (void*) W_NEW(wfsm_state_terminate));

    W_CALL(fsm,add_transition)(NULL, W_NEW(wfsm_transition_normal,.start=I,.event=1,.target=T));

    W_CALL_VOID(fsm,start);

    W_TEST_ASSERT(fsm->default_region->current_state == I, "fsm start failed");

    W_CALL(fsm,push_event)(1, "Event");

    while (W_CALL_VOID(fsm,pop_queues))
        ;
    W_TEST_ASSERT(fsm->default_region->current_state == T, "transition failed");
    W_TEST_ASSERT(!fsm->is_running, "termination failed");

    W_CALL_VOID(fsm,free);
)

#endif
