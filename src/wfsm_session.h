#ifndef __WFSM_SESSION_H
#define __WFSM_SESSION_H

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
#define W_POSTFIX "_class.h"
#include "classes.h"

/* Build the header. */
#include "wfsm_session_class.h"
#include <wondermacros/objects/x/class_declare.h>


/*Unit Test*/

#ifndef W_TEST
# define W_TEST(...)
#endif


W_TEST(wfsm_session,
)

#endif
