
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "wren.h"

#include "random.h"
#include "log.h"
#include "engine.h"

#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"

/*
** Random number generator implementation
*/

/*
** Set the seed for the random number generator
*/
void pe_random_set_seed(WrenVM *vm) {
    uint32_t seed = (uint32_t)wrenGetSlotDouble(vm, 1);
    LOG_DEBUG("Setting seed to %d\n", seed);
    srand(seed);
}

/*
** Generate a random number between 0 and 1
*/
void pe_random_rand(WrenVM *vm) {
    double random = (double)rand() / (double)RAND_MAX;
    wrenSetSlotDouble(vm, 0, random);
}

/*
** Generate a random number between min and max
*/
void pe_random_irange(WrenVM *vm) {
    uint32_t min = (uint32_t)wrenGetSlotDouble(vm, 1);
    uint32_t max = (uint32_t)wrenGetSlotDouble(vm, 2);
    uint32_t random = (rand() % (max - min + 1)) + min;
    wrenSetSlotDouble(vm, 0, random);
}

/*
** Generate perlin noise
*/
void pe_random_perlin(WrenVM *vm) {
    float x = (float)wrenGetSlotDouble(vm, 1);
    float y = (float)wrenGetSlotDouble(vm, 2);
    float z = (float)wrenGetSlotDouble(vm, 3);
    int x_wrap = (int)wrenGetSlotDouble(vm, 4);
    int y_wrap = (int)wrenGetSlotDouble(vm, 5);
    int z_wrap = (int)wrenGetSlotDouble(vm, 6);
    int seed = (int)wrenGetSlotDouble(vm, 7);

    float out = stb_perlin_noise3_seed(x, y, z, x_wrap, y_wrap, z_wrap, seed);
    wrenSetSlotDouble(vm, 0, out);
}

/*
** Register random number generator functions
*/
void pe_random_register_functions(struct pe_engine_state *engine_state) {
    pe_add_function(&engine_state->wren_functions, "main", "Random", "seed(_)",
                    true, &pe_random_set_seed);
    pe_add_function(&engine_state->wren_functions, "main", "Random", "rand()",
                    true, &pe_random_rand);
    pe_add_function(&engine_state->wren_functions, "main", "Random",
                    "irange(_,_)", true, &pe_random_irange);
    pe_add_function(&engine_state->wren_functions, "main", "Random",
                    "perlin(_,_,_,_,_,_,_)", true, &pe_random_perlin);
}
