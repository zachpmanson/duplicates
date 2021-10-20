#include <string.h>
#include "duplicates.h"

// Create a new empty list
LISTNODE *list_new(void) {
    return NULL;
}

// Check if file's sha2hash is already in list, return listnode where found or null
LISTNODE *list_find(LISTNODE *listnode, FILES *file) {
    while (listnode != NULL) {
        // traverse listnodes till end, return the listnode if it has the sha2hash we are looking for
        //printf("COMPARING listnode->sha2hash:%s to file->hash:%s\n",listnode->sha2hash,file->hash);
        if (strcmp(listnode->sha2hash, file->hash) == 0) {
            //printf("THEY MATCHED!");
            return listnode;
        }
        listnode = listnode->next;
    }
    return NULL;
}

// Allocate space for a new item
LISTNODE *create_empty_listnode(FILES *file) {
    //printf("Creating new listnode for hash %s\n",file->hash);
    LISTNODE *new = calloc(1, sizeof(LISTNODE));
    CHECK_ALLOC(new);
    new->sha2hash = strdup(file->hash);
    CHECK_ALLOC(new->sha2hash); //this may cause errors
    new->next = NULL;
    unique_hashes = realloc(unique_hashes, (n_unique_hashes + 1) * sizeof(unique_hashes[0]));
    CHECK_ALLOC(unique_hashes);
    unique_hashes[n_unique_hashes] = strdup(file->hash); //add to shar2hash array
    CHECK_ALLOC(unique_hashes[n_unique_hashes]);
    ++n_unique_hashes;//increment hash counter
    total_unique_size += file->size;
    //printf("total_unique_size:%i\n",total_unique_size);
    return new;
}

// Add a file to the files array within an existing listnode 
void add_file_to_listnode(LISTNODE *listnode, FILES *file) {
    // Allocate additional space for a new FILES * in array
    listnode->files = realloc(listnode->files, (listnode->nfiles + 1) * sizeof(listnode->files[0]));// if this fails try size(file));
    CHECK_ALLOC(listnode->files);
    
    // Add pathname
    listnode->files[listnode->nfiles].pathname = strdup(file->pathname);
    CHECK_ALLOC(listnode->files[listnode->nfiles].pathname);
    // Add filesize
    listnode->files[listnode->nfiles].size = file->size;
    // add sha2 (is redundant but whatever)
    listnode->files[listnode->nfiles].hash = strdup(file->hash);
    CHECK_ALLOC(listnode->files[listnode->nfiles].hash);

    //printf("\t file %s added! has sha2hash %s\n", listnode->files[listnode->nfiles].pathname, listnode->files[listnode->nfiles].hash);
    ++listnode->nfiles;
}

// Adds a file to the listnode for its sha2hash, or creates a new listnode and then adds file to it
LISTNODE *list_add(LISTNODE *listnode, FILES *file) {
    
    LISTNODE *foundlistnode;
    if ((foundlistnode = list_find(listnode, file)) != NULL) {
        //printf("\tFound listnode for sha2hash: %s\n", file->hash);
        // if we find there is a listnode for this sha2hash, add file to it
        add_file_to_listnode(foundlistnode, file);
        return listnode;
    } else {
        // if no listnode exists for this sha2hash, create one and add file to it.
        //printf("Couldn't find listnode for sha2hash: %s\n", file->hash);
        LISTNODE *new = create_empty_listnode(file);
        add_file_to_listnode(new, file);
        new->next = listnode;
        return new;
    }
}

LISTNODE *find_listnode_from_hash(LISTNODE *listnode, char *sha2hash) {
    while (listnode != NULL) {
        // traverse listnodes till end, return the listnode if it has the sha2hash we are looking for
        if (strcmp(listnode->sha2hash, sha2hash) == 0) {
            return listnode;
        }
        listnode = listnode->next;
    }
    return NULL;
}
