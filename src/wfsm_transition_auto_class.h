#define CLASS wfsm_transition_auto

#define wfsm_transition_auto__define                                         \
    /* Inherits: */                                                          \
    wfsm_transition__define                                                  \
                                                                             \
    OVERRIDE(wfsm_transition_auto,take)                                      \
                                                                             \
    VAR(read,struct wfsm_state*,target)                                      \
                                                                             \
    /**/
