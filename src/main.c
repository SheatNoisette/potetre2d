#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wren.h"

#include "log.h"
#include "engine.h"
#include "utils.h"

#define DEFAULT_WREN_FILE "game.wren"

// Main engine state - We're working with callbacks, so we need to keep
// track of the state of the engine.
struct pe_engine_state *pe_global_state = NULL;

int main(int argc, char *argv[]) {

    char *wren_file_content = NULL;
    int return_code = 0;

    // Engine state
    pe_global_state = calloc(1, sizeof(struct pe_engine_state));


    // Load a Wren file from the disk (or use default)
    if (argc > 1) {
        LOG_DEBUG("Loading Wren file '%s'\n", argv[1]);
        wren_file_content = util_read_file(argv[1]);
    } else {
        LOG_DEBUG("Loading default Wren file '%s'\n", DEFAULT_WREN_FILE);
        wren_file_content = util_read_file(DEFAULT_WREN_FILE);
    }

    // Initialize the engine
    LOG_DEBUG("Starting engine\n");
    pe_engine_init(pe_global_state);

    // Wren VM
    pe_global_state->vm = wrenNewVM(&pe_global_state->wren_config);
    wrenEnsureSlots(pe_global_state->vm, PE_WREN_SLOTS);

    // Register engine specific functions
    LOG_DEBUG("Registering engine functions...\n");
    pe_engine_register_functions(pe_global_state);

    LOG_DEBUG("Starting game...\n");
    // Call the init function
    WrenInterpretResult result = wrenInterpret(pe_global_state->vm, "main", wren_file_content);
    if (util_interpret_wren_output(result) != 0) {
        LOG_ERROR("Error while interpreting Wren file\n");
        return_code = 1;
        goto destroy;
    }

    LOG_DEBUG("Starting main loop...\n");
    pe_engine_update(pe_global_state);

    // Destroy the state
    LOG_DEBUG("Destroying engine state...\n");
destroy:
    wrenFreeVM(pe_global_state->vm);
    free(pe_global_state);
    free(wren_file_content);

    return return_code;
}
