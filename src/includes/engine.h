#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "mujs.h"

#include <stdint.h>

struct pe_engine_state {
    void *fenster_state; /* Fenster State */
    js_State *js; /* Main JS Context */

    uint32_t fps_limit; /* FPS Limit */
    uint32_t *window_buffer; /* Pointer to the window buffer */
};

void pe_engine_register_functions(struct pe_engine_state *engine_state);
void pe_engine_update(struct pe_engine_state *engine_state);
void pe_engine_close(struct pe_engine_state *engine_state);

#endif /* __ENGINE_H__ */
