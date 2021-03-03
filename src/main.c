#include <stdio.h>
#include <string.h>
#include <log.h>
#include "utils/vec.h"
#include "utils/hashmap.h"
#include "utils/panic.h"

int main(int argc, char** argv) {
    if (argc == 1) panic("No argument provided", BAD_INPUT);
    if (strcmp(argv[1], "vector") == 0) {
        vec_t test = vec_new(sizeof(int));
        int val1 = 32;
        vec_push(&test, &val1);
        log_debug("test[0] = %d", *(int*)vec_at(&test, 0));
        vec_shrink(&test, 3);
        log_debug("Length: %zu", vec_len(&test));
        int val2 = 32;
        vec_push(&test, &val2);
        log_debug("test[0] = %d", *(int*)vec_at(&test, 0));
        int val3 = 64;
        vec_push(&test, &val3);
        log_debug("test[1] = %d", *(int*)vec_at(&test, 1));
        
        log_debug("Length: %zu", vec_len(&test));
        
        vec_pop(&test);
        log_debug("Length: %zu", vec_len(&test));

        vec_pop(&test);
        log_debug("Length: %zu", vec_len(&test));
        
        vec_pop(&test);
        log_debug("Length: %zu", vec_len(&test));
        
        vec_pop(&test);
        log_debug("Length: %zu", vec_len(&test));
        
        int val4 = 128;
        vec_push(&test, &val4);
        log_debug("test[0] = %d", *(int*)vec_at(&test, 0));
    }
    else if (strcmp(argv[1], "hashmap") == 0) {
        size_t sz = 20;
        if (argc > 2) sz = strtol(argv[2], NULL, 10);
        hashmap_t h = hashmap_new(sizeof(int), sizeof(double));
        int keys[sz];
        for (int i = 0; i < sz; i++) {
            int key = rand() % 128;
            double val = rand();
            log_debug("Inserting pair %d %f", key, val);
            keys[i] = key;
            hashmap_set(&h, &key, &val);
        }
        for (int i = 0; i < sz; i++) {
            void* addr = hashmap_get(&h, &keys[i]);
            double val = *(double*)addr;
            log_debug("Read back pair %d %f", keys[i], val);
        }
        for (int i = 0; i < sz; i++) hashmap_del(&h, &keys[i]);
        hashmap_free(&h);
    }
    else {
        panic("Invalid argument.", BAD_INPUT);
    }
}
