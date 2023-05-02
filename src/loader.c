#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "generated/engine_std.h"

#include "loader.h"
#include "log.h"
#include "utils.h"

/*
** Code loading
*/
char *pe_load_code(const char *path) {
    char *wren_file_content = NULL;
    char *final_content = NULL;

    // Load a Wren file from the disk (or use default)
    if (path == NULL) {
        LOG_DEBUG("Loading default Wren file '%s'\n", DEFAULT_WREN_FILE);
        wren_file_content = util_read_file(DEFAULT_WREN_FILE);
    } else {
        LOG_DEBUG("Loading Wren file '%s'\n", path);
        wren_file_content = util_read_file(path);
    }

    // Add stdlib
    final_content =
        malloc((strlen(wren_file_content) + ENGINE_STD_DATA_LENGTH + 1) *
               sizeof(char));
    CHECK_ALLOC(final_content);

    // Concatenate the stdlib and the Wren file
    memcpy(final_content, engine_std_exported, ENGINE_STD_DATA_LENGTH);
    memcpy(final_content + ENGINE_STD_DATA_LENGTH, wren_file_content,
           strlen(wren_file_content));

    // Destroy the Wren file content and return the final content
    free(wren_file_content);

    return final_content;
}
