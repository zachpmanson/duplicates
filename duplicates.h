#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "hashmap.h"

typedef struct {
    char *pathname;
    char *hash;
} FILES;

FILES *files;
int nfiles;

char *strSHA2(char *filename);
void scan_directory(char *dirname);

bool including_hidden;
