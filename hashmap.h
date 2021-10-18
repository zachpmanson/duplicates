#include "listnode.h"

typedef	LIST * HASHTABLE;

extern	HASHTABLE	*hashtable_new(void);

extern	void		 hashtable_add( HASHTABLE *, char *string);

extern	bool		 hashtable_find(HASHTABLE *, char *string);
