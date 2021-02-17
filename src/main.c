#include <stdio.h>
#include "vec.h"
#include "hashmap.c"

int main() {
    /* exit(1); */
    Vec test = vec_new();
    VEC_PUSH(int, &test, 32);
    printf("test[0] = %d\n", *VEC_AT(int, &test, 0));

    VEC_SHRINK(int, &test, 3);
    printf("Length: %d\n", VEC_LEN(int, &test));

    VEC_PUSH(int, &test, 32);
    printf("test[0] = %d\n", *VEC_AT(int, &test, 0));

    VEC_PUSH(int, &test, 64);
    printf("test[1] = %d\n", *VEC_AT(int, &test, 1));

    printf("Length: %d\n", VEC_LEN(int, &test));

    VEC_POP(int, &test);
    printf("Length: %d\n", VEC_LEN(int, &test));

    VEC_POP(int, &test);
    printf("Length: %d\n", VEC_LEN(int, &test));

    VEC_POP(int, &test);
    printf("Length: %d\n", VEC_LEN(int, &test));

    VEC_POP(int, &test);
    printf("Length: %d\n", VEC_LEN(int, &test));

    VEC_PUSH(int, &test, 128);
    printf("test[0] = %d\n", *VEC_AT(int, &test, 0));

    hashmap_t h;
    typedef struct abc {int x; int y;} abc;
    hashmap_cons(&h, int, abc, 10, 0.5);
    for (int i = 0; i < 100; i++) {
        abc temp = {.x = i, .y = i+1};
        hashmap_ins(int, abc, &h, i, temp);
    }
    for (int i = 0; i < 100; i++) {
        printf("%d %d\n", hashmap_get(abc, &h, i).x, hashmap_get(abc, &h, i).y);
    }
}
