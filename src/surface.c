#include <stdlib.h>
#include <math.h>

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
    float alpha = (float)wrenGetSlotDouble(vm, 4);

    // Check alpha
    if (alpha < 0.0f) {
        alpha = 0.0f;
    } else if (alpha > 1.0f) {
        alpha = 1.0f;
    }

    if (surface_id >= engine->surfaces->size) {
        LOG_ERROR("Trying to draw a surface with an invalid ID\n");
        return;
    }

    Tigr *surface = (Tigr *)pe_vector_get(engine->surfaces, surface_id);

    if (surface == NULL) {
        LOG_ERROR("Trying to draw a NULL surface\n");
        return;
    }

    tigrBlitAlpha(engine->screen, surface, x, y, 0, 0, surface->w, surface->h,
                  alpha);
}

/*
** Draw a surface rotated to the screen
*/
void pe_surface_draw_surface_rotated(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t surface_id = (uint32_t)wrenGetSlotDouble(vm, 1);
    uint32_t x = (uint32_t)wrenGetSlotDouble(vm, 2);
    uint32_t y = (uint32_t)wrenGetSlotDouble(vm, 3);
    double angle = wrenGetSlotDouble(vm, 4);

    if (surface_id >= engine->surfaces->size) {
        LOG_ERROR("Trying to draw a surface with an invalid ID\n");
        return;
    }

    Tigr *surface = (Tigr *)pe_vector_get(engine->surfaces, surface_id);

    if (surface == NULL) {
        LOG_ERROR("Trying to draw a NULL surface\n");
        return;
    }

    for (uint32_t sx = 0; sx < (uint32_t)surface->w; sx++) {
        for (uint32_t sy = 0; sy < (uint32_t)surface->h; sy++) {
            unsigned char r, g, b, a;
            uint32_t new_x, new_y;
            struct Tigr *app_surface = engine->screen;

            size_t index = sx + sy * surface->w;
            a = surface->pix[index].a;
            r = surface->pix[index].r;
            g = surface->pix[index].g;
            b = surface->pix[index].b;

            if (a == 0) {
                continue;
            }

            // negate the angle because of top-left origin
            double a_cos = cos(-angle);
            double a_sin = sin(-angle);

            int32_t centered_x = sx - ((uint32_t)surface->w / 2);
            int32_t centered_y = sy - ((uint32_t)surface->h / 2);

            new_x = (centered_x * a_cos - centered_y * a_sin) + x;
            new_y = (centered_x * a_sin + centered_y * a_cos) + y;

            if (new_x >= (uint32_t)app_surface->w ||
                new_y >= (uint32_t)app_surface->h) {
                continue;
            }

            tigrPlot(app_surface, new_x, new_y, tigrRGBA(r, g, b, a));

            if (new_x + 1 >= (uint32_t)app_surface->w ||
                new_y + 1 >= (uint32_t)app_surface->h) {
                continue;
            }

            // fill in gaps
            tigrPlot(app_surface, new_x + 1, new_y, tigrRGBA(r, g, b, a));
            tigrPlot(app_surface, new_x, new_y + 1, tigrRGBA(r, g, b, a));
            tigrPlot(app_surface, new_x + 1, new_y + 1, tigrRGBA(r, g, b, a));
        }
    }
}

/*
** Get width of the surface
*/
void pe_surface_get_width(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t surface_id = (uint32_t)wrenGetSlotDouble(vm, 1);

    if (surface_id >= engine->surfaces->size) {
        LOG_ERROR("Trying to get width of a surface with an invalid ID\n");
        return;
    }

    Tigr *surface = (Tigr *)pe_vector_get(engine->surfaces, surface_id);

    if (surface == NULL) {
        LOG_ERROR("Trying to get width of a NULL surface\n");
        return;
    }

    wrenSetSlotDouble(vm, 0, surface->w);
}

/*
** Get height of the surface
*/
void pe_surface_get_height(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t surface_id = (uint32_t)wrenGetSlotDouble(vm, 1);

    if (surface_id >= engine->surfaces->size) {
        LOG_ERROR("Trying to get height of a surface with an invalid ID\n");
        return;
    }

    Tigr *surface = (Tigr *)pe_vector_get(engine->surfaces, surface_id);

    if (surface == NULL) {
        LOG_ERROR("Trying to get height of a NULL surface\n");
        return;
    }

    wrenSetSlotDouble(vm, 0, surface->h);
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
                    "new(_,_)", true, &pe_surface_new_surface);
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "new_from_png(_)", true, &pe_surface_new_surface_from_png);
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "set_target(_)", true, &pe_surface_set_surface_as_target);
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "reset_target()", true, &pe_surface_reset_target);
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "draw(_,_,_,_)", true, &pe_surface_draw_surface);
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "get_width(_)", true, &pe_surface_get_width);
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "get_height(_)", true, &pe_surface_get_height);
    pe_add_function(&engine_state->wren_functions, "main", "Surface",
                    "draw_angle(_,_,_,_)", true,
                    &pe_surface_draw_surface_rotated);
}
