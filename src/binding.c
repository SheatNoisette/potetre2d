#include <stdlib.h>
#include <string.h>

#include "binding.h"
#include "utils.h"

/*
** Wren function binder
*/

/*
** Add a function to the Wren VM
*/
void pe_add_function(struct pe_wren_functions_container *cnt,
                     const char *wren_module, const char *name,
                     const char *signature, bool is_static,
                     pe_wren_function_t function) {

    if (cnt->length == cnt->capacity || cnt->length == 0) {
        cnt->capacity *= 2;
        cnt->functions = realloc(
            cnt->functions, cnt->capacity * sizeof(struct pe_wren_function));
    }

    // Copy the strings - This should be better
    cnt->functions[cnt->length].wren_module = malloc(strlen(wren_module) + 1);
    CHECK_ALLOC(cnt->functions[cnt->length].wren_module);
    strcpy(cnt->functions[cnt->length].wren_module, wren_module);

    cnt->functions[cnt->length].name = malloc(strlen(name) + 1);
    CHECK_ALLOC(cnt->functions[cnt->length].name);
    strcpy(cnt->functions[cnt->length].name, name);

    cnt->functions[cnt->length].signature = malloc(strlen(signature) + 1);
    CHECK_ALLOC(cnt->functions[cnt->length].signature);
    strcpy(cnt->functions[cnt->length].signature, signature);

    cnt->functions[cnt->length].function = function;
    cnt->functions[cnt->length].is_static = is_static;

    cnt->length++;
}

/*
** Find a function into the container
** Return the function pointer if found, NULL otherwise
**
** Please note that Wren caches the function pointer, so we don't need to
** make a complete lookup every time we call a function.
*/
pe_wren_function_t pe_find_function(struct pe_wren_functions_container *cnt,
                                    const char *wren_module, const char *name,
                                    const char *signature) {
    for (size_t i = 0; i < cnt->length; i++) {
        if (strcmp(cnt->functions[i].wren_module, wren_module) == 0 &&
            strcmp(cnt->functions[i].name, name) == 0 &&
            strcmp(cnt->functions[i].signature, signature) == 0) {
            return cnt->functions[i].function;
        }
    }

    return NULL;
}
