#define CLASS wfsm

#define wfsm__define                                                      \
    /* Inherits */                                                        \
      /*none */                                                           \
                                                                          \
    METHOD(wfsm,public,struct wfsm_state*,add_state,                      \
        (struct wfsm_region* region, struct wfsm_state* state))           \
                                                                          \
    METHOD(wfsm,public,struct wfsm_transition*,add_transition,            \
        (struct wfsm_region* region, struct wfsm_transition* transition)) \
                                                                          \
    METHOD(wfsm,public,void,add_state_region,                             \
        (const char* name))                                               \
                                                                          \
    METHOD(wfsm,public,void,set_start,                                    \
        (struct wfsm_region* region, struct wfsm_state* state))           \
    METHOD(wfsm,public,void,start)                                        \
    METHOD(wfsm,public,void,run_queues)                                   \
                                                                          \
    METHOD(wfsm,public,void,push_event,                                   \
        (WFSM_EVENT_TYPE event, void* data))                              \
                                                                          \
    METHOD(wfsm,public,void,stop_by_final,                                \
        (struct wfsm_region* region, struct wfsm_state* state))           \
                                                                          \
    VAR(public,int,is_running)                                            \
    VAR(private,struct wfsm_region**,orthogonal_regions)                  \
    VAR(read,struct wfsm_region*,default_region)                          \
                                                                          \
    /**/
