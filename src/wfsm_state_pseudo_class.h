#define CLASS wfsm_state_pseudo

#define wfsm_state_pseudo__define                                        \
    /* Inherits */                                                       \
      /*none */                                                          \
                                                                         \
    METHOD(wfsm_state_pseudo,public,void,enter,\
        (struct wfsm_event* event))                                 \
    METHOD(wfsm_state_pseudo,public,int,on_event,                               \
        (struct wfsm_event* event))                                      \
    METHOD(wfsm_state_pseudo,public,int,add_transition,                         \
        (const struct wfsm_transition* transition))                      \
                                                                         \
    VAR(public,struct wfsm_region*,region)                               \
    VAR(private,struct wfsm_event_map*,events)                           \
                                                                         \
    VAR(read,const struct wfsm_transition_auto*,auto_transition)         \
                                                                         \
    /**/
