#include "vec.h"
#include <stdlib.h>
#include <stddef.h>

struct Vec vec_new() {
    struct Vec vec = {
            .buffer = NULL,
            .len = 0,
            .cap = 0,
    };
    return vec;
}

bool vec_grow(struct Vec* self, size_t bytes) {
    size_t new_len = self->len + bytes;

    if (self->cap <= new_len) {
        // Find a suitable capacity
        size_t new_cap = max(32, self->cap);
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

void* vec_raw(struct Vec* self) {
    return self->buffer;
}

size_t vec_len(struct Vec* self, size_t elem_size) {
    return self->len / elem_size;
}

void vec_free(struct Vec* self) {
    // NOTE: `free` is NOOP for `NULL` pointers.
    free(self->buffer);
}
