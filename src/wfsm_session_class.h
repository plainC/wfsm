#define CLASS wfsm_session

#define wfsm_session__define                                                 \
    /* Inherits: */                                                          \
    /* none */                                                               \
                                                                             \
    VAR(read,unsigned,id)                                                    \
    VAR(read,const struct wfsm*,fsm)                                         \
                                                                             \
    VAR(private,struct wfsm_event**,events)                                  \
    VAR(private,struct wfsm_state**,states)                                  \
                                                                             \
    METHOD(wfsm_session,public,void,push_event,                              \
        (struct wfsm_event* event))                                          \
    METHOD(wfsm_session,public,int,pop_event)                                \
                                                                             \
    /**/
