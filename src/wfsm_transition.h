#ifndef __WFSM_TRANSITION_H
#define __WFSM_TRANSITION_H

#include "wfsm.h"

typedef void (*wfsm_transition_func)(struct wfsm_transition* self, struct wfsm_event* event);
typedef int (*wfsm_guard_func)(struct wfsm_transition* self, struct wfsm_event* event);

enum wfsm_transition_flags {
    WFSM_TRANSITION_NORMAL   = 0,
    WFSM_TRANSITION_LOCAL    = 1,
    WFSM_TRANSITION_INTERNAL = 2,
    WFSM_TRANSITION_AUTO     = 4,
    WFSM_TRANSITION_INITIAL  = 8,
};

/* Build the header. */
#include "wfsm_transition_class.h"
#include <wondermacros/objects/x/class_declare.h>

/*Unit Test*/

#ifndef W_TEST
# define W_TEST(...)
#endif

#ifndef W_TEST_GROUP
# define W_TEST_GROUP(...)
#endif

#endif
