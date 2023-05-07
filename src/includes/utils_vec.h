#ifndef __UTILS_VEC_H__
#define __UTILS_VEC_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Free function used to free a element in the vector
typedef void (*pe_vector_free_fnc_t)(void *);

struct pe_vector {
    size_t size;
    size_t capacity;

    bool *is_empty; /* For sparse vectors */
    void **data;  /* Content */
    void (*free_fnc)(void *);
};


struct pe_vector *pe_vector_new(pe_vector_free_fnc_t free_fnc);
void pe_vector_destroy(struct pe_vector *vec);
void *pe_vector_get_fast(struct pe_vector *vec, size_t index);
void *pe_vector_get(struct pe_vector *vec, size_t index);
size_t pe_vector_push(struct pe_vector *vec, void *value);
size_t pe_vector_insert(struct pe_vector *vec, void *value);
void pe_vector_remove(struct pe_vector *vec, size_t index);
void pe_vector_pop(struct pe_vector *vec);

#endif /* __UTILS_VEC_H__ */
