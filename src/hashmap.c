#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <log.h>

#define is_same_type(a, b)    __builtin_types_compatible_p(typeof(a), typeof(b))

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
                         const char*: hash_str,                         \
                         default: _exit_fatal("Invalid type passed to hash(). Please supply your own hash function instead."))

typedef struct hashmap {
    const char* __ktype;
    const char* __vtype;
    void* keys;
    void* vals;
#ifdef DEBUG
    size_t k_sz;
    size_t v_sz;
#endif
    size_t len;
} hashmap_t;

static void _hashmap_cons(hashmap_t* h, const char* ktype, const char* vtype, )
{
    h->__ktype = ktype;
    h->__vtype = vtype;
    h->vals = malloc(val_sz * len);
    h->keys = malloc(key_sz * len);
#ifdef DEBUG
    h->k_sz = key_sz;
    h->v_sz = val_sz;
#endif
    h->len = len;
}

#define hashmap_cons(hmap, k_type, v_type, len) _hashmap_cons(hmap, #k_type, #v_type, sizeof(k_type), sizeof(v_type), len)
/* #define hashmap_cons_exp(hmap, k_sz, v_sz, len) _hashmap_cons(hmap, k_sz, v_sz, len) */


#ifdef DEBUG
#define check_size(sz, expected, ctx) if(sz != expected) log_warn("Type size mismatch in value of %s (declared size %zu != %s size %zu)", ctx, expected, ctx, sz)
#endif

#ifdef DEBUG
#define hashmap_ins(T1, T2, hmap, k, v) check_size(sizeof(T1), hmap->k_sz, "hashmap inserted key"); \
    check_size(sizeof(T2), hmap->v_sz, "hashmap inserted val"); \
    ((T1*)(hmap)->keys)[hash(k) % (hmap)->len] = k; \
    ((T2*)(hmap)->vals)[hash(k) % (hmap)->len] = v;
#else
#define hashmap_ins(T1, T2, hmap, k, v) ((T2*)(hmap)->vals)[hash(k) % (hmap)->len] = v; \
    ((T1*)(hmap)->keys)[hash(k) % (hmap)->len] = k;
#endif
#define hashmap_ins_arr(T1, T2, hmap, k, v, k_sz, v_sz) hashmap_ins(T1, T2, hmap, malloc(k_sz), malloc(v_sz))


static void* _hashmap_get(hashmap_t* h, size_t index, size_t v_sz)
{
    return h->vals + (index * v_sz);
}

#ifdef DEBUG
#define hashmap_get(T, hmap, k) check_size(sizeof(T), hmap->v_sz, "hashmap read value"); \
        *((T*)_hashmap_get(hmap, hash(k) % (hmap)->len, sizeof(T)))
#else
#define hashmap_get(T, hmap, k) *((T*)_hashmap_get(hmap, hash(k) % (hmap)->len, sizeof(T)))
#endif
