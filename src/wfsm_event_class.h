#define CLASS wfsm_event

#define NO_CONSTRUCT

#define wfsm_event__define                                                   \
    /* Inherits: */                                                          \
    /* none */                                                               \
                                                                             \
    METHOD(wfsm_event,public,void,change_id,                                 \
        (unsigned id))                                                       \
                                                                             \
    VAR(read,char*,name)                                                     \
    VAR(read,unsigned,event)                                                 \
                                                                             \
    /**/
