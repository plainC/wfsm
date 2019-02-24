#define CLASS wfsm_state_terminate

#define wfsm_state_terminate__define                                     \
    /* Inherits */                                                       \
    wfsm_state_pseudo__define                                            \
                                                                         \
    OVERLOAD(wfsm_state_terminate,enter) \
                                                                         \
    /**/
