#include <stdlib.h>

#include "wren.h"
#include "engine.h"
#include "binding.h"
#include "tigr.h"

/*
** Drawing primitives
*/

/*
** Draw a line
*/
void pe_draw_line(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t x1 = (uint32_t)wrenGetSlotDouble(vm, 1);
    uint32_t y1 = (uint32_t)wrenGetSlotDouble(vm, 2);
    uint32_t x2 = (uint32_t)wrenGetSlotDouble(vm, 3);
    uint32_t y2 = (uint32_t)wrenGetSlotDouble(vm, 4);
    uint8_t r = (uint8_t)wrenGetSlotDouble(vm, 5) & 0xFF;
    uint8_t g = (uint8_t)wrenGetSlotDouble(vm, 6) & 0xFF;
    uint8_t b = (uint8_t)wrenGetSlotDouble(vm, 7) & 0xFF;
    uint8_t a = (uint8_t)wrenGetSlotDouble(vm, 8) & 0xFF;

    tigrLine(engine->current_surface, x1, y1, x2, y2, tigrRGBA(r, g, b, a));
}

/*
** Draw a rectangle (filled and unfilled)
*/
void pe_draw_rect(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t x = (uint32_t)wrenGetSlotDouble(vm, 1);
    uint32_t y = (uint32_t)wrenGetSlotDouble(vm, 2);
    uint32_t w = (uint32_t)wrenGetSlotDouble(vm, 3);
    uint32_t h = (uint32_t)wrenGetSlotDouble(vm, 4);
    uint8_t r = (uint8_t)wrenGetSlotDouble(vm, 5) & 0xFF;
    uint8_t g = (uint8_t)wrenGetSlotDouble(vm, 6) & 0xFF;
    uint8_t b = (uint8_t)wrenGetSlotDouble(vm, 7) & 0xFF;
    uint8_t a = (uint8_t)wrenGetSlotDouble(vm, 8) & 0xFF;
    bool filled = wrenGetSlotBool(vm, 9);

    if (filled) {
        tigrFillRect(engine->current_surface, x, y, w, h, tigrRGBA(r, g, b, a));
    } else {
        tigrRect(engine->current_surface, x, y, w, h, tigrRGBA(r, g, b, a));
    }
}

/*
** Draw a circle (filled and unfilled)
*/
void pe_draw_circle(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t x = (uint32_t)wrenGetSlotDouble(vm, 1);
    uint32_t y = (uint32_t)wrenGetSlotDouble(vm, 2);
    uint32_t r = (uint32_t)wrenGetSlotDouble(vm, 3);
    uint8_t red = (uint8_t)wrenGetSlotDouble(vm, 4) & 0xFF;
    uint8_t green = (uint8_t)wrenGetSlotDouble(vm, 5) & 0xFF;
    uint8_t blue = (uint8_t)wrenGetSlotDouble(vm, 6) & 0xFF;
    uint8_t alpha = (uint8_t)wrenGetSlotDouble(vm, 7) & 0xFF;
    bool filled = wrenGetSlotBool(vm, 8);

    if (filled) {
        tigrFillCircle(engine->current_surface, x, y, r,
                       tigrRGBA(red, green, blue, alpha));
    } else {
        tigrCircle(engine->current_surface, x, y, r,
                   tigrRGBA(red, green, blue, alpha));
    }
}

/*
** Put a pixel on the screen
*/
static void pe_engine_put_pixel(WrenVM *vm) {
    uint32_t x = (uint32_t)wrenGetSlotDouble(vm, 1);
    uint32_t y = (uint32_t)wrenGetSlotDouble(vm, 2);
    uint8_t r = (uint32_t)wrenGetSlotDouble(vm, 3) & 0xFF;
    uint8_t g = (uint32_t)wrenGetSlotDouble(vm, 4) & 0xFF;
    uint8_t b = (uint32_t)wrenGetSlotDouble(vm, 5) & 0xFF;

    // Get state from the VM
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    if (x >= (uint32_t)engine->current_surface->w ||
        y >= (uint32_t)engine->current_surface->h) {
        return;
    }

    engine->current_surface->pix[y * engine->current_surface->w + x].r = r;
    engine->current_surface->pix[y * engine->current_surface->w + x].g = g;
    engine->current_surface->pix[y * engine->current_surface->w + x].b = b;
    engine->current_surface->pix[y * engine->current_surface->w + x].a = 0xFF;
}

/*
** Clear the screen
*/
static void pe_engine_clear_screen(WrenVM *vm) {
    uint8_t r = (uint32_t)wrenGetSlotDouble(vm, 1) & 0xFF;
    uint8_t g = (uint32_t)wrenGetSlotDouble(vm, 2) & 0xFF;
    uint8_t b = (uint32_t)wrenGetSlotDouble(vm, 3) & 0xFF;
    uint8_t a = (uint32_t)wrenGetSlotDouble(vm, 4) & 0xFF;

    // Get state from the VM
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    tigrClear(engine->current_surface, tigrRGBA(r, g, b, a));
}

/*
** Draw text to the screen
*/
static void pe_engine_draw_text(WrenVM *vm) {
    uint32_t x = (uint32_t)wrenGetSlotDouble(vm, 1);
    uint32_t y = (uint32_t)wrenGetSlotDouble(vm, 2);
    const char *text = wrenGetSlotString(vm, 3);
    uint8_t r = (uint32_t)wrenGetSlotDouble(vm, 4) & 0xFF;
    uint8_t g = (uint32_t)wrenGetSlotDouble(vm, 5) & 0xFF;
    uint8_t b = (uint32_t)wrenGetSlotDouble(vm, 6) & 0xFF;
    uint8_t a = (uint32_t)wrenGetSlotDouble(vm, 7) & 0xFF;

    // Get state from the VM
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    tigrPrint(engine->current_surface, tfont, x, y, tigrRGBA(r, g, b, a), "%s",
              text);
}

/*
** Get the value of a pixel
*/
void pe_draw_get_pixel(WrenVM *vm) {
    uint32_t x = (uint32_t)wrenGetSlotDouble(vm, 1);
    uint32_t y = (uint32_t)wrenGetSlotDouble(vm, 2);

    // Get state from the VM
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    if (x >= (uint32_t)engine->current_surface->w ||
        y >= (uint32_t)engine->current_surface->h) {
        return;
    }

    size_t position = y * engine->current_surface->w + x;
    uint8_t r = engine->current_surface->pix[position].r;
    uint8_t g = engine->current_surface->pix[position].g;
    uint8_t b = engine->current_surface->pix[position].b;
    uint8_t a = engine->current_surface->pix[position].a;

    wrenSetSlotNewList(vm, 0);
    wrenSetSlotDouble(vm, 1, r);
    wrenInsertInList(vm, 0, 0, 1);
    wrenSetSlotDouble(vm, 1, g);
    wrenInsertInList(vm, 0, 1, 1);
    wrenSetSlotDouble(vm, 1, b);
    wrenInsertInList(vm, 0, 2, 1);
    wrenSetSlotDouble(vm, 1, a);
    wrenInsertInList(vm, 0, 3, 1);
}

/*
** Register the drawing primitives
*/
void pe_draw_register_functions(struct pe_engine_state *engine_state) {
    pe_add_function(&engine_state->wren_functions, "main", "Draw",
                    "line(_,_,_,_,_,_,_,_)", true, &pe_draw_line);
    pe_add_function(&engine_state->wren_functions, "main", "Draw",
                    "rectangle(_,_,_,_,_,_,_,_,_)", true, &pe_draw_rect);
    pe_add_function(&engine_state->wren_functions, "main", "Draw",
                    "circle(_,_,_,_,_,_,_,_)", true, &pe_draw_circle);
    pe_add_function(&engine_state->wren_functions, "main", "Draw",
                    "put_pixel(_,_,_,_,_)", true, &pe_engine_put_pixel);
    pe_add_function(&engine_state->wren_functions, "main", "Draw",
                    "clear(_,_,_,_)", true, &pe_engine_clear_screen);
    pe_add_function(&engine_state->wren_functions, "main", "Draw",
                    "text(_,_,_,_,_,_,_)", true, &pe_engine_draw_text);
    pe_add_function(&engine_state->wren_functions, "main", "Draw",
                    "internal_get_pixel(_,_)", true, &pe_draw_get_pixel);
}
