#include "vec.h"
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

struct vec_t vec_new(size_t elem_size) {
    struct vec_t vec = {
            .buffer = NULL,
            .len = 0,
            .cap = 0,
            .elem_sz = elem_size,
    };
    return vec;
}

bool vec_grow(vec_t* self, size_t count) {
    size_t new_len = self->len + (count * self->elem_sz);

    if (self->cap <= new_len) {
        // Find a suitable capacity
        size_t new_cap = fmax(32, self->cap);
        do {
            if (new_cap >= SIZE_MAX / 2)
                return false;  // Fail on overflow

            new_cap *= 2;
        } while (new_cap <= new_len);

        // Reallocate the buffer
        // NOTE: `realloc` on `NULL` works as `malloc`
        void* buffer = realloc(self->buffer, new_cap);
        if (buffer == NULL) {
            return false;
        }

        self->buffer = buffer;
        self->cap = new_cap;
    }

    self->len = new_len;

    return true;
}

void vec_shrink(vec_t* self, size_t count) {
    self->len -= fmin((count * self->elem_sz), self->len);

    if (self->len == 0) {
        // NOTE: `free` is NOOP for `NULL` pointers.
        free(self->buffer);
        self->buffer = NULL;
        self->cap = 0;
    } else if (self->len < self->cap / 2) {
        self->cap /= 2;

        void* buffer = realloc(self->buffer, self->cap);
        if (buffer != NULL) {
            // If `NULL` is returned, the old buffer is not deallocated.
            self->buffer = buffer;
        }
    }
}

void* vec_raw(vec_t* self) {
    return self->buffer;
}

size_t vec_len(vec_t* self) {
    return self->len / self->elem_sz;
}

void* vec_at(vec_t* self, size_t index)
{
    return vec_raw(self) + (index * self->elem_sz);
}

bool vec_push(vec_t* self, void* value) {
    do {
        if (!vec_grow(self, 1)) {
            return false;
        }
        memcpy(vec_at(self, vec_len(self) - 1), value, self->elem_sz);
    } while (false);
    return true;
}


void vec_pop(vec_t* self) {
    vec_shrink(self, 1 * self->elem_sz);
}

void vec_free(vec_t* self) {
    // NOTE: `free` is NOOP for `NULL` pointers.
    free(self->buffer);
}
