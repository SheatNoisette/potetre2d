#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "wren.h"
#include "binding.h"
#include "engine.h"
#include "log.h"
#include "file_io.h"
#include "utils.h"

/*
** File IO for Potetre2D
*/

/*
** Create a new file instance
*/
void pe_file_io_new_file(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    const char *path = wrenGetSlotString(vm, 1);
    const char *mode = wrenGetSlotString(vm, 2);

    if (path == NULL) {
        LOG_ERROR("Trying to open a file with a NULL path\n");
        wrenSetSlotDouble(vm, 0, -1.);
        return;
    } else if (mode == NULL) {
        LOG_ERROR("Trying to open a file with a NULL mode\n");
        wrenSetSlotDouble(vm, 0, -1.);
        return;
    }

    FILE *file = fopen(path, mode);

    if (file == NULL) {
        LOG_ERROR("Failed to open file '%s' with mode '%s'\n", path, mode);
        wrenSetSlotDouble(vm, 0, -1.);
        return;
    }

    struct pe_file_vector_data *file_data =
        calloc(1, sizeof(struct pe_file_vector_data));
    CHECK_ALLOC(file_data);

    size_t path_len = strlen(path);
    file_data->file_name = calloc(path_len + 1, sizeof(char));
    CHECK_ALLOC(file_data->file_name);

    memcpy(file_data->file_name, path, path_len);
    file_data->file = file;

    // Get size of file if opened in read mode
    if (strcmp(mode, "r") == 0) {
        fseek(file, 0L, SEEK_END);
        file_data->file_size = ftell(file);
        fseek(file, 0L, SEEK_SET);
    } else {
        file_data->file_size = 0;
    }

    uint32_t file_id = pe_vector_push(engine->files, (void *)file_data);
    LOG_DEBUG("New file handle ID: %d\n", file_id);
    wrenSetSlotDouble(vm, 0, file_id);
}

/*
** Close and free a file instance
*/
void pe_file_io_close_file(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t file_id = (uint32_t)wrenGetSlotDouble(vm, 1);

    if (file_id >= engine->files->size) {
        LOG_ERROR("Trying to close a file with an invalid ID\n");
        return;
    }

    struct pe_file_vector_data *file_data =
        (struct pe_file_vector_data *)pe_vector_get(engine->files, file_id);
    if (file_data == NULL) {
        LOG_ERROR("Trying to close a NULL file\n");
        return;
    } else if (file_data->file == NULL) {
        LOG_ERROR("Trying to close a NULL file\n");
        return;
    }

    pe_vector_remove(engine->files, file_id);
}

/*
** Read a byte from a file instance
*/
void pe_file_io_read_byte(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t file_id = (uint32_t)wrenGetSlotDouble(vm, 1);

    if (file_id >= engine->files->size) {
        LOG_ERROR("Trying to read a byte from a file with an invalid ID\n");
        return;
    }

    struct pe_file_vector_data *file_data =
        (struct pe_file_vector_data *)engine->files->data[file_id];
    if (file_data == NULL) {
        LOG_ERROR("Trying to read a byte from a NULL file\n");
        return;
    } else if (file_data->file == NULL) {
        LOG_ERROR("Trying to read a byte from a NULL file\n");
        return;
    }

    char byte = fgetc(file_data->file);
    if (byte == EOF) {
        wrenSetSlotDouble(vm, 0, 0.);
        return;
    }

    wrenSetSlotDouble(vm, 0, (double)byte);
}

/*
** Get the length of a file instance
*/
void pe_file_io_length(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));

    uint32_t file_id = (uint32_t)wrenGetSlotDouble(vm, 1);

    if (file_id >= engine->files->size) {
        LOG_ERROR("Trying to get the length of a file with an invalid ID\n");
        return;
    }

    struct pe_file_vector_data *file_data =
        (struct pe_file_vector_data *)engine->files->data[file_id];
    if (file_data == NULL) {
        LOG_ERROR("Trying to get the length of a NULL file\n");
        return;
    } else if (file_data->file == NULL) {
        LOG_ERROR("Trying to get the length of a NULL file\n");
        return;
    }

    wrenSetSlotDouble(vm, 0, file_data->file_size);
}

/*
** Destroy a file instance
*/
void pe_close_destroy_file(void *data) {
    struct pe_file_vector_data *file_data = (struct pe_file_vector_data *)data;
    if (file_data == NULL) {
        LOG_ERROR("Trying to destroy a NULL file\n");
        return;
    } else if (file_data->file == NULL) {
        LOG_ERROR("Trying to destroy a NULL file\n");
        return;
    }
    free(file_data->file_name);
    fclose(file_data->file);
    free(file_data);
}

void pe_file_io_register_functions(struct pe_engine_state *engine_state) {
    pe_add_function(&engine_state->wren_functions, "main", "FileIO",
                    "internal_open(_,_)", true, &pe_file_io_new_file);
    pe_add_function(&engine_state->wren_functions, "main", "FileIO",
                    "internal_close(_)", true, &pe_file_io_close_file);
    pe_add_function(&engine_state->wren_functions, "main", "FileIO",
                    "internal_read_byte(_)", true, &pe_file_io_read_byte);
    pe_add_function(&engine_state->wren_functions, "main", "FileIO",
                    "internal_length(_)", true, &pe_file_io_length);
}