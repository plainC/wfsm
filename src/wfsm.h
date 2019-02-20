#ifndef __WFSM_H
#define __WFSM_H

#ifndef WDEBUG_EXPAND
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

# include <boost/preprocessor/variadic/size.hpp>
# include <wondermacros/objects/api.h>
# include <wondermacros/array/dynamic_array.h>
# include <wondermacros/array/deque.h>
# include <wondermacros/array/hash_table.h>
#endif

/* Forward declare all classes. */
#define W_XMACRO <wondermacros/objects/x/forward_declare.h>
#include "classes.h"



#define WFSM_EVENT_TYPE unsigned
#define WFSM_EVENT_QUEUE_SIZE 3 /* ^ 2 */

struct wfsm_event {
    WFSM_EVENT_TYPE event;
    const struct wfsm_region* region;
    void* data;
};

struct wfsm_event_map {
    WFSM_EVENT_TYPE key;
    const struct wfsm_transition* value;
};

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
