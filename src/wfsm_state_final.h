#ifndef __WFSM_STATE_FINAL_H
#define __WFSM_STATE_FINAL_H


/* Forward declare all classes. */
#define W_XMACRO <wondermacros/objects/x/forward_declare.h>
#include "classes.h"

#include "wfsm_state.h"

/* Build the header. */
#include "wfsm_state_final_class.h"
#include <wondermacros/objects/x/class_declare.h>


/*Unit Test*/

#ifndef W_TEST
# define W_TEST(...)
#endif


W_TEST(wfsm_state_final,
)

#endif
