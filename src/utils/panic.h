enum panic_type {
    UNREACHABLE_STATE,
    NULLPTR,
};

/**
 * Logs error message 'what' to FATAL, exits.
 */
void panic(const char* what, const char* where, enum panic_type type);
