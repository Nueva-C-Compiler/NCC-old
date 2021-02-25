#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct vec_t
{
    void* buffer;
    size_t len;
    size_t cap;
    size_t elem_sz;
} vec_t;

/**
 * Creates a new vector with length `0`. Nothing is allocated at this stage.
 */
vec_t vec_new();

/**
 * Grows the a vector by the specified byte count.
 * @returns whether or not the vector was successfully resized.
 */
bool vec_grow(vec_t* self, size_t count);

/**
 * Shrink the a vector by the specified byte count.
 */
void vec_shrink(vec_t* self, size_t count);

/**
 * Returns a raw pointer to the start of the vector's backing memory. Only bytes `0 .. length` (exclusive upper bound) are
 * valid. The pointer may be `NULL` if the length of the vector is zero.
 * This pointer can be cast to an array of elements.
 */
void* vec_raw(vec_t* self);

/**
 * Returns the length of the vector in elements given the size of an element in bytes.
 */
size_t vec_len(vec_t* self);

/**
 * Frees a vector's backing memory. It is undefined behavior to reuse a freed vector.
 */
void vec_free(vec_t* self);

/**
 * Return pointer to vector element. It is undefined behavior to read past the allocated length.
 */
void* vec_at(vec_t* self, size_t index);

/**
 * Push a value to the end of the vector. TODO Propagate OOM error.
 */
void vec_push(vec_t* self, void* value);

#define vec_pop(p_self) vec_shrink(p_self, 1)
