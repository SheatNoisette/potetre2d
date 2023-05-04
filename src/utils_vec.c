#include <stdlib.h>

#include "utils.h"
#include "utils_vec.h"

/*
** Vector implementation
*/

/*
** Create a new vector
** Create a automanager vector
*/
struct pe_vector *pe_vector_new(pe_vector_free_fnc_t free_fnc) {
    struct pe_vector *vec = calloc(1, sizeof(struct pe_vector));
    CHECK_ALLOC(vec);

    vec->size = 0;
    vec->capacity = 0;
    vec->data = NULL;
    vec->free_fnc = free_fnc;
    vec->is_empty = NULL;

    return vec;
}

/*
** Destroy a vector
*/
void pe_vector_destroy(struct pe_vector *vec) {
    if (vec == NULL)
        return;

    if (vec->free_fnc != NULL)
        for (size_t i = 0; i < vec->size; i++)
            if (!vec->is_empty[i])
                vec->free_fnc(vec->data[i]);

    free(vec->data);
    free(vec);
}

/*
** Get a value from a vector (fast)
*/
inline void *pe_vector_get_fast(struct pe_vector *vec, size_t index) {
    return vec->data[index];
}

/*
** Get a value from a vector (safe)
*/
void *pe_vector_get(struct pe_vector *vec, size_t index) {
    if (index >= vec->size)
        return NULL;

    if (vec->is_empty != NULL && vec->is_empty[index])
        return NULL;

    return vec->data[index];
}

/*
** Double the capacity of the vector
*/
static void pe_vector_double_capacity(struct pe_vector *vec) {
    vec->capacity *= 2;
    vec->data = realloc(vec->data, vec->capacity * sizeof(void *));
    vec->is_empty = realloc(vec->is_empty, vec->capacity * sizeof(bool));
    CHECK_ALLOC(vec->data);
    CHECK_ALLOC(vec->is_empty);

    for (size_t i = vec->size; i < vec->capacity; i++)
        vec->is_empty[i] = true;
}

/*
** Push a value to the end of the vector
*/
size_t pe_vector_push(struct pe_vector *vec, void *value) {
    if (vec->size == vec->capacity)
        pe_vector_double_capacity(vec);

    vec->data[vec->size] = value;
    vec->is_empty[vec->size] = false;
    vec->size++;

    return vec->size - 1;
}

/*
** Insert a value at the first empty slot
*/
size_t pe_vector_insert(struct pe_vector *vec, void *value) {
    for (size_t i = 0; i < vec->size; i++) {
        if (vec->is_empty[i]) {
            vec->data[i] = value;
            vec->is_empty[i] = false;
            return i;
        }
    }

    return pe_vector_push(vec, value);
}

/*
** Remove a value from the vector froml a given index
*/
void pe_vector_remove(struct pe_vector *vec, size_t index) {
    if (index >= vec->size)
        return;

    if (vec->free_fnc != NULL)
        vec->free_fnc(vec->data[index]);

    vec->is_empty[index] = true;
}

/*
** Pop the last value from the vector
*/
void pe_vector_pop(struct pe_vector *vec) {
    if (vec->size == 0)
        return;

    if (vec->free_fnc != NULL)
        vec->free_fnc(vec->data[vec->size - 1]);

    vec->is_empty[vec->size - 1] = true;
    vec->size--;
}
