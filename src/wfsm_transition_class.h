#define CLASS wfsm_transition

#define wfsm_transition__define                                          \
    /* Inherits */                                                       \
      /*none */                                                          \
                                                                         \
    METHOD(wfsm_transition,public,void,take,                             \
        (struct wfsm_event* event))                                      \
    METHOD(wfsm_transition,public,int,try_on_event,                      \
        (struct wfsm_event* event))                                      \
                                                                         \
    VAR(read,wfsm_transition_func,transition_cb)                         \
    VAR(read,struct wfsm_state*,start)                                   \
    VAR(read,WFSM_EVENT_TYPE,event)                                      \
    VAR(read,struct wfsm_state*,target)                                  \
    /**/
