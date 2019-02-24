#ifndef __WFSM_TRANSITION_INTERNAL_H
#define __WFSM_TRANSITION_INTERNAL_H

#include "wfsm.h"
#include "wfsm_transition.h"

/* Build the header. */
#include "wfsm_transition_internal_class.h"
#include <wondermacros/objects/x/class_declare.h>

/*Unit Test*/

#ifndef W_TEST
# define W_TEST(...)
#endif

W_TEST(wfsm_transition_internal,
    struct wfsm* fsm = W_NEW(wfsm);

    struct wfsm_state* I = (void*)
        W_CALL(fsm,add_state)(NULL, (void*) W_NEW(wfsm_state_initial));

    W_CALL(fsm,add_transition)(NULL, W_NEW(wfsm_transition_internal,.start=I,.event=1));

    W_CALL_VOID(fsm,start);

    W_TEST_ASSERT(fsm->default_region->current_state == I, "fsm start failed");

    W_CALL_VOID(fsm,free);
)

#endif
