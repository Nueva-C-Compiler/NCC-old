#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "hashmap.h"
#include <log.h>


#define HASHMAP_INIT_SIZE 16

// djb2 hash
// http://www.cse.yorku.ca/~oz/hash.html
size_t hash(char* p, size_t sz)
{
    unsigned long hash = 5381;
    int c;

    for (int i = 0; i < sz; i++) {
        c = *p++;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

// Check if arbitrary block of memory is zero
bool iszero(void *p, size_t len)
{
    bool iszero = true;
    for (int i = 0; i < len; i++){
        if (*(char*)p != 0) {
            iszero = false;
            break;
        }
        p++;
    }
    return iszero;
}


// Initialize the hashmap pointed to by h.
void hashmap_init(hashmap_t* h, size_t ksize, size_t vsize)
{
    // Keys and vals are in different arrays so unnecessary things aren't in cache
    h->keys = calloc(HASHMAP_INIT_SIZE, ksize);
    h->vals = malloc(vsize * HASHMAP_INIT_SIZE);
    h->k_sz = ksize;
    h->v_sz = vsize;
    h->len = HASHMAP_INIT_SIZE;
    h->filled = 0; // Store # of filled keys for load factor calculation
}

void hashmap_resize(hashmap_t* h)
{
    void* tempk = h->keys;
    void* tempv = h->vals;
    h->len *= 2;
    log_debug("Resizing to %d items", h->len);
    // Simple to use calloc here because keys need to be initialized to zero.
    h->keys = calloc(h->len, h->k_sz);
    h->vals = malloc(h->len * h->v_sz);
    // Copy all keys and values
    for (size_t off = 0; off < (h->len / 2); off++) {
        // Don't bother copying entries with empty keys
        if (!iszero(tempk + (off*h->k_sz), h->k_sz)) {
            hashmap_set(h, tempk + (off*h->k_sz), tempv + (off*h->v_sz));
            h->filled--;
        }
    }
    free(tempk);
    free(tempv);
}

int hashmap_set(hashmap_t* h, void* k, void* v)
{
    // Check if load factor too high

    if ((float)h->filled / h->len > (float)2/3) hashmap_resize(h);
    size_t index = hash(k, h->k_sz) % h->len;
    int looped_once = 0;
    // Start at the hashed index, iterate until own key or empty key is found
    for (size_t off = index; off < h->len; off+=1) {
        // Check if stored key at hashed index is equal to key: if so, replace value
        if (memcmp(h->keys + (off*h->k_sz), k, h->k_sz) == 0) {
            memcpy(h->vals + (off*h->v_sz), v, h->v_sz);
            return 0x0;
        }
        // Check if stored key is zero: if so, copy key and value over
        if (iszero(h->keys + (off*h->k_sz), h->k_sz)) {
            h->filled++;
            memcpy(h->vals + (off*h->v_sz), v, h->v_sz);
            memcpy(h->keys + (off*h->k_sz), k, h->k_sz);
            return 0x0;
        }
        if (off == h->len-1 && looped_once == 0) {
            off = 0;
            looped_once = 1;
        }
    }
    // Hashmap is full (this shouldn't ever happen unless default size is really low)
    return 0x1;
}

// Returns address of value if it exists, otherwise returns 0x0 for no value or 0x1 for full table.
void* hashmap_get(hashmap_t* h, void* k)
{
    size_t index = hash(k, h->k_sz) % h->len;
    int looped_once = 0;
    // Start at the hashed index, iterate until wanted key or empty key is found
    for (size_t off = index; off < h->len; off+=1) {
        // Check if entry has correct key
        if (memcmp(h->keys + (off * h->k_sz), k, h->k_sz) == 0) {
            return h->vals + (off * h->v_sz);
        }
        // Empty entry means this key doesn't exist: return not found
        if (iszero(h->keys + (off * h->k_sz), h->k_sz)) {
            return 0x0;
        }
        // If we hit the end, wrap back around the hashmap. Only do this once.
        if (off == h->len-1 && looped_once == 0) {
            off = 0;
            looped_once = 1;
        }
    }
}

int hashmap_del(hashmap_t* h, void* k)
{
    size_t index = hash(k, h->k_sz) % h->len;
    int looped_once = 0;
    for (size_t off = index; off < h->len; off+=1) {
        if (memcmp(h->keys + (off * h->k_sz), k, h->k_sz) == 0) {
            memset(h->keys + (off * h->v_sz), 0, h->k_sz);
            // No reason to delete value, will just be overwritten next time.
            return 0;
        }
        if (iszero(h->keys + (off * h->k_sz), h->k_sz)) return 1;
        if (off == h->len-1 && looped_once == 0) {
            off = 0;
            looped_once = 1;
        }
    }
    return 1;
}

void hashmap_free(hashmap_t* h)
{
    free(h->keys);
    free(h->vals);
}