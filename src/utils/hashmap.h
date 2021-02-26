#include <stddef.h>

typedef struct hashmap_t {
    void* keys;
    void* vals;
    size_t k_sz;
    size_t v_sz;
    size_t len;
    size_t filled;
} hashmap_t;

/**
 * Constructs a new hashmap_t.
 * @returns constructed hashmap_t or a completely blank hashmap_t in case of failure.
 */
hashmap_t hashmap_new(size_t ksize, size_t vsize);

/**
 * Sets a key-value pair in the hashmap_t passed to it.
 * NOTE: Will panic on full hashmap
 * @returns false for failure, true for success.
 */
bool hashmap_set(hashmap_t* h, void* k, void* v);

/**
 * Get value associated with key in hashmap.
 * @returns address of value associated with key in hashmap if it exists, otherwise returns NULL if no matching key found.
 */
void* hashmap_get(hashmap_t* h, void* k);

/**
 * Deletes key in hashmap (but not value).
 * @returns false for failure, true for success.
 */
bool hashmap_del(hashmap_t* h, void* k);

/**
 * Frees the hashmap.
 */
void hashmap_free(hashmap_t* h);
