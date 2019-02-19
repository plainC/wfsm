#define CLASS wfsm_transition

#define wfsm_transition__define                                          \
    /* Inherits */                                                       \
      /*none */                                                          \
                                                                         \
    METHOD(wfsm_transition,public,void,take)                             \
                                                                         \
    VAR(read,struct wfsm_state*,start)                                   \
    VAR(read,WFSM_EVENT_TYPE,event)                                      \
    VAR(read,struct wfsm_state*,target)                                  \
    /**/
