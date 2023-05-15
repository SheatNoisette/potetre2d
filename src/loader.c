#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "generated/engine_std.h"
#include "pithy.h"

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
        wren_file_content = find_and_load_decompress_file(DEFAULT_WREN_FILE);
    } else {
        LOG_DEBUG("Loading Wren file '%s'\n", path);
        wren_file_content = find_and_load_decompress_file(path);
    }

    // Add stdlib
    final_content = calloc(
        sizeof(char), (strlen(wren_file_content) + ENGINE_STD_DATA_LENGTH + 1));
    CHECK_ALLOC(final_content);

    // Concatenate the stdlib and the Wren file
    memcpy(final_content, engine_std_exported, ENGINE_STD_DATA_LENGTH);
    memcpy(final_content + ENGINE_STD_DATA_LENGTH, wren_file_content,
           strlen(wren_file_content));

    // Destroy the Wren file content and return the final content
    free(wren_file_content);

    return final_content;
}

/*
** Find a file from the path and check if the prefix '_' is present
** If it is, load the file and return the decompressed content
*/
char *find_and_load_decompress_file(const char *path) {
    size_t path_length = strlen(path);
    char *file_content = NULL;

    if (path_length == 0)
        return NULL;

    // Compressed file name (with '_' prefix and '\0')
    char *compressed_file_name = malloc(sizeof(char) * (path_length + 2));
    CHECK_ALLOC(compressed_file_name);
    memset(compressed_file_name, 0, path_length + 2);
    compressed_file_name[0] = '_';
    memcpy(compressed_file_name + 1, path, path_length);

    // Check if a compressed file exists
    LOG_DEBUG("* Looking for compressed file '%s'...\n", compressed_file_name);
    if (util_file_exists(compressed_file_name) == true) {
        LOG_DEBUG(" - Found compressed file '%s'!\n", compressed_file_name);

        file_content = util_read_file(compressed_file_name);
        size_t compressed_file_size = util_file_length(compressed_file_name);

        LOG_DEBUG(" - File read! Decompressing file '%s'...\n",
                  compressed_file_name);

        // Decompress the file {
        size_t output_size = 0;
        char *decompressed_file_content = NULL;

        pithy_GetDecompressedLength(file_content, compressed_file_size,
                                    &output_size);

        decompressed_file_content = calloc(sizeof(char), output_size);
        CHECK_ALLOC(decompressed_file_content);

        pithy_Decompress(file_content, compressed_file_size,
                         decompressed_file_content, output_size);
        // }

        // Compressed file content is no longer needed
        LOG_DEBUG(" - File unpacked! File size: %lu from %lu (ratio: %lu)\n",
                  output_size, compressed_file_size,
                  compressed_file_size * 100 / output_size);

        free(file_content);
        file_content = decompressed_file_content;
    } else {
        LOG_DEBUG(" - Compressed file not found, using '%s' instead\n", path);
        file_content = util_read_file(path);
    }

    free(compressed_file_name);
    return file_content;
}
