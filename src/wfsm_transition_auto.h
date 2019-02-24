#ifndef __WFSM_TRANSITION_AUTO_H
#define __WFSM_TRANSITION_AUTO_H

#include "wfsm.h"
#include "wfsm_transition.h"

/* Build the header. */
#include "wfsm_transition_auto_class.h"
#include <wondermacros/objects/x/class_declare.h>

/*Unit Test*/

#ifndef W_TEST
# define W_TEST(...)
#endif

#ifndef W_TEST_GROUP
# define W_TEST_GROUP(...)
#endif

W_TEST(wfsm_transition_auto,
    struct wfsm* fsm = W_NEW(wfsm);

    struct wfsm_state* I = (void*)
        W_CALL(fsm,add_state)(NULL, (void*) W_NEW(wfsm_state_initial));
    struct wfsm_state* A = (void*)
        W_CALL(fsm,add_state)(NULL, (void*) W_NEW(wfsm_state));


    W_CALL(fsm,add_transition)(NULL, W_NEW(wfsm_transition_auto,.start=I,.target=A));

    W_CALL_VOID(fsm,start);

    W_TEST_ASSERT(fsm->default_region->current_state == A, "auto transition failed");

    W_CALL_VOID(fsm,free);
)

#endif
