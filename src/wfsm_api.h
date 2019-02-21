#ifndef __WFSM_API_H
#define __WFSM_API_H

#include <boost/preprocessor/seq/for_each.hpp>
#include <wondermacros/meta/stringize.h>
#include <wondermacros/misc/unused.h>


#define ADD_STATES(fsm,...)                                                \
   BOOST_PP_OVERLOAD(_ADD_STATES_,__VA_ARGS__)(fsm,__VA_ARGS__)
#define _ADD_STATES_1(fsm,states)                                          \
   _ADD_STATES_2(fsm,states,NULL)
#define _ADD_STATES_2(fsm,states,Super)                                    \
   BOOST_PP_SEQ_FOR_EACH(_ADD_STATES,(fsm,Super),states)
#define _ADD_STATES(z,tuple,state)                                         \
   struct wfsm_state* W_CAT(state_,BOOST_PP_SEQ_ELEM(0,state)) =           \
        W_CALL(BOOST_PP_TUPLE_ELEM(0,tuple),add_state)(NULL,               \
        W_NEW(wfsm_state,                                                  \
        .super = BOOST_PP_TUPLE_ELEM(1,tuple),                             \
        .name = W_STRINGIZE(BOOST_PP_SEQ_ELEM(0,state)),                   \
        .flags = W_CAT(WFSM_STATE_,BOOST_PP_SEQ_ELEM(1,state)),            \
        .entry_cb = W_CAT(BOOST_PP_SEQ_ELEM(0,state),_entry),              \
        .exit_cb = W_CAT(BOOST_PP_SEQ_ELEM(0,state),_exit)));


#define ADD_TRANSITIONS(fsm,transitions)                                   \
   BOOST_PP_SEQ_FOR_EACH(_ADD_TRANSITIONS,fsm,transitions)
#define _ADD_TRANSITIONS(z,fsm,transition)                                 \
    W_CALL(fsm,add_transition)(NULL, W_NEW(wfsm_transition,                \
        .start = W_CAT(state_,BOOST_PP_SEQ_ELEM(0,transition)),            \
        .event = BOOST_PP_SEQ_ELEM(1,transition),                          \
        .target = W_CAT(state_,BOOST_PP_SEQ_ELEM(2,transition)),           \
        .action_cb = W_CAT(BOOST_PP_SEQ_ELEM(0,transition),_,              \
            BOOST_PP_SEQ_ELEM(1,transition))));

#define BUILD_STATE_FUNCS(states)                                          \
    BOOST_PP_SEQ_FOR_EACH(_BUILD_STATE_FUNCS,~,states)
#define _BUILD_STATE_FUNCS(z,data,state)                                   \
    void W_CAT(BOOST_PP_SEQ_ELEM(0,state),_entry)(struct wfsm_state* self) \
    { W_UNUSED(self); BOOST_PP_SEQ_ELEM(2,state) }                         \
    void W_CAT(BOOST_PP_SEQ_ELEM(0,state),_exit)(struct wfsm_state* self)  \
    { W_UNUSED(self); BOOST_PP_SEQ_ELEM(3,state) }

#define BUILD_TRANSITION_FUNCS(transitions)                                \
    BOOST_PP_SEQ_FOR_EACH(_BUILD_TRANSITION_FUNCS,~,transitions)
#define _BUILD_TRANSITION_FUNCS(z,data,transition)                         \
    void W_CAT(BOOST_PP_SEQ_ELEM(0,transition),_,                          \
        BOOST_PP_SEQ_ELEM(1,transition))                                   \
        (struct wfsm_transition* self, struct wfsm_event* event)           \
    { W_UNUSED(self); W_UNUSED(event); BOOST_PP_SEQ_ELEM(3,transition) }   \

#endif

