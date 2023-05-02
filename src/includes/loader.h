#ifndef __LOADER_H__
#define __LOADER_H__

#include <stdint.h>

#include "wren.h"
#include "engine.h"

char *pe_load_code(const char *path);

#endif /* __LOADER_H__ */
