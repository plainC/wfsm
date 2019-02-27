#define CLASS wfsm_transition_normal

#define wfsm_transition_normal__define                                       \
    /* Inherits: */                                                          \
    wfsm_transition_on_event__define                                         \
                                                                             \
    OVERLOAD(wfsm_transition_normal,take)                                    \
                                                                             \
    VAR(read,struct wfsm_state*,target)                                      \
    /**/
