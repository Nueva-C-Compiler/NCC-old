typedef struct hashmap_t {
    void* keys;
    void* vals;
    size_t k_sz;
    size_t v_sz;
    size_t len;
} hashmap_t; 

void hashmap_init(hashmap_t* h, size_t ksize, size_t vsize);
int hashmap_set(hashmap_t* h, void* k, void* v);
void* hashmap_get(hashmap_t* h, void* k);
void hashmap_del();
size_t hashmap_count();
void hashmap_free();
