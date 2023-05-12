#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tigr.h"

#include "engine.h"
#include "log.h"
#include "utils.h"
#include "utils_vec.h"
#include "surface.h"
#include "file_io.h"

/*
** Write to the console
*/
static void wren_write_fn(WrenVM *vm, const char *text) {
    (void)vm;
    LOG_INFO("%s", text);
}

/*
** Error handling
*/
void wren_error_fn(WrenVM *vm, WrenErrorType errorType, const char *module,
                   const int line, const char *msg) {
    (void)vm;
    switch (errorType) {
    case WREN_ERROR_COMPILE:
        printf("[%s line %d] [Error] %s\n", module, line, msg);
        break;
    case WREN_ERROR_STACK_TRACE:
        printf("[%s line %d] in %s\n", module, line, msg);
        break;
    case WREN_ERROR_RUNTIME:
        printf("[Runtime Error] %s\n", msg);
        struct pe_engine_state *engine =
            ((struct pe_engine_state *)wrenGetUserData(vm));
        engine->running = false;
        break;
    }
}

/*
** Wren method binding
*/
WrenForeignMethodFn bindForeignMethod(WrenVM *vm, const char *module,
                                      const char *className, bool isStatic,
                                      const char *signature) {
    (void)isStatic;
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    LOG_DEBUG("Finding method '%s' in class '%s' in module '%s'...\n",
              signature, className, module);

    // Find the function
    pe_wren_function_t fnc =
        pe_find_function(&engine->wren_functions, module, className, signature);

    // If the function is not found, error out
    if (fnc == NULL) {
        LOG_ERROR("Function '%s' not found\n", signature);
        return NULL;
    }

    // Return the function
    return fnc;
}

/*
** Initialize the engine state
** Callback
*/
static void pe_engine_init_state(WrenVM *vm) {
    double width = (uint32_t)wrenGetSlotDouble(vm, 1);
    double height = (uint32_t)wrenGetSlotDouble(vm, 2);
    char *title = (char *)wrenGetSlotString(vm, 3);

    // Init the engine state - Bypass const warning
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    engine->screen = tigrWindow((int)width, (int)height, title, 0);
    engine->current_surface = engine->screen;
}

/*
** Initialize the engine configuration
*/
void pe_engine_init(struct pe_engine_state *engine_state) {

    // Configure the wren VM
    wrenInitConfiguration(&engine_state->wren_config);
    engine_state->wren_config.writeFn = &wren_write_fn;
    engine_state->wren_config.errorFn = &wren_error_fn;
    engine_state->wren_config.bindForeignMethodFn = &bindForeignMethod;

    // Wren functions container
    engine_state->wren_functions.functions =
        calloc(1, sizeof(struct pe_wren_function));
    engine_state->wren_functions.length = 0;
    engine_state->wren_functions.capacity = 1;

    // Engine status
    engine_state->running = true;
    engine_state->surfaces = pe_vector_new(&pe_destroy_surface_engine);
    engine_state->current_surface = NULL;
    engine_state->files = pe_vector_new(&pe_close_destroy_file);
}

/*
** Exit cleanly from Wren
*/
void pe_engine_wren_destroy(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));
    engine->running = false;
}

/*
** Register engine specific functions
*/
void pe_engine_register_functions(struct pe_engine_state *engine_state) {
    pe_add_function(&engine_state->wren_functions, "main", "Engine",
                    "init(_,_,_)", true, &pe_engine_init_state);

    pe_add_function(&engine_state->wren_functions, "main", "Engine",
                    "destroy()", true, &pe_engine_wren_destroy);
}

/*
** Render loop
*/
void pe_engine_start(struct pe_engine_state *engine_state) {
    WrenHandle *game_class;
    WrenHandle *game_init;
    WrenHandle *game_update;

    // Get the handle to the main class
    wrenEnsureSlots(engine_state->vm, 1);
    wrenGetVariable(engine_state->vm, "main", "Game", 0);
    game_class = wrenGetSlotHandle(engine_state->vm, 0);
    game_init = wrenMakeCallHandle(engine_state->vm, "init()");

    // Call the init function
    wrenCall(engine_state->vm, game_init);

    wrenEnsureSlots(engine_state->vm, 1);
    wrenSetSlotHandle(engine_state->vm, 0, game_class);
    game_update = wrenMakeCallHandle(engine_state->vm, "tick()");

    while (engine_state->running && (!tigrClosed(engine_state->screen))) {
        // Call the update function
        wrenEnsureSlots(engine_state->vm, 1);
        wrenSetSlotHandle(engine_state->vm, 0, game_class);
        wrenCall(engine_state->vm, game_update);
        tigrUpdate(engine_state->screen);
    }

    // Free the handles
    wrenReleaseHandle(engine_state->vm, game_class);
    wrenReleaseHandle(engine_state->vm, game_init);
    wrenReleaseHandle(engine_state->vm, game_update);
}

/*
** Destroy the engine
*/
void pe_engine_close(struct pe_engine_state *engine_state) {
    LOG_DEBUG("* Closing engine...\n");
    pe_free_functions_container(&engine_state->wren_functions);
    tigrFree(engine_state->screen);
    pe_vector_destroy(engine_state->surfaces);
}
