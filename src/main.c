#include <stdio.h>
#include <log.h>
#include "utils/vec.h"
#include "utils/hashmap.h"

int main() {
    Vec test = vec_new();
    VEC_PUSH(int, &test, 32);
    log_debug("test[0] = %d", *VEC_AT(int, &test, 0));

    VEC_SHRINK(int, &test, 3);
    log_debug("Length: %zu", VEC_LEN(int, &test));

    VEC_PUSH(int, &test, 32);
    log_debug("test[0] = %d", *VEC_AT(int, &test, 0));

    VEC_PUSH(int, &test, 64);
    log_debug("test[1] = %d", *VEC_AT(int, &test, 1));

    log_debug("Length: %zu", VEC_LEN(int, &test));

    VEC_POP(int, &test);
    log_debug("Length: %zu", VEC_LEN(int, &test));

    VEC_POP(int, &test);
    log_debug("Length: %zu", VEC_LEN(int, &test));

    VEC_POP(int, &test);
    log_debug("Length: %zu", VEC_LEN(int, &test));

    VEC_POP(int, &test);
    log_debug("Length: %zu", VEC_LEN(int, &test));

    VEC_PUSH(int, &test, 128);
    log_debug("test[0] = %d", *VEC_AT(int, &test, 0));

    hashmap_t h;
    hashmap_init(&h, sizeof(int), sizeof(double));
    int keys[20];
    for (int i = 0; i < 20; i++) {
        int key = rand() % 128;
        double val = rand();
        log_debug("Inserting pair %d %f", key, val);
        keys[i] = key;
        hashmap_set(&h, &key, &val);
    }
    for (int i = 0; i < 20; i++) {
        void* addr = hashmap_get(&h, &keys[i]);
        double val = *(double*)addr;
        log_debug("Read back pair %d %f", keys[i], val);
    }
}
