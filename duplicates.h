#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *pathname;
    char *hash;
} FILES;

FILES *files;
int nfiles;

char *strSHA2(char *filename);
void scan_directory(char *dirname);

bool including_hidden;

typedef struct _list {
     char           *string;
     struct _list   *next;
} LIST;

extern	LIST	*list_new(void);
extern	LIST	*list_add(  LIST *list, char *newstring);
extern	bool	 list_find (LIST *list, char *want);
extern	void	 list_print(LIST *list);
