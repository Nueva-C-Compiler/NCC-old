#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct Vec
{
    void* buffer;
    size_t len;
    size_t cap;
} Vec;

/**
 * Creates a new vector with length `0`. Nothing is allocated at this stage.
 */
Vec vec_new();

/**
 * Grows the a vector by the specified byte count.
 * @returns whether or not the vector was successfully resized.
 */
bool vec_grow(Vec* self, size_t bytes);

/**
 * Shrink the a vector by the specified byte count.
 */
void vec_shrink(Vec* self, size_t bytes);

/**
 * Returns a raw pointer to the start of the vector's backing memory. Only bytes `0 .. length` (exclusive upper bound) are
 * valid. The pointer may be `NULL` if the length of the vector is zero.
 * This pointer can be cast to an array of elements.
 */
void* vec_raw(Vec* self);

/**
 * Returns the length of the vector in elements given the size of an element in bytes.
 */
size_t vec_len(Vec* self, size_t elem_size);

/**
 * Frees a vector's backing memory. It is undefined behavior to reuse a freed vector.
 */
void vec_free(Vec* self);

#define VEC_GROW(T, p_self, count) vec_grow(p_self, sizeof(T) * count)
#define VEC_SHRINK(T, p_self, count) vec_shrink(p_self, sizeof(T) * count)
#define VEC_LEN(T, p_self) vec_len(p_self, sizeof(T))
#define VEC_AT(T, p_self, index) &(((T*) vec_raw(p_self))[index])

// TODO: Propagate OOM instead of panicking.
#define VEC_PUSH(T, p_self, value) do {                                   \
    struct Vec* __vec_push_self = p_self;                                 \
    if (!VEC_GROW(T, __vec_push_self, 1)) {                               \
        exit(EXIT_FAILURE);                                               \
    }                                                                     \
    *VEC_AT(T, __vec_push_self, VEC_LEN(T, __vec_push_self) - 1) = value; \
} while (false)
#define VEC_POP(T, p_self) VEC_SHRINK(T, p_self, 1)
