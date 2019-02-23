#ifndef __WFSM_API_H
#define __WFSM_API_H

#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/punctuation/remove_parens.hpp>
#include <wondermacros/meta/stringize.h>
#include <wondermacros/misc/unused.h>


#define ADD_STATES(fsm,...)                                                \
   BOOST_PP_OVERLOAD(_ADD_STATES_,__VA_ARGS__)(fsm,__VA_ARGS__)
#define _ADD_STATES_1(fsm,states)                                          \
   _ADD_STATES_2(fsm,states,NULL)
#define _ADD_STATES_2(fsm,states,Super)                                    \
   BOOST_PP_SEQ_FOR_EACH(_ADD_STATES,(fsm,Super),states)
#define GET_FSM(tuple) BOOST_PP_TUPLE_ELEM(0,tuple)
#define GET_SUPER(tuple) BOOST_PP_TUPLE_ELEM(1,tuple)
#define GET_NAME(state) BOOST_PP_TUPLE_ELEM(0,state)
#define GET_TYPE(state) W_CAT(WFSM_STATE_,BOOST_PP_TUPLE_ELEM(1,state))
#define GET_ENTRY(state) W_CAT(GET_NAME(state),_entry)
#define GET_EXIT(state) W_CAT(GET_NAME(state),_exit)
#define GET_ENTRY_CODE(state) BOOST_PP_TUPLE_ELEM(2,state)
#define GET_EXIT_CODE(state) BOOST_PP_TUPLE_ELEM(3,state)

#define _ADD_STATES(z,tuple,state) _ADD_STATES_(tuple,state)
#define _ADD_STATES_(tuple,state)                       \
   struct wfsm_state* W_CAT(state_,GET_NAME(state)) =   \
        W_CALL(GET_FSM(tuple),add_state)(NULL,          \
        W_NEW(wfsm_state,                               \
        .region = GET_FSM(tuple)->default_region,       \
        .super = GET_SUPER(tuple),                      \
        .name = W_STRINGIZE(GET_NAME(state)),           \
        .flags = GET_TYPE(state),                       \
        .entry_cb = GET_ENTRY(state),                   \
        .exit_cb = GET_EXIT(state)));


#define GET_KIND(transition) W_CAT(WFSM_TRANSITION_,BOOST_PP_TUPLE_ELEM(0,transition))
#define GET_START(transition) BOOST_PP_TUPLE_ELEM(1,transition)
#define GET_EVENT(transition) BOOST_PP_TUPLE_ELEM(2,transition)
#define GET_TARGET(transition) BOOST_PP_TUPLE_ELEM(3,transition)
#define GET_ACTION(transition) BOOST_PP_TUPLE_ELEM(4,transition)
#define GET_GUARD(transition) BOOST_PP_TUPLE_ELEM(5,transition)

#define ADD_TRANSITIONS(fsm,transitions)                                            \
   BOOST_PP_SEQ_FOR_EACH(_ADD_TRANSITIONS,fsm,transitions)
#define _ADD_TRANSITIONS(z,fsm,transition)                                          \
    W_CALL(fsm,add_transition)(NULL, W_NEW(wfsm_transition,                         \
        .start = W_CAT(state_,GET_START(transition)),                               \
        .event = GET_EVENT(transition),                                             \
        .target = W_CAT(state_,GET_TARGET(transition)),                             \
        .flags = GET_KIND(transition),                                              \
        .action_cb = W_CAT(GET_START(transition),_,                                 \
            GET_EVENT(transition)),                                                 \
        .guard_cb = BOOST_PP_IF(BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(transition),5),\
            W_CAT(GET_START(transition),_,GET_EVENT(transition),_guard),NULL)));

#define BUILD_STATE_FUNCS(states)                                          \
    BOOST_PP_SEQ_FOR_EACH(_BUILD_STATE_FUNCS,~,states)
#define _BUILD_STATE_FUNCS(z,data,state)                                   \
    void W_CAT(GET_NAME(state),_entry)(struct wfsm_state* self)            \
    { W_UNUSED(self); GET_ENTRY_CODE(state) }                              \
    void W_CAT(GET_NAME(state),_exit)(struct wfsm_state* self)             \
    { W_UNUSED(self); GET_EXIT_CODE(state) }

#define BUILD_TRANSITION_FUNCS(transitions)                                \
    BOOST_PP_SEQ_FOR_EACH(_BUILD_TRANSITION_FUNCS,~,transitions)
#define _BUILD_TRANSITION_FUNCS(z,data,transition)                         \
    void W_CAT(GET_START(transition),_,                                    \
        GET_EVENT(transition))                                             \
        (struct wfsm_transition* self, struct wfsm_event* event)           \
    { W_UNUSED(self); W_UNUSED(event); GET_ACTION(transition) }            \
    BOOST_PP_EXPR_IF(BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(transition),5),  \
        int W_CAT(GET_START(transition),_,GET_EVENT(transition),_guard)    \
        (struct wfsm_transition* self, struct wfsm_event* event)           \
    { W_UNUSED(self); W_UNUSED(event);                                     \
        return GET_GUARD(transition); })                                   \

#endif

