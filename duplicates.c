//  CITS2002 Project 2 2021
//  Name(s):             Zach Manson, Dempsey Thompson
//  Student number(s):   22903345, 22988643

#include "duplicates.h"
#include <getopt.h>
#include <limits.h>
char *realpath(const char *__restrict__file_name, char *__restrict__resolved_name);

#define OPTLIST "aAf:h:lmq"

// To explain proper usage of program
void usage() {
    fprintf(stderr, "Usage: requires 1 directory arg\n");
    // add more usage instructions
}

// Function to handle -A flag, which finds if project is advanced
// may change to EXIT_SUCCESS later if we decide to do advanced
void is_advanced() {
    exit(EXIT_FAILURE);
}

void do_standard_output() {
    printf("%i\n", nfiles);
    printf("%i\n", total_file_size);
    printf("%i\n",n_unique_hashes);
    printf("%i\n", total_unique_size);
}

void do_single_file_comparison(char *filename_to_match) {
    //printf("printing all dupes of %s\n", filename_to_match);
    char *hash_to_match = strSHA2(filename_to_match);
    //printf("hashed file: %s\n", hash_to_match);

    if (hash_to_match == NULL) {
        exit(EXIT_FAILURE);
    }
    LISTNODE *l = get_listnode_from_sha2hash(full_hashtable, hash_to_match);
    // if no listnode for that hash exists, exit failure
    if (l == NULL) {
        exit(EXIT_FAILURE);
    }
    // if listnode exists are there is more than 1
    if (l->nfiles > 1) {
        // list all duplicates
        for (int i = 0; i < l->nfiles; ++i) {
            // other than original file
            char *fullpath1 = realpath(l->files[i].pathname, NULL);
            char *fullpath2 = realpath(filename_to_match, NULL);

            if (strcmp(fullpath1, fullpath2) != 0) {
                printf("%s\n",l->files[i].pathname);
            }
        }
        exit(EXIT_SUCCESS);
    } else {
        // otherwise no duplicates exist
        exit(EXIT_FAILURE);
    }
}

void do_single_hash_comparison(char *hash_to_match) {

    if (hash_to_match == NULL) {
        exit(EXIT_FAILURE);
    }
    LISTNODE *l = get_listnode_from_sha2hash(full_hashtable, hash_to_match);
    // if no listnode for that hash exists, exit failure
    if (l == NULL) {
        exit(EXIT_FAILURE);
    }
    // if listnode exists are there is more than 1
    if (l->nfiles > 1) {
        // list all duplicates
        for (int i = 0; i < l->nfiles; ++i) {
            printf("%s\n",l->files[i].pathname);
        }
        exit(EXIT_SUCCESS);
    } else {
        // otherwise no duplicates exist
        exit(EXIT_FAILURE);
    }
}

void do_list_all_files() {
    
}

void do_quiet_output() {
    if (nfiles > total_unique_size) {
        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    
    // Requires at least 1 arg
    if (argc < 2) {
        usage();
        exit(EXIT_FAILURE);
    }
    
    bool standard_output = true;
    bool quiet_output = false;
    bool single_file_comparison = false;
    bool single_hash_comparison = false;
    bool list_all_files = false;
    char *filename_to_match = NULL;
    char *hash_to_match;

    // Processes CLI args
    // Will fill these in as we go
    int opt;
    while ( (opt = getopt(argc, argv, OPTLIST)) != -1) {
        switch (opt) {
            case 'a':
                including_hidden = true;
                break;
            case 'A':
                is_advanced();
                break;
            case 'f':
                //printf("optarg: %s\n", optarg);
                filename_to_match = strdup(optarg);
                single_file_comparison = true;
                standard_output = false;
                break;
            case 'h':
                hash_to_match = optarg;
                single_hash_comparison = true;
                standard_output = false;
                break;
            case 'l':
                standard_output = false;
                list_all_files = true;
                break;
            //case 'm': // unsure if supposed to process this as an arg
            //    break;// for basic version of project
            case 'q':
                standard_output = false;
                quiet_output = true;
                break;
        }
    }

    scan_directory(argv[optind]);
    full_hashtable = hashtable_new();

    for (int i = 0; i < nfiles; ++i) {
        hashtable_add(full_hashtable, &files[i]);
    }

    if (standard_output == true) {
        do_standard_output();
    } else if (single_file_comparison == true) {
        do_single_file_comparison(filename_to_match);
    } else if (single_hash_comparison == true) {
        do_single_hash_comparison(hash_to_match);
    } else if (list_all_files == true) {
        do_list_all_files();
    } else if (quiet_output == true) {
        do_quiet_output();
    } else {
        perror("Arg error!");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
