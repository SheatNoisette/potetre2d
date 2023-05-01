#ifndef __BINDING_H__
#define __BINDING_H__

#include <stdint.h>

#include "wren.h"

// Wren function typedef
typedef void (*pe_wren_function_t)(WrenVM *vm);

/*
** Function description struct
*/
struct pe_wren_function {
    char *wren_module;
    char *name;
    char *signature;
    bool is_static;
    pe_wren_function_t function;
};

/*
** Function container
*/
struct pe_wren_functions_container {
    size_t length;
    size_t capacity;

    struct pe_wren_function *functions;
};

void pe_add_function(struct pe_wren_functions_container *cnt,
                     const char *wren_module, const char *name,
                     const char *signature, bool is_static,
                     pe_wren_function_t function);
pe_wren_function_t pe_find_function(struct pe_wren_functions_container *cnt,
                                    const char *wren_module, const char *name,
                                    const char *signature);
#endif /* __BINDING_H__ */
