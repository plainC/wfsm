#define CLASS wfsm_region

#define wfsm_region__define                                              \
    /* Inherits */                                                       \
      /*none */                                                          \
                                                                         \
    METHOD(wfsm_region,public,void,add_state,                            \
        (void* state))                                                   \
                                                                         \
    METHOD(wfsm_region,public,void,start)                                \
                                                                         \
    METHOD(wfsm_region,public,void,push_event,                           \
        (WFSM_EVENT_TYPE event, void* data))                             \
                                                                         \
    VAR(private,struct wfsm_state**,states)                              \
    VAR(private,struct wfsm_transition**,transitions)                    \
                                                                         \
    /**/
