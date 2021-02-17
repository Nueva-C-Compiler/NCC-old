#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <log.h>

// djb2 algorithm
static size_t hash_str(const char* str)
{
    size_t hash = 5381;
    int c;
    // equivalent to hash * 33 + c
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

int _exit_fatal(const char* what)
{
    log_fatal(what);
    exit(1);
    return 1;
}

#define hash(x) _Generic((x), int: (size_t) x,                          \
                         uint64_t: (size_t) x % UINT32_MAX,             \
                         uint32_t: x,                                   \
                         uint16_t: x,                                   \
                         uint8_t: x,                                    \
                         const char*: hash_str,                         \
                         default: _exit_fatal("Invalid type passed to hash(). Please supply your own hash function instead."))

typedef struct hashmap {
    const char* __ktype;
    const char* __vtype;
    size_t k_sz;
    size_t v_sz;
    void* keys;
    void* vals;
    size_t len;
    size_t filled;
    float max_load;
} hashmap_t;

static void _hashmap_cons(hashmap_t* h, const char* ktype, const char* vtype, size_t key_sz, size_t val_sz, size_t len, float max_load)
{
    h->__ktype = ktype;
    h->__vtype = vtype;
    h->k_sz = key_sz;
    h->v_sz = val_sz;
    h->vals = malloc(val_sz * len);
    h->keys = calloc(len, key_sz);
    h->len = len;
    h->filled = 0;
    h->max_load = max_load;
}

#define hashmap_cons(hmap, k_type, v_type, len, max_load) _hashmap_cons(hmap, #k_type, #v_type, sizeof(k_type), sizeof(v_type), len, max_load)
/* #define hashmap_cons_exp(hmap, k_sz, v_sz, len) _hashmap_cons(hmap, k_sz, v_sz, len) */

#ifdef DEBUG
int check_type(const char* type, const char* expected, const char* ctx) {
    if(strcmp(type, expected) != 0) {
        log_warn("Type mismatch in value of %s (expected %s, got %s)", ctx, expected, type);
        return 1;
    }
    return 0;
}
#endif

static int isempty(void* ptr, size_t len)
{
    char* p = (char*)ptr;
    for (int i = 0; i < len; i++) {
        if (p[i] != 0) return 1;
    }
    return 0;
}

static void _hashmap_load_check(hashmap_t* h)
{
    h->filled++;
    if ((h->filled / h->len) < h->max_load) return;
    h->len *= 2;
    printf("Resized to %zu\n", h->len);
    void* tmpk = h->keys;
    void* tmpv = h->vals;
    h->vals = malloc(h->len*h->v_sz);
    h->keys = calloc(h->len, h->k_sz);
    for (int i = 0; i < h->len; i++) {
        if (isempty(tmpk+i*h->k_sz, h->k_sz)) continue; // Will break if default constructed value not 0 FIXME
        size_t index = hash_str(tmpk+(i*h->k_sz)); // hash_str here is temporary solution FIXME?
        memcpy(h->vals+index, tmpv+index, h->v_sz);
        memcpy(h->keys+index, tmpk+index, h->k_sz);
    }
    free(tmpk);
    free(tmpv);
}

#ifdef DEBUG
#define hashmap_ins(T1, T2, hmap, k, v) check_type(#T1, (hmap)->__ktype, "hashmap inserted key"); \
    check_type(#T2, (hmap)->__vtype, "hashmap inserted val");           \
    _hashmap_load_check(hmap); \
    ((T1*)(hmap)->keys)[hash(k) % (hmap)->len] = k; \
    ((T2*)(hmap)->vals)[hash(k) % (hmap)->len] = v;
#else
#define hashmap_ins(T1, T2, hmap, k, v) ((T2*)(hmap)->vals)[hash(k) % (hmap)->len] = v; \
    ((T1*)(hmap)->keys)[hash(k) % (hmap)->len] = k;
#endif
#define hashmap_ins_arr(T1, T2, hmap, k, v, k_sz, v_sz) hashmap_ins(T1, T2, hmap, malloc(k_sz), malloc(v_sz))

static void* _hashmap_get(hashmap_t* h, size_t index, size_t v_sz, const char* vtype)
{
#ifdef DEBUG
    check_type(vtype, h->__vtype, "hashmap read val");
#endif
    return h->vals + (index * v_sz);
}

#define hashmap_get(T, hmap, k) *((T*)_hashmap_get(hmap, hash(k) % (hmap)->len, sizeof(T), #T))
