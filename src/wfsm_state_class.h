#define CLASS wfsm_state

#define ABSTRACT

#define wfsm_state__define                                                   \
    /* Inherits: */                                                          \
    /* none */                                                               \
                                                                             \
    METHOD(wfsm_state,public,void,enter,                                     \
        (struct wfsm_session* session, struct wfsm_state** startp))          \
    METHOD(wfsm_state,public,void,exit,                                      \
        (struct wfsm_session* session))                                      \
                                                                             \
    METHOD(wfsm_state,public,int,add_transition,                             \
        (struct wfsm_transition* transition))                                \
    METHOD(wfsm_state,public,void,on_event,                                  \
        (struct wfsm_event* event, struct wfsm_session* session,             \
         struct wfsm_state** statep))                                        \
                                                                             \
    VAR(read,wfsm_state_cb,on_entry_cb)                                      \
    VAR(read,wfsm_state_cb,on_exit_cb)                                       \
                                                                             \
    VAR(read,char*,name)                                                     \
    VAR(private,struct wfsm_transition**,transitions)                        \
    VAR(private,struct wfsm_transition**,auto_transitions)                   \
                                                                             \
    /**/


#define TO_HEADER                                                            \
    typedef void (*wfsm_state_cb)(struct wfsm_session* session);


