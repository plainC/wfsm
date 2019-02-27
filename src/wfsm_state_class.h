#define CLASS wfsm_state

#define ABSTRACT

#define wfsm_state__define                                                   \
    /* Inherits: */                                                          \
    /* none */                                                               \
                                                                             \
    METHOD(wfsm_state,public,void,on_event,                                  \
        (struct wfsm_event* event, struct wfsm_session* session,             \
         struct wfsm_state** statep))                                        \
    VAR(read,char*,name)                                                     \
                                                                             \
    /**/
