#include "duplicates.h"
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <sys/param.h>
#include  <dirent.h>
#include  <string.h>

#if defined(__linux__)
extern char *strdup(const char *s);
#endif

// Checks that a given pathname doesn't end with /. or /..
int is_valid_dir(char *s) {
    char *slash = strrchr(s, '/');
    if (slash && strcmp(slash, "/.") == 0) {
        return 0;
    } else if (slash && strcmp(slash, "/..") == 0) {
        return 0;
    }
    return 1;
}

// Returns 1 if file is hidden (also 1 for . and ..)
int is_hidden_file(char *s) {
    char *slash = strrchr(s, '/');
    char c = slash[1];
    if (c == '.') return 1;
    return 0;
}

// Recursively find all files in dir and subdirs
void scan_directory(char *dirname) {
    DIR *dirp;
    struct dirent *dp;
    dirp = opendir(dirname);
    if (dirp == NULL) {
        perror(dirname);
        exit(EXIT_FAILURE);
    }

    // Loop through every file/subdir in dir
    while ( (dp = readdir(dirp)) != NULL ) {
        struct stat stat_info;
        char pathname[MAXPATHLEN];
        sprintf(pathname, "%s/%s", dirname, dp->d_name);

        if ( stat(pathname, &stat_info) != 0 ) {
            perror(pathname);
            exit(EXIT_FAILURE);
        }

        // Check if we exclude hidden files
        if (including_hidden == false) {
            // check if file is hidden
            if (is_hidden_file(pathname) == 1) {
                // move onto next file
                continue;
            }
        }

        if (S_ISDIR(stat_info.st_mode) != 0 && is_valid_dir(pathname)) {
            // if dp is dir, recurse 
            scan_directory(strdup(pathname));
        } else if (S_ISREG(stat_info.st_mode) != 0) {
            // Resize files array
            files = realloc(files, (nfiles + 1) * sizeof(files[0]));
            CHECK_ALLOC(files);

            files[nfiles].pathname = strdup(pathname);
            CHECK_ALLOC(files[nfiles].pathname);
            
            files[nfiles].size = stat_info.st_size;

            char *c = strSHA2(pathname);
            files[nfiles].hash = strdup(c);
            CHECK_ALLOC(files[nfiles].hash);
            
            ++nfiles;   
        }
    }

    closedir(dirp);
}