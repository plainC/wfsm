#define CLASS wfsm

#define NO_CONSTRUCT

#define wfsm__define                                                      \
    /* Inherits */                                                        \
      /*none */                                                           \
                                                                          \
    METHOD(wfsm,public,struct wfsm_state*,add_state,                      \
        (struct wfsm_state* state))                                       \
                                                                          \
    METHOD(wfsm,public,struct wfsm_transition*,add_transition,            \
        (struct wfsm_transition* transition))                             \
                                                                          \
    VAR(read,struct wfsm_state**,states)                                  \
                                                                          \
    /**/
