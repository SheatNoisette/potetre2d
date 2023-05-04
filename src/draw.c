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

    tigrLine(engine->screen, x1, y1, x2, y2, tigrRGBA(r, g, b, a));
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
        tigrRect(engine->screen, x, y, w, h, tigrRGBA(r, g, b, a));
    } else {
        tigrFillRect(engine->screen, x, y, w, h, tigrRGBA(r, g, b, a));
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
        tigrFillCircle(engine->screen, x, y, r,
                       tigrRGBA(red, green, blue, alpha));
    } else {
        tigrCircle(engine->screen, x, y, r, tigrRGBA(red, green, blue, alpha));
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

    if (x >= (uint32_t)engine->screen->w || y >= (uint32_t)engine->screen->h) {
        return;
    }

    engine->screen->pix[y * engine->screen->w + x].r = r;
    engine->screen->pix[y * engine->screen->w + x].g = g;
    engine->screen->pix[y * engine->screen->w + x].b = b;
    engine->screen->pix[y * engine->screen->w + x].a = 0xFF;
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

    tigrClear(engine->screen, tigrRGBA(r, g, b, a));
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
}
