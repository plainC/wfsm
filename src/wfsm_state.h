#ifndef __WFSM_STATE_H
#define __WFSM_STETE_H

#include "wfsm.h"

typedef void (*wfsm_state_func)(struct wfsm_state* self);

enum wfsm_state_flags {
    WFSM_STATE_NORMAL    = 0,
    WFSM_STATE_INITIAL   = 1,
    WFSM_STATE_FINAL     = 2,
    WFSM_STATE_TERMINATE = 4,
};

/* Build the header. */
#include "wfsm_state_class.h"
#include <wondermacros/objects/x/class_declare.h>

/*Unit Test*/

#ifndef W_TEST
# define W_TEST(...)
#endif

#ifndef W_TEST_GROUP
# define W_TEST_GROUP(...)
#endif

#endif
