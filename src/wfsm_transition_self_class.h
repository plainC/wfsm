#define CLASS wfsm_transition_self

#define wfsm_transition_self__define                                         \
    /* Inherits: */                                                          \
    wfsm_transition__define                                                  \
                                                                             \
    OVERLOAD(wfsm_transition_self,take)                                      \
                                                                             \
    VAR(read,unsigned,event)                                                 \
                                                                             \
    /**/
