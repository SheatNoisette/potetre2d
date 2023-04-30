#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mujs.h"
#include "fenster.h"

#include "engine.h"
#include "log.h"

// Engine state
extern struct pe_engine_state *pe_global_state;

/*
** Put a pixel on the screen
*/
static void pe_engine_put_pixel(js_State *J) {
    int x = js_tointeger(J, 1);
    int y = js_tointeger(J, 2);
    int r = js_tointeger(J, 3) & 0xFF;
    int g = js_tointeger(J, 4) & 0xFF;
    int b = js_tointeger(J, 5) & 0xFF;

    LOG_DEBUG("Put pixel at %d, %d with color %d, %d, %d\n", x, y, r, g, b);

    pe_global_state->window_buffer[y * ((struct fenster *)pe_global_state->fenster_state)->width + x] = r << 16 | g << 8 | b;

    js_pushundefined(J);
}


/*
** Clear the screen
*/
static void pe_engine_clear_screen(js_State *J) {
    int r = js_tointeger(J, 1) & 0xFF;
    int g = js_tointeger(J, 2) & 0xFF;
    int b = js_tointeger(J, 3) & 0xFF;

    memset(pe_global_state->window_buffer, r << 16 | g << 8 | b, ((struct fenster *)pe_global_state->fenster_state)->width * ((struct fenster *)pe_global_state->fenster_state)->height * sizeof(uint32_t));

    js_pushundefined(J);
}

/*
** Init the engine
*/
static void pe_engine_init(js_State *J) {
    int width = js_tointeger(J, 1);
    int height = js_tointeger(J, 2);
    const char *title = js_tostring(J, 3);
    int target_fps = js_tointeger(J, 4);

    LOG_DEBUG("Init engine with width %d, height %d, title %s, target_fps %d\n", width, height, title, target_fps);

    // Init the engine state - Bypass const warning
    pe_global_state->fenster_state = malloc(sizeof(struct fenster));
    pe_global_state->window_buffer = calloc(width * height, sizeof(uint32_t));

    size_t title_size = strlen(title);
    char *title_copy = calloc(title_size + 1, sizeof(char));
    memcpy(title_copy, title, title_size + 1);

    struct fenster f = {
        .width = width,
        .height = height,
        .title = title,
        .buf = pe_global_state->window_buffer
    };
    memcpy(pe_global_state->fenster_state, &f, sizeof(struct fenster));
    
    // Init the window
    fenster_open((struct fenster *)pe_global_state->fenster_state);

    js_pushundefined(J);
}

/*
** Register engine specific functions
** Engine.* functions
*/
void pe_engine_register_functions(struct pe_engine_state *engine_state) {
    LOG_DEBUG("* Registering engine functions...\n");

    js_newcfunction(engine_state->js, pe_engine_put_pixel, "pg_set_pixel", 5);
    js_setglobal(engine_state->js, "pg_set_pixel");

    js_newcfunction(engine_state->js, pe_engine_clear_screen, "pg_clear_screen", 3);
    js_setglobal(engine_state->js, "pg_clear_screen");

    js_newcfunction(engine_state->js, pe_engine_init, "pg_init", 4);
    js_setglobal(engine_state->js, "pg_init");
}

/*
** Render loop
*/
void pe_engine_update(struct pe_engine_state *engine_state) {
    while (fenster_loop((struct fenster *)engine_state->fenster_state) == 0) {
        // Call the update js function
        js_getglobal(pe_global_state->js, "update");
        js_pushnull(pe_global_state->js);
        if (js_pcall(pe_global_state->js, 0)) {
            LOG_ERROR("Error while calling update function\n");
            LOG_ERROR("%s\n", js_trystring(pe_global_state->js, -1, "Error"));
        }
    }
}

/*
** Destroy the engine
*/
void pe_engine_close(struct pe_engine_state *engine_state) {
    LOG_DEBUG("* Closing engine...\n");
    fenster_close((struct fenster *)engine_state->fenster_state);
    free(engine_state->fenster_state);
    free(engine_state->window_buffer);
}
