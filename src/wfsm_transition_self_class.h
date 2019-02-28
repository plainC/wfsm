#define CLASS wfsm_transition_self

#define wfsm_transition_self__define                                         \
    /* Inherits: */                                                          \
    wfsm_transition_on_event__define                                         \
                                                                             \
    OVERRIDE(wfsm_transition_self,take)                                      \
                                                                             \
    /**/
