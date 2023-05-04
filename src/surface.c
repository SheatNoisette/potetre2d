#include <stdlib.h>

#include "wren.h"
#include "tigr.h"
#include "engine.h"
#include "log.h"

/*
** Create a new surface and return its ID
*/
void pe_surface_new_surface(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t width = (uint32_t)wrenGetSlotDouble(vm, 1);
    uint32_t height = (uint32_t)wrenGetSlotDouble(vm, 2);

    Tigr *surface = tigrBitmap(width, height);

    uint32_t surface_id = pe_vector_push(engine->surfaces, (void *)surface);
    LOG_DEBUG("Created surface with ID %d\n", surface_id);
    wrenSetSlotDouble(vm, 0, surface_id);
}

/*
** Create a new surface from a PNG file and return its ID
*/
void pe_surface_new_surface_from_png(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    const char *path = wrenGetSlotString(vm, 1);

    if (path == NULL) {
        LOG_ERROR("Trying to load a surface from a NULL path\n");
        return;
    }

    Tigr *surface = tigrLoadImage(path);

    if (surface == NULL) {
        LOG_ERROR("Failed to load surface from path '%s'\n", path);
        return;
    }

    uint32_t surface_id = pe_vector_push(engine->surfaces, (void *)surface);
    LOG_DEBUG("Created surface with ID %d\n", surface_id);
    wrenSetSlotDouble(vm, 0, surface_id);
}

/*
** Set the surface as the target for drawing
*/
void pe_surface_set_surface_as_target(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t surface_id = (uint32_t)wrenGetSlotDouble(vm, 1);

    if (surface_id >= engine->surfaces->size) {
        LOG_ERROR("Trying to set a surface as target with an invalid ID\n");
        return;
    }

    Tigr *surface = (Tigr *)pe_vector_get(engine->surfaces, surface_id);

    if (surface == NULL) {
        LOG_ERROR("Trying to set a NULL surface as target\n");
        return;
    }

    engine->current_surface = surface;
}

/*
** Reset the target to the screen
*/
void pe_surface_reset_target(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    engine->current_surface = engine->screen;
}

/*
** Draw a surface to the screen
*/
void pe_surface_draw_surface(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t surface_id = (uint32_t)wrenGetSlotDouble(vm, 1);
    uint32_t x = (uint32_t)wrenGetSlotDouble(vm, 2);
    uint32_t y = (uint32_t)wrenGetSlotDouble(vm, 3);

    if (surface_id >= engine->surfaces->size) {
        LOG_ERROR("Trying to draw a surface with an invalid ID\n");
        return;
    }

    Tigr *surface = (Tigr *)pe_vector_get(engine->surfaces, surface_id);

    if (surface == NULL) {
        LOG_ERROR("Trying to draw a NULL surface\n");
        return;
    }

    tigrBlit(engine->screen, surface, x, y, 0, 0, surface->w, surface->h);
}

/*
** Destroy from the vector
*/
void pe_destroy_surface_engine(void *data) {
    if (data == NULL) {
        LOG_ERROR("Trying to destroy a NULL surface\n");
        return;
    }
    tigrFree((Tigr *)data);
}


void pe_surface_register_functions(struct pe_engine_state *engine_state) {
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "new_surface(_,_)", true, &pe_surface_new_surface);
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "new_surface_from_png(_)", true,
                    &pe_surface_new_surface_from_png);
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "set_target(_)", true,
                    &pe_surface_set_surface_as_target);
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "reset_target()", true, &pe_surface_reset_target);
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "draw_surface(_,_,_)", true, &pe_surface_draw_surface);
}
