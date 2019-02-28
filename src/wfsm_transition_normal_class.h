#define CLASS wfsm_transition_normal

#define wfsm_transition_normal__define                                       \
    /* Inherits: */                                                          \
    wfsm_transition_on_event__define                                         \
                                                                             \
    OVERRIDE(wfsm_transition_normal,take)                                    \
                                                                             \
    VAR(read,struct wfsm_state*,target)                                      \
    /**/
