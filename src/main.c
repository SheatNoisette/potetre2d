#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mujs.h"

#include "log.h"
#include "engine.h"

#define DEFAULT_JS_FILE "game.js"

// Main engine state - We're working with callbacks, so we need to keep
// track of the state of the engine.
struct pe_engine_state *pe_global_state = NULL;

int main(int argc, char *argv[]) {

    LOG_DEBUG("Starting engine\n");

    // Engine state
    pe_global_state = calloc(1, sizeof(struct pe_engine_state));

    // New state
    pe_global_state->js = js_newstate(NULL, NULL, JS_STRICT);

    // Load a JS file from the disk (or use default)
    if (argc > 1) {
        LOG_DEBUG("Loading JS file %s\n", argv[1]);
        js_dofile(pe_global_state->js, argv[1]);
    } else {
        LOG_DEBUG("Loading default JS file %s\n", DEFAULT_JS_FILE);
        js_dofile(pe_global_state->js, DEFAULT_JS_FILE);
    }

    // Register engine specific functions
    LOG_DEBUG("Registering engine functions...\n");
    pe_engine_register_functions(pe_global_state);

    LOG_DEBUG("Starting game...\n");
    // Call the init function
    js_getglobal(pe_global_state->js, "init");
    js_pushnull(pe_global_state->js); /* As this.* */
    if (js_pcall(pe_global_state->js, 0)) {
        LOG_ERROR("Error calling init function: %s\n", js_trystring(pe_global_state->js, -1, NULL));
        return 1;
    }

    LOG_DEBUG("Starting main loop...\n");
    pe_engine_update(pe_global_state);

    // Destroy the state
    LOG_DEBUG("Destroying engine state...\n");
    pe_engine_close(pe_global_state);
    js_gc(pe_global_state->js, 0);
    js_freestate(pe_global_state->js);
    free(pe_global_state);

    return 0;
}
