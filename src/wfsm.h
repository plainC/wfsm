#ifndef __WFSM_H
#define __WFSM_H

#ifndef WDEBUG_EXPAND
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

# include <boost/preprocessor/variadic/size.hpp>
# include <wondermacros/objects/api.h>
# include <wondermacros/array/dynamic_array.h>
#endif

#define WFSM_EVENT_TYPE unsigned

/* Forward declare all classes. */
#define W_XMACRO <wondermacros/objects/x/forward_declare.h>
#include "classes.h"

/* Build the header. */
#include "wfsm_class.h"
#include <wondermacros/objects/x/class_declare.h>

/*Unit Test*/

#ifndef W_TEST
# define W_TEST(...)
#endif

#ifndef W_TEST_GROUP
# define W_TEST_GROUP(...)
#endif

W_TEST_GROUP("FSM Core")

W_TEST(wfsm,
    struct wfsm* fsm = W_NEW(wfsm);
    W_CALL_VOID(fsm,free);
)

#endif
