#define CLASS wfsm_session

#define NO_CONSTRUCT
#define NO_DESTRUCT

#define wfsm_session__define                                                 \
    /* Inherits: */                                                          \
    /* none */                                                               \
                                                                             \
    VAR(read,unsigned,id)                                                    \
    VAR(read,const struct wfsm*,fsm)                                         \
    VAR(read,struct wfsm_state*,state)                                       \
                                                                             \
    /**/
