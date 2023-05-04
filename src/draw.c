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
** Register the drawing primitives
*/
void pe_draw_register_functions(struct pe_engine_state *engine_state) {
    pe_add_function(&engine_state->wren_functions, "main", "Draw",
                    "line(_,_,_,_,_,_,_,_)", true, &pe_draw_line);
    pe_add_function(&engine_state->wren_functions, "main", "Draw",
                    "rectangle(_,_,_,_,_,_,_,_,_)", true, &pe_draw_rect);
    pe_add_function(&engine_state->wren_functions, "main", "Draw",
                    "circle(_,_,_,_,_,_,_,_)", true, &pe_draw_circle);
}