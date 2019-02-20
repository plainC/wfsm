#define CLASS wfsm_region

#define wfsm_region__define                                              \
    /* Inherits */                                                       \
      /*none */                                                          \
                                                                         \
    METHOD(wfsm_region,public,void,add_state,                            \
        (const struct wfsm_state* state))                                \
    METHOD(wfsm_region,public,void,add_transition,                       \
        (const struct wfsm_transition* transition))                      \
                                                                         \
    METHOD(wfsm_region,public,void,set_start,                            \
        (struct wfsm_state* state))                                      \
    METHOD(wfsm_region,public,void,start)                                \
    METHOD(wfsm_region,public,void,run_queue)                            \
                                                                         \
    METHOD(wfsm_region,public,void,push_event,                           \
        (WFSM_EVENT_TYPE event, void* data))                             \
                                                                         \
    VAR(private,struct wfsm_state*,start_state)                          \
    VAR(read,struct wfsm_state*,current_state)                           \
    VAR(private,struct wfsm_event*,events)                               \
    VAR(private,struct wfsm_state**,states)                              \
    VAR(private,struct wfsm_transition**,transitions)                    \
                                                                         \
    /**/