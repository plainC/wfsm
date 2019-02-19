#ifndef __WFSM_STATE_H
#define __WFSM_STETE_H

#include "wfsm.h"

typedef void (*wfsm_state_func)(struct wfsm_state* self);

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
