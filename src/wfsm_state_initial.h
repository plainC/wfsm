#ifndef __WFSM_STATE_INITIAL_H
#define __WFSM_STATE_INITIAL_H

#include "wfsm.h"
#include "wfsm_state_pseudo.h"

/* Build the header. */
#include "wfsm_state_initial_class.h"
#include <wondermacros/objects/x/class_declare.h>

/*Unit Test*/

#ifndef W_TEST
# define W_TEST(...)
#endif


#ifndef W_TEST_GROUP
# define W_TEST_GROUP(...)
#endif

W_TEST_GROUP("States")

W_TEST(wfsm_state_initial,
    struct wfsm* fsm = W_NEW(wfsm);

    struct wfsm_state* A = (void*)
        W_CALL(fsm,add_state)(NULL, (void*) W_NEW(wfsm_state_initial));

    W_CALL_VOID(fsm,start);

    W_TEST_ASSERT(fsm->default_region->current_state == A, "fsm start failed");

    W_CALL_VOID(fsm,free);
)

#endif
