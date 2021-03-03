#include "panic.h"
#include <log.h>
#include "stdlib.h"

void _panic(const char* what, const char* where, enum panic_type type)
{
    log_fatal("%s: Raise panic  '%s'", where, what);
    exit(1);
}
