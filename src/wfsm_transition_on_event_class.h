#define CLASS wfsm_transition_on_event

#define ABSTRACT
#define NO_CONSTRUCT

#define wfsm_transition_on_event__define                                     \
    /* Inherits: */                                                          \
    wfsm_transition__define                                                  \
                                                                             \
    VAR(read,unsigned,event)                                                 \
                                                                             \
    /**/
