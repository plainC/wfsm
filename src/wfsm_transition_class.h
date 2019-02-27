#define CLASS wfsm_transition

#define ABSTRACT
#define NO_CONSTRUCT

#define wfsm_transition__define                                              \
    /* Inherits: */                                                          \
    /* none */                                                               \
                                                                             \
    METHOD(wfsm_transition,public,void,set_start,                            \
        (struct wfsm_state* state))                                          \
    METHOD(wfsm_transition,public,int,accepted,                              \
        (struct wfsm_event* event, struct wfsm_session* session))            \
    METHOD(wfsm_transition,public,void,take,                                 \
        (struct wfsm_event* event, struct wfsm_session* session,             \
         struct wfsm_state** statep))                                        \
                                                                             \
    VAR(read,struct wfsm_state*,start)                                       \
    VAR(public,wfsm_action_cb,action_cb)                                     \
                                                                             \
    /**/

#define TO_HEADER                                                            \
    typedef void (*wfsm_action_cb)(struct wfsm_session* session, struct wfsm_event* event);

