#include <stdbool.h>

//  A HELPFUL PREPROCESSOR MACRO TO CHECK IF ALLOCATIONS WERE SUCCESSFUL
#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

typedef struct _list {
     char           *string;
     struct _list   *next;
} LIST;

extern	LIST	*list_new(void);
extern	LIST	*list_add(  LIST *list, char *newstring);
extern	bool	 list_find (LIST *list, char *want);
extern	void	 list_print(LIST *list);
