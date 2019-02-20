#include "wfsm.h"
#include "wfsm_state.h"
#include "wfsm_transition.h"
#include <boost/preprocessor/seq/for_each.hpp>
#include <wondermacros/meta/stringize.h>
#include <wondermacros/misc/unused.h>


#define STATES                                                             \
 ( (A) (printf("In A\n");) (printf("Out of A\n");) )                       \
 ( (B) (printf("In B\n");) (printf("Out of B\n");) )                       \
 ( (C) (printf("In C\n");) (printf("Out of C\n");) )                       \

#define TRANSITIONS                                                        \
 ( (A) (12) (B) (printf("Transition 1\n");) )                              \
 ( (B) (8)  (C) (printf("Transition 2\n");) )                              \

#define ADD_STATES(fsm,states)                                             \
   BOOST_PP_SEQ_FOR_EACH(_ADD_STATES,fsm,states)
#define _ADD_STATES(z,fsm,state)                                           \
   struct wfsm_state* W_CAT(state_,BOOST_PP_SEQ_ELEM(0,state)) =           \
        W_CALL(fsm,add_state)(NULL, W_NEW(wfsm_state,                      \
        .name = W_STRINGIZE(BOOST_PP_SEQ_ELEM(0,state)),                   \
        .entry_cb = W_CAT(BOOST_PP_SEQ_ELEM(0,state),_entry),              \
        .exit_cb = W_CAT(BOOST_PP_SEQ_ELEM(0,state),_exit)));

#define ADD_TRANSITIONS(fsm,transitions)                                   \
   BOOST_PP_SEQ_FOR_EACH(_ADD_TRANSITIONS,fsm,transitions)
#define _ADD_TRANSITIONS(z,fsm,transition)                                 \
    W_CALL(fsm,add_transition)(NULL, W_NEW(wfsm_transition,                \
        .start = W_CAT(state_,BOOST_PP_SEQ_ELEM(0,transition)),            \
        .event = BOOST_PP_SEQ_ELEM(1,transition),                          \
        .target = W_CAT(state_,BOOST_PP_SEQ_ELEM(2,transition)),           \
        .action_cb = W_CAT(BOOST_PP_SEQ_ELEM(0,transition),_,BOOST_PP_SEQ_ELEM(1,transition))));

#define BUILD_STATE_FUNCS(states)                                          \
    BOOST_PP_SEQ_FOR_EACH(_BUILD_STATE_FUNCS,~,states)
#define _BUILD_STATE_FUNCS(z,data,state)                                   \
    void W_CAT(BOOST_PP_SEQ_ELEM(0,state),_entry)(struct wfsm_state* self) \
    { W_UNUSED(self); BOOST_PP_SEQ_ELEM(1,state) }                         \
    void W_CAT(BOOST_PP_SEQ_ELEM(0,state),_exit)(struct wfsm_state* self)  \
    { W_UNUSED(self); BOOST_PP_SEQ_ELEM(2,state) }

#define BUILD_TRANSITION_FUNCS(transitions)                                \
    BOOST_PP_SEQ_FOR_EACH(_BUILD_TRANSITION_FUNCS,~,transitions)
#define _BUILD_TRANSITION_FUNCS(z,data,transition)                                   \
    void W_CAT(BOOST_PP_SEQ_ELEM(0,transition),_,BOOST_PP_SEQ_ELEM(1,transition))(struct wfsm_transition* self, struct wfsm_event* event) \
    { W_UNUSED(self); BOOST_PP_SEQ_ELEM(3,transition) }                         \


BUILD_STATE_FUNCS(STATES)
BUILD_TRANSITION_FUNCS(TRANSITIONS)


int main()
{
    struct wfsm* fsm = W_NEW(wfsm);

    ADD_STATES(fsm, STATES);
    ADD_TRANSITIONS(fsm, TRANSITIONS);

    W_CALL(fsm,set_start)(NULL,state_A);
    W_CALL_VOID(fsm,start);
    W_CALL(fsm,push_event)(12, "Foobar");
    W_CALL(fsm,push_event)(8, "Next");

    W_CALL_VOID(fsm,run_queues);

    W_CALL_VOID(fsm,free);
}

