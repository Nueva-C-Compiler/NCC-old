#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <log.h>
#include <stdbool.h>

#include "hashmap.h"

#define HASHMAP_INIT_SIZE 16

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


void hashmap_init(hashmap_t* h, size_t ksize, size_t vsize)
{
    h->keys = calloc(HASHMAP_INIT_SIZE, ksize);
    memset(h->keys, 0, HASHMAP_INIT_SIZE * ksize);
    h->k_sz = ksize;
    h->vals = malloc(vsize * HASHMAP_INIT_SIZE);
    h->v_sz = vsize;
    h->len = HASHMAP_INIT_SIZE;
    h->filled = 0;
}



void hashmap_resize(hashmap_t* h)
{
    void* tempk = h->keys;
    void* tempv = h->vals;
    h->len *= 2;
    h->keys = calloc(h->len, h->k_sz);
    h->vals = malloc(h->len * h->v_sz);
    for (size_t off = 0; off < (h->len / 2); off++) {
        if (!iszero(h->keys + (off*h->k_sz), h->len)) {
            memcpy(h->vals + (off*h->v_sz), tempv + (off*h->v_sz), h->v_sz);
            memcpy(h->keys + (off*h->k_sz), tempk + (off*h->k_sz), h->k_sz);
        }
    }
    free(tempk);
    free(tempv);
}


int hashmap_set(hashmap_t* h, void* k, void* v)
{
    printf("%f\n", (float)h->filled / h->len);
    if ((float)h->filled / h->len > (float)2/3) hashmap_resize(h);
    size_t index = hash(k, h->k_sz) % h->len;
    for (size_t off = index; off < h->len; off+=1) {
        if (memcmp(h->keys + (off*h->k_sz), k, h->k_sz) == 0) {
            memcpy(h->vals + (off*h->v_sz), v, h->v_sz);
            memcpy(h->keys + (off*h->k_sz), k, h->k_sz);
            return 0x0;
        }
        if (iszero(h->keys + (off*h->k_sz), h->len)) {
            h->filled++;
            memcpy(h->vals + (off*h->v_sz), v, h->v_sz);
            memcpy(h->keys + (off*h->k_sz), k, h->k_sz);
            return 0x0;
        }
    }
    return 0x1; 
}

// Returns address of value if it exists, otherwise returns 0x0 for no value or 0x1 for full table.
void* hashmap_get(hashmap_t* h, void* k)
{
    
    size_t index = hash(k, h->k_sz) % h->len;
    for (size_t off = index; off < h->len; off+=1) {
        if (memcmp(h->keys + (off * h->k_sz), k, h->k_sz) == 0) {
            return h->vals + (off * h->v_sz);
        }
        if (iszero(h->keys + (off * h->k_sz), h->len)) return 0x0;
    }
    return 0x1; 
}

void hashmap_del()
{
}

void hashmap_free()
{
}
