#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>

#include "wren.h"
#include "log.h"

#define CHECK_ALLOC(ptr)                                                       \
    if (ptr == NULL) {                                                         \
        LOG_ERROR("Failed to allocate memory\n");                              \
        exit(1);                                                               \
    }

char *util_read_file(const char *path);
bool util_file_exists(const char *path);
size_t util_file_length(const char *path);
int util_interpret_wren_output(WrenInterpretResult result);

#endif /* __UTILS_H__ */
