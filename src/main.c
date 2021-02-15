#include <stdio.h>
#include "vec.h"

int main() {
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
}
