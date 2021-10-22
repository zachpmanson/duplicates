// listnode.c implements all the functions that handle struct LISTNODE
#include "duplicates.h"
#include <string.h>

// Create a new empty list
LISTNODE *list_new(void) {
    return NULL;
}

// Check if file's sha2hash is already in list, return listnode where found or null
LISTNODE *list_find(LISTNODE *listnode, FILES *file) {
    // Traverse listnodes till end
    while (listnode != NULL) {
        // Return the listnode if it has the sha2hash we are looking for
        if (strcmp(listnode->sha2hash, file->hash) == 0) {
            return listnode;
        }
        listnode = listnode->next;
    }
    return NULL;
}

// Allocate space for a new item
LISTNODE *create_empty_listnode(FILES *file) {
    LISTNODE *new = calloc(1, sizeof(LISTNODE));
    CHECK_ALLOC(new);
    new->sha2hash = strdup(file->hash);
    CHECK_ALLOC(new->sha2hash);
    new->next = NULL;
    unique_hashes = realloc(unique_hashes, (n_unique_hashes + 1) * sizeof(unique_hashes[0]));
    CHECK_ALLOC(unique_hashes);
    unique_hashes[n_unique_hashes] = strdup(file->hash); // Add to sha2hash array
    CHECK_ALLOC(unique_hashes[n_unique_hashes]);
    // Increment hash and unique size counters
    ++n_unique_hashes;
    total_unique_size += file->size;
    return new;
}

// Add a file to the files array within an existing listnode 
void add_file_to_listnode(LISTNODE *listnode, FILES *file) {
    // Allocate additional space for a new FILES * in array
    listnode->files = realloc(listnode->files, (listnode->nfiles + 1) * sizeof(listnode->files[0]));
    CHECK_ALLOC(listnode->files);
    
    // Add pathname
    listnode->files[listnode->nfiles].pathname = strdup(file->pathname);
    CHECK_ALLOC(listnode->files[listnode->nfiles].pathname);
    // Add filesize
    listnode->files[listnode->nfiles].size = file->size;
    // Add sha2hash
    listnode->files[listnode->nfiles].hash = strdup(file->hash);
    CHECK_ALLOC(listnode->files[listnode->nfiles].hash);
    // Increment number of files at listnode
    ++listnode->nfiles;
}

// Adds a file to existing listnode for its sha2hash, or creates a new listnode and then adds file to it
LISTNODE *list_add(LISTNODE *listnode, FILES *file) {
    
    LISTNODE *foundlistnode;
    if ((foundlistnode = list_find(listnode, file)) != NULL) {
        // If we find there is a listnode for this sha2hash, add file to it
        add_file_to_listnode(foundlistnode, file);
        return listnode;
    } else {
        // If no listnode exists for this sha2hash, create one and add file to it.
        LISTNODE *new = create_empty_listnode(file);
        add_file_to_listnode(new, file);
        new->next = listnode;
        return new;
    }
}

// Finds the listnode corresponding to given sha2hash
LISTNODE *find_listnode_from_hash(LISTNODE *listnode, char *sha2hash) {
    while (listnode != NULL) {
        // Traverse listnodes till end, return the listnode if it has the sha2hash we are looking for
        if (strcmp(listnode->sha2hash, sha2hash) == 0) {
            return listnode;
        }
        listnode = listnode->next;
    }
    return NULL;
}
