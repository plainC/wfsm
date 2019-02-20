#define CLASS wfsm_state

#define wfsm_state__define                                               \
    /* Inherits */                                                       \
      /*none */                                                          \
                                                                         \
    METHOD(wfsm_state,public,void,enter)                                 \
    METHOD(wfsm_state,public,void,exit)                                  \
    METHOD(wfsm_state,public,void,on_event,                              \
        (struct wfsm_event* event))                                      \
    METHOD(wfsm_state,public,void,add_transition,                        \
        (const struct wfsm_transition* transition))                        \
                                                                         \
    VAR(read,char*,name)                                                 \
    VAR(private,struct wfsm_event_map*,events)                           \
    VAR(read,wfsm_state_func,entry_cb)                                   \
    VAR(read,wfsm_state_func,exit_cb)                                    \
                                                                         \
    /**/