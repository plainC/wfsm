#define CLASS wfsm_transition_internal

#define wfsm_transition_internal__define                                 \
    /* Inherits */                                                       \
    wfsm_transition__define                                              \
                                                                         \
    OVERLOAD(wfsm_transition_internal,try_on_event)                      \
                                                                         \
    /**/
