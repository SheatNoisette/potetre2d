#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wren.h"

#include "log.h"
#include "engine.h"
#include "loader.h"
#include "utils.h"

int main(int argc, char *argv[]) {

    char *wren_file_content = NULL;
    struct pe_engine_state *engine_state = NULL;
    int return_code = 0;

    // Tell engine version
    LOG_DEBUG("Potetre2D Engine %s (build %d)\n", BUILD_ID, BUILD_NUMBER);

    // Initialize the engine
    LOG_DEBUG("Starting engine...\n");
    // Initialize the engine state
    engine_state = pe_engine_init();
    if (engine_state == NULL) {
        LOG_ERROR("Error while initializing engine\n");
        return EXIT_FAILURE;
    }

    LOG_DEBUG("Loading code...\n");
    wren_file_content = pe_load_code(argc == 1 ? NULL : argv[1]);
    LOG_DEBUG("* Code loaded!\n");

    // Load the code into the VM
    if (util_interpret_wren_output(
            wrenInterpret(engine_state->vm, "main", wren_file_content)) != 0) {
        LOG_ERROR("Error while interpreting Game Wren file\n");
        return_code = 1;
        goto destroy;
    }
    LOG_DEBUG("* Code loaded and compiled!\n");

    LOG_DEBUG("Starting game...\n");
    return_code = pe_engine_start(engine_state, argc, argv);

    // Destroy the state
    LOG_DEBUG("Destroying engine state...\n");
    pe_engine_close(engine_state);

destroy:
    free(wren_file_content);

    LOG_DEBUG("Bye!\n");

    return return_code;
}
