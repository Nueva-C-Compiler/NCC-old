#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//#if !(__STDC__==1 && __STDC_VERSION >= 201112L)
//#error C11 compiler required.
//#endif

// djb2 algorithm
size_t hash_str(const char* str)
{
    size_t hash = 5381;
    int c;
    // equivalent to hash * 33 + c, which is 
    while (c = *str++) hash = ((hash << 5) + hash) + c;
    return hash;
}

#define hash(x) _Generic((x), int: (size_t) x,   \
                         const char*: hash_str)


typedef struct hashmap {
    void* keys; // For recomputing hashes properly.
    void* vals;
    size_t k_sz;
    size_t v_sz;
    size_t len;
} hashmap_t;

static void _hashmap_cons(hashmap_t* h, size_t key_sz, size_t val_sz, size_t len)
{
    h->vals = malloc(val_sz * len);
    h->keys = malloc(key_sz * len);
    h->k_sz = key_sz;
    h->v_sz = val_sz;
    h->len = len;
}

#define hashmap_cons(hmap, k_type, v_type, len) _hashmap_cons(hmap, sizeof(k_type), sizeof(v_type), len)
#define hashmap_cons_exp(hmap, k_sz, v_sz, len) _hashmap_cons(hmap, k_sz, v_sz, len)

void _hashmap_ins(hashmap_t* h, size_t index, void* key, void* val)
{
    memcpy(h->vals+index, val, h->v_sz);
    memcpy(h->keys+index, key, h->k_sz);
}

#define hashmap_ins(hmap, k, v) _hashmap_ins(hmap, hash(k), &k, v)
   
int main()
{
    hashmap_t h;
    hashmap_cons(&h, int, const char*, 10);
    int v = 2;
    hashmap_ins(&h, v, "abc");
    printf("%s\n", ((char**)h.vals)[1]);
}
