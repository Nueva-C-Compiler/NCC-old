#include "panic.h"
#include <log.h>
#include "stdlib.h"

void panic(const char* what, enum panic_type type)
{
    log_fatal("Panic: '%s'", what);
    exit(1);
}
