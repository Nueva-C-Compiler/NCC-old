#include <stdio.h>
#include "vec.h"
#include "../log/src/log.h"

int main() {
    Vec test = vec_new();
    VEC_PUSH(int, &test, 32)
    printf("test[0]=%d", *VEC_AT(int, &test, 0));
    log_info("Finished.");
}
