#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define	CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); } 

#if	defined(__linux__)
extern	char	*strdup(char *string);
#endif

// struct for file metadata
typedef struct {
    char *pathname;
    int size;
    char *hash;
} FILES;

FILES *files;
int nfiles;
int total_file_size;

// strSHA2.c functions
char *strSHA2(char *filename);
// files.c functions
void scan_directory(char *dirname);

// Needed for the -a flag
bool including_hidden;

// struct for listnode used in hashtable
typedef struct _list {
     char *sha2hash;
     FILES *files;
     int nfiles;
     struct _list   *next;
} LISTNODE;

char **unique_hashes; // dynamically allocated array of strings
int n_unique_hashes;
int total_unique_size;

// listnode.c functions
LISTNODE *list_new(void);
LISTNODE *create_empty_listnode(FILES *file);
LISTNODE *list_find(LISTNODE *listnode, FILES *file);
void add_file_to_listnode(LISTNODE *listnode, FILES *file);
LISTNODE *list_add(LISTNODE *listnode, FILES *file);
LISTNODE *find_listnode_from_hash(LISTNODE *listnode, char *sha2hash);

// struct for hashtable as array of listnodes
typedef LISTNODE * HASHTABLE;

// hashtable.c functions
HASHTABLE *hashtable_new(void);
void hashtable_add(HASHTABLE *hashtable, FILES *file);
LISTNODE *get_listnode_from_sha2hash(HASHTABLE *hashtable, char *sha2hash);

// hashtable that will store all files
HASHTABLE *full_hashtable;
