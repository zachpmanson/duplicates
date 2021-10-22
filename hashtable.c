#include <stdint.h>

#include "duplicates.h"

#define	HASHTABLE_SIZE 997

// Simple hash function to find which of the 997 slots to enter a sha2hash into
uint32_t hash_string(char *string)
{
    uint32_t hash = 0;

    while(*string != '\0') {
        hash = hash*33 + *string;
        ++string;
    }
    return hash;
}

// Allocate space for a new hashtable
HASHTABLE *hashtable_new(void) {
    HASHTABLE *new = calloc(HASHTABLE_SIZE, sizeof(LISTNODE *));
    CHECK_ALLOC(new);
    return new;
}

// Add a file to a hashtable
void hashtable_add(HASHTABLE *hashtable, FILES *file) {
    uint32_t h = hash_string(file->hash) % HASHTABLE_SIZE;
    hashtable[h] = list_add(hashtable[h], file);
}

// Retrieves the listnode corresponding to a sha2hash
LISTNODE *get_listnode_from_sha2hash(HASHTABLE *hashtable, char *sha2hash) {
    uint32_t h = hash_string(sha2hash) % HASHTABLE_SIZE;
    return find_listnode_from_hash(hashtable[h], sha2hash);
}


