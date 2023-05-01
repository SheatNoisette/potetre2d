#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdint.h>

#include "wren.h"
#include "binding.h"

// Slots for function calls Wren
#define PE_WREN_SLOTS 6

/*
** Engine state struct
*/
struct pe_engine_state {
    /* Fenster */
    void *fenster_state; /* Fenster State */

    /* Wren */
    WrenConfiguration wren_config; /* Wren Configuration */
    WrenVM *vm; /* Wren Virtual Machine */
    struct pe_wren_functions_container wren_functions; /* Wren Functions */

    /* Engine */
    uint32_t fps_limit; /* FPS Limit */
    uint32_t *window_buffer; /* Pointer to the window buffer */
};

void pe_engine_init(struct pe_engine_state *engine_state);
void pe_engine_register_functions(struct pe_engine_state *engine_state);
void pe_engine_update(struct pe_engine_state *engine_state);
void pe_engine_close(struct pe_engine_state *engine_state);

#endif /* __ENGINE_H__ */
