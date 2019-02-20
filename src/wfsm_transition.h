#ifndef __WFSM_TRANSITION_H
#define __WFSM_TRANSITION_H

#include "wfsm.h"

typedef void (*wfsm_transition_func)(struct wfsm_transition* self, struct wfsm_event* event);

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
