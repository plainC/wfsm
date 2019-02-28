#define CLASS wfsm_state_final

#define NO_CONSTRUCT
#define NO_DESTRUCT

#define wfsm_state_final__define                                             \
    /* Inherits: */                                                          \
    wfsm_state__define                                                       \
                                                                             \
    OVERLOAD(wfsm_state_final,enter)                                         \
                                                                             \
    /**/
