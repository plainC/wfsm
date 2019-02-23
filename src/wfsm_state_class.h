#define CLASS wfsm_state

#define wfsm_state__define                                               \
    /* Inherits */                                                       \
      /*none */                                                          \
                                                                         \
    METHOD(wfsm_state,public,void,enter)                                 \
    METHOD(wfsm_state,public,void,exit)                                  \
    METHOD(wfsm_state,public,int,on_event,                               \
        (struct wfsm_event* event))                                      \
    METHOD(wfsm_state,public,int,add_transition,                         \
        (const struct wfsm_transition* transition))                      \
                                                                         \
    VAR(read,struct wfsm_region*,region)                                 \
    VAR(read,struct wfsm_state*,super)                                   \
    VAR(read,char*,name)                                                 \
    VAR(read,enum wfsm_state_flags,flags)                                \
    VAR(private,struct wfsm_event_map*,events)                           \
    VAR(read,wfsm_state_func,entry_cb)                                   \
    VAR(read,wfsm_state_func,exit_cb)                                    \
                                                                         \
    VAR(read,const struct wfsm_transition*,auto_transition)              \
                                                                         \
    /**/
