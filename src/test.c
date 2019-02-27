#include "wfsm.h"
#include "wfsm_session.h"
#include "wfsm_state.h"
#include "wfsm_state_normal.h"

int main()
{
    struct wfsm* f = W_NEW(wfsm);

    struct wfsm_state* s = W_NEW(wfsm_state_normal, .name = "s");
    printf("name=%s\n", s->name);

    W_CALL_VOID(f,free);
}

