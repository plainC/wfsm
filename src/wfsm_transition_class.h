#define CLASS wfsm_transition

#define wfsm_transition__define                                          \
    /* Inherits */                                                       \
      /*none */                                                          \
                                                                         \
    METHOD(wfsm_transition,public,int,try_on_event,                      \
        (struct wfsm_event* event))                                      \
                                                                         \
    VAR(read,wfsm_transition_func,action_cb)                             \
    VAR(read,wfsm_guard_func,guard_cb)                                   \
                                                                         \
    VAR(read,struct wfsm_state_pseudo*,start)                                   \
    VAR(read,WFSM_EVENT_TYPE,event)                                      \
    VAR(read,struct wfsm_state_pseudo*,target)                                  \
                                                                         \
    VAR(read,int,flags)                                                  \
    /**/
