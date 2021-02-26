enum panic_type {
    UNREACHABLE_STATE,
    NULLPTR,
};
void panic(const char* what, enum panic_type type);
