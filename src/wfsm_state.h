#ifndef __WFSM_STATE_H
#define __WFSM_STATE_H

#include "wfsm.h"
#include "wfsm_state_pseudo.h"
#include "wfsm_state_initial.h"

typedef void (*wfsm_state_func)(struct wfsm_state* self);


/* Build the header. */
#include "wfsm_state_class.h"
#include <wondermacros/objects/x/class_declare.h>

/*Unit Test*/

#ifndef W_TEST
# define W_TEST(...)
#endif

W_TEST(wfsm_state,
    struct wfsm* fsm = W_NEW(wfsm);

    struct wfsm_state_pseudo* I = (void*)
        W_CALL(fsm,add_state)(NULL, (void*) W_NEW(wfsm_state_initial));

    struct wfsm_state* A = (void*)
        W_CALL(fsm,add_state)(NULL, (void*) W_NEW(wfsm_state, .name="A"));

    W_CALL_VOID(fsm,start);

    W_TEST_ASSERT(fsm->default_region->current_state == I, "fsm start failed");

    W_CALL_VOID(fsm,free);
)

#endif
