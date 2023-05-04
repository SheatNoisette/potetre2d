
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
** Get keycode from string
*/
void pe_input_get_keycode(WrenVM *vm) {
    char *key = (char *)wrenGetSlotString(vm, 1);
    uint32_t keycode = 0;

    // @TODO: Handle special keys
    if (strlen(key) == 1) {
        keycode = (uint32_t)key[0];
    } else {
        keycode = 0;
    }

    wrenSetSlotDouble(vm, 0, (double)keycode);
}

/*
** Check if key is pressed
*/
void pe_input_is_pressed(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t keycode = (uint32_t)wrenGetSlotDouble(vm, 1);
    bool pressed = tigrKeyHeld(engine->screen, keycode);

    wrenSetSlotBool(vm, 0, pressed);
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
    pe_add_function(&engine_state->wren_functions, "main", "Input", "get_keycode(_)",
                    true, &pe_input_get_keycode);
    pe_add_function(&engine_state->wren_functions, "main", "Input", "is_key_pressed(_)",
                    true, &pe_input_is_pressed);
}
