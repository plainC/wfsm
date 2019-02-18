#define CLASS wfsm

#define wfsm__define                                                     \
    /* Inherits */                                                       \
      /*none */                                                          \
                                                                         \
    METHOD(wfsm,public,void,add_state,                                   \
        (void* region, void* state))                                     \
                                                                         \
    METHOD(wfsm,public,void,add_state_region,                            \
        (const char* name))                                              \
                                                                         \
    METHOD(wfsm,public,void,start)                                       \
                                                                         \
    METHOD(wfsm,public,void,push_event,                                  \
        (WFSM_EVENT_TYPE event, void* data))                             \
                                                                         \
                                                                         \
    /**/
