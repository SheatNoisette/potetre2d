#include <stdlib.h>
#include <math.h>

#include "gmath.h"
#include "wren.h"
#include "engine.h"
#include "binding.h"

/*
** Common Math functions
*/

/*
** Cosinus
*/
void pe_gmath_cosinus(WrenVM *vm) {
    double x = wrenGetSlotDouble(vm, 1);
    wrenSetSlotDouble(vm, 0, cos(x));
}

/*
** Sinus
*/
void pe_gmath_sinus(WrenVM *vm) {
    double x = wrenGetSlotDouble(vm, 1);
    wrenSetSlotDouble(vm, 0, sin(x));
}

/*
** Arctan2
*/
void pe_gmath_atan2(WrenVM *vm) {
    double x = wrenGetSlotDouble(vm, 1);
    double y = wrenGetSlotDouble(vm, 2);
    wrenSetSlotDouble(vm, 0, atan2(x, y));
}

/*
** Power
*/
void pe_gmath_power(WrenVM *vm) {
    double x = wrenGetSlotDouble(vm, 1);
    double y = wrenGetSlotDouble(vm, 2);
    wrenSetSlotDouble(vm, 0, pow(x, y));
}

/*
** Square root
*/
void pe_gmath_sqrt(WrenVM *vm) {
    double x = wrenGetSlotDouble(vm, 1);
    wrenSetSlotDouble(vm, 0, sqrt(x));
}

/*
** Register functions
*/
void pe_gmath_register_functions(struct pe_engine_state *engine_state) {
    pe_add_function(&engine_state->wren_functions, "main", "Math", "cos(_)",
                    true, &pe_gmath_cosinus);
    pe_add_function(&engine_state->wren_functions, "main", "Math", "sin(_)",
                    true, &pe_gmath_sinus);
    pe_add_function(&engine_state->wren_functions, "main", "Math", "atan2(_,_)",
                    true, &pe_gmath_atan2);
    pe_add_function(&engine_state->wren_functions, "main", "Math", "pow(_,_)",
                    true, &pe_gmath_power);
    pe_add_function(&engine_state->wren_functions, "main", "Math", "sqrt(_)",
                    true, &pe_gmath_sqrt);
}
