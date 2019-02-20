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
    METHOD(wfsm_region,public,int,pop_queue)                             \
    METHOD(wfsm_region,public,void,stop)                                 \
    METHOD(wfsm_region,public,void,set_state,                            \
        (const struct wfsm_state* state))                                \
                                                                         \
                                                                         \
    METHOD(wfsm_region,public,void,push_event,                           \
        (WFSM_EVENT_TYPE event, void* data))                             \
                                                                         \
    VAR(read,char*,name)                                                 \
    VAR(read,const struct wfsm*,owner)                                   \
    VAR(private,const struct wfsm_state*,start_state)                    \
    VAR(read,const struct wfsm_state*,current_state)                     \
    VAR(private,struct wfsm_event*,events)                               \
    VAR(private,const struct wfsm_state**,states)                        \
    VAR(private,struct wfsm_transition**,transitions)                    \
                                                                         \
    /**/
