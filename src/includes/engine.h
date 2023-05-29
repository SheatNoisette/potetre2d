#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdint.h>

#include "wren.h"
#include "binding.h"
#include "tigr.h"
#include "utils_vec.h"
#include "audio.h"

// Engine version
#ifndef BUILD_ID
#define BUILD_ID "unknown"
#endif
#ifndef BUILD_NUMBER
#define BUILD_NUMBER 0
#endif

// Slots for function calls Wren
#define PE_WREN_SLOTS 6

// Default game script
#define DEFAULT_WREN_FILE "game.wren"

// OS Macros
#define OS_RETURN_CODE_NIX 0
#define OS_RETURN_CODE_MAC 1
#define OS_RETURN_CODE_WINDOWS 2
#define OS_RETURN_CODE_UNKNOWN 3

/*
** Engine state struct
*/
struct pe_engine_state {
    /* Tigr */
    Tigr *screen; /* Tigr Screen */

    /* Wren */
    WrenConfiguration wren_config; /* Wren Configuration */
    WrenVM *vm;                    /* Wren Virtual Machine */
    struct pe_wren_functions_container wren_functions; /* Wren Functions */

    /* Engine */
    uint32_t fps_limit;         /* FPS Limit */
    bool running;               /* Engine running state */
    bool headless;              /* Headless mode */
    struct pe_vector *surfaces; /* Surfaces */
    Tigr *current_surface;      /* Current surface target */
    struct pe_vector *files;    /* Files loaded externally */
    struct pe_audio *audio;     /* Audio */
};

void pe_engine_init(struct pe_engine_state *engine_state);
void pe_engine_register_functions(struct pe_engine_state *engine_state);
int pe_engine_start(struct pe_engine_state *engine_state, int argc,
                    char **argv);
void pe_engine_close(struct pe_engine_state *engine_state);

#endif /* __ENGINE_H__ */
