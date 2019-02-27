#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_state_initial.h"


/* Begin class implementation. */
#include "wfsm_state_initial_class.h"
#include <wondermacros/objects/x/class_start.h>

CONSTRUCT(wfsm_state_initial) {
    W_CALL_ACONSTRUCT(wfsm_state);
}

FINALIZE(wfsm_state_initial) {
    W_CALL_AFINALIZE(wfsm_state);
}

#include <wondermacros/objects/x/class_end.h>
