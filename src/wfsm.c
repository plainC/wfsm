#ifndef WDEBUG_EXPAND
# include <wondermacros/misc/unused.h>
#endif


#include "wfsm.h"
#include "wfsm_region.h"


/* Begin class implementation. */
#include "wfsm_class.h"
#include <wondermacros/objects/x/class_start.h>


CONSTRUCT(wfsm) /* self */
{
    self->orthogonal_regions = NULL;
    self->default_region = W_NEW(wfsm_region, .owner = self);
    self->is_running = 0;

    W_DYNAMIC_ARRAY_PUSH(self->orthogonal_regions, self->default_region);
}

FINALIZE(wfsm) /* self */
{
    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_region*, region, self->orthogonal_regions)
        W_CALL_VOID(region,free);

    W_DYNAMIC_ARRAY_FREE(self->orthogonal_regions);
}

METHOD(wfsm,public,struct wfsm_state*,add_state,
    (struct wfsm_region* region, struct wfsm_state* state))
{
    if (!region)
        region = self->default_region;

    W_CALL(region,add_state)(state);

    return state;
}

METHOD(wfsm,public,struct wfsm_transition*,add_transition,
    (struct wfsm_region* region, struct wfsm_transition* transition))
{
    if (!region)
        region = self->default_region;

    W_CALL(region,add_transition)(transition);

    return transition;
}

METHOD(wfsm,public,void,add_state_region,
    (const char* name))
{
    W_UNUSED(self);
    W_UNUSED(name);
}

METHOD(wfsm,public,void,set_start,
    (struct wfsm_region* region, struct wfsm_state* state))
{
    if (!region)
        region = self->default_region;

    W_CALL(region,set_start)(state);
}

METHOD(wfsm,public,void,start)
{
    self->is_running = 1;
    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_region*, region, self->orthogonal_regions)
        W_CALL_VOID(region,start);
}

METHOD(wfsm,public,void,stop_by_final,
   (struct wfsm_region* region, struct wfsm_state* state))
{
    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_region*, r, self->orthogonal_regions)
        if (r != region)
            W_CALL_VOID(r,stop);
    self->is_running = 0;
}

METHOD(wfsm,public,void,run_queues)
{
    if (!self->is_running) {
        printf("Error: not running\n");
        return;
    }
    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_region*, region, self->orthogonal_regions)
        W_CALL_VOID(region,run_queue);
}

METHOD(wfsm,public,void,push_event,
    (WFSM_EVENT_TYPE event, void* data))
{
    if (!self->is_running) {
        printf("Error: not running\n");
        return;
    }
    W_DYNAMIC_ARRAY_FOR_EACH(struct wfsm_region*, region, self->orthogonal_regions)
        W_CALL(region,push_event)(event, data);
}


#include <wondermacros/objects/x/class_end.h>
