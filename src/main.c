#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wren.h"

#include "log.h"
#include "engine.h"
#include "utils.h"
#include "loader.h"
#include "random.h"
#include "input.h"

int main(int argc, char *argv[]) {

    char *wren_file_content = NULL;
    int return_code = 0;
    struct pe_engine_state *pe_global_state =
        calloc(1, sizeof(struct pe_engine_state));

    // Initialize the engine
    LOG_DEBUG("Starting engine\n");
    pe_engine_init(pe_global_state);

    // Wren VM
    pe_global_state->vm = wrenNewVM(&pe_global_state->wren_config);
    wrenEnsureSlots(pe_global_state->vm, PE_WREN_SLOTS);
    wrenSetUserData(pe_global_state->vm, pe_global_state);

    // Register engine specific functions
    LOG_DEBUG("Registering engine functions...\n");
    {
        pe_engine_register_functions(pe_global_state);
        pe_random_register_functions(pe_global_state);
        pe_input_register_functions(pe_global_state);
    }

    LOG_DEBUG("Loading code...\n");
    wren_file_content = pe_load_code(argc == 1 ? NULL : argv[1]);
    LOG_DEBUG("* Code loaded!\n");

    // Load the code into the VM
    if (util_interpret_wren_output(wrenInterpret(pe_global_state->vm, "main",
                                                 wren_file_content)) != 0) {
        LOG_ERROR("Error while interpreting Game Wren file\n");
        return_code = 1;
        goto destroy;
    }
    LOG_DEBUG("* Code loaded and compiled!\n");

    LOG_DEBUG("Starting game...\n");
    pe_engine_start(pe_global_state);

    // Destroy the state
    LOG_DEBUG("Destroying engine state...\n");
    pe_engine_close(pe_global_state);
destroy:
    wrenFreeVM(pe_global_state->vm);
    free(pe_global_state);
    free(wren_file_content);

    LOG_DEBUG("Bye!\n");

    return return_code;
}
