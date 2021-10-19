#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define	CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); } 

typedef struct {
    char *pathname;
    int size;
    char *hash;
} FILES;

FILES *files;
int nfiles;

// strSHA2.c functions
char *strSHA2(char *filename);
// files.c functions
void scan_directory(char *dirname);

bool including_hidden;

// struct for listnode
typedef struct _list {
     char           *sha2hash;
     FILES *files;
     int nfiles;
     struct _list   *next;
} LISTNODE;

// listnode.c functions
LISTNODE *list_new(void);
LISTNODE *create_empty_listnode(FILES *file);
LISTNODE *list_find(LISTNODE *listnode, FILES *file);
void add_file_to_listnode(LISTNODE *listnode, FILES *file);
LISTNODE *list_add(LISTNODE *listnode, FILES *file);

// struct for hashtable as array of listnodes
typedef LISTNODE * HASHTABLE;

// hashtable.c functions
HASHTABLE *hashtable_new(void);
void hashtable_add(HASHTABLE *hashtable, FILES *file);

