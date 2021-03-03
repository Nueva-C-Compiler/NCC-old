enum panic_type {
    UNREACHABLE_STATE,
    NULLPTR,
    BAD_INPUT,
};

/**
 * Logs error message 'what' to FATAL, exits.
 */
void _panic(const char* what, const char* where, enum panic_type type);

#define panic(what, type) _panic(what, __FILE__, type);
