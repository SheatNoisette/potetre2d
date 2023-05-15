#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wren.h"
#include "log.h"

/*
** Read a file and return a string
*/
char *util_read_file(const char *path) {

    FILE *file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, "Could not open file '%s'\n", path);
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    if (!buffer) {
        fprintf(stderr, "Could not allocate memory for file '%s'\n", path);
        exit(1);
    }

    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if (bytes_read < file_size) {
        fprintf(stderr, "Could not read file '%s'\n", path);
        exit(1);
    }

    buffer[bytes_read] = '\0';

    fclose(file);

    return buffer;
}

/*
** Check if a file exists
*/
bool util_file_exists(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        return false;
    }

    fclose(file);
    return true;
}

/*
** Get file length
*/
size_t util_file_length(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        return 0;
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    fclose(file);

    return file_size;
}

/*
** Interpret Wren output
*/
int util_interpret_wren_output(WrenInterpretResult result) {
    switch (result) {
        case WREN_RESULT_COMPILE_ERROR:
            LOG_ERROR("Wren - Compile Error!\n");
            return 1;
            break;
        case WREN_RESULT_RUNTIME_ERROR:
            LOG_ERROR("Wren - Runtime Error!\n");
            return 1;
            break;
        case WREN_RESULT_SUCCESS:
            LOG_DEBUG("Wren - Success!\n");
            break;
    }

    return 0;
}
