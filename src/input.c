
#include <stdlib.h>
#include <string.h>

#include "tigr.h"
#include "wren.h"
#include "engine.h"

/*
** Input subsystem
*/

/*
** Get mouse x position
*/
void pe_input_mouse_x(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    int x, y, buttons;
    tigrMouse(engine->screen, &x, &y, &buttons);

    wrenSetSlotDouble(vm, 0, (double)x);
}

/*
** Get mouse y position
*/
void pe_input_mouse_y(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    int x, y, buttons;
    tigrMouse(engine->screen, &x, &y, &buttons);

    wrenSetSlotDouble(vm, 0, (double)y);
}

/*
** Get mouse button
*/
void pe_input_mouse_button(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    int x, y, buttons;
    tigrMouse(engine->screen, &x, &y, &buttons);

    // Maybe don't use double?
    wrenSetSlotDouble(vm, 0, (double)buttons);
}

/*
** Register input functions
*/
void pe_input_register_functions(struct pe_engine_state *engine_state) {
    pe_add_function(&engine_state->wren_functions, "main", "Input", "mouse_x()",
                    true, &pe_input_mouse_x);
    pe_add_function(&engine_state->wren_functions, "main", "Input", "mouse_y()",
                    true, &pe_input_mouse_y);
    pe_add_function(&engine_state->wren_functions, "main", "Input", "get_mouse_button()",
                    true, &pe_input_mouse_button);
}
