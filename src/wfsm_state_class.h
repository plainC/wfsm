#define CLASS wfsm_state

#define wfsm_state__define                                               \
    /* Inherits */                                                       \
      /*none */                                                          \
                                                                         \
    METHOD(wfsm_state,public,void,enter)                                 \
    METHOD(wfsm_state,public,void,exit)                                  \
                                                                         \
    VAR(read,char*,name)                                                 \
    VAR(read,wfsm_state_func,entry_cb)                                   \
    VAR(read,wfsm_state_func,exit_cb)                                    \
                                                                         \
    /**/
