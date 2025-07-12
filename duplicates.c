//  CITS2002 Project 2 2021
//  Name(s):             Zach Manson, Dempsey Thompson
//  Student number(s):   22903345, 22988643

#include "duplicates.h"
#include <getopt.h>
#include <limits.h>

#define OPTLIST "aAf:h:lmqQT"

char *realpath(const char *__restrict__file_name, char *__restrict__resolved_name);

// To explain proper usage of program
void usage(void) {
    fprintf(stderr, "Usage: ./duplicates directory_path [-a] [-A] [-f filename] [-h SHA2_hash] [-l] [-q]\n");
    // add more usage instructions
}

// Function to handle -A flag, which finds if project is advanced.  Returns 1
void is_advanced(void) {
    exit(EXIT_FAILURE);
}

// No flag output
void do_standard_output(void) {
    printf("%i\n", nfiles);
    printf("%i\n", total_file_size);
    printf("%i\n",n_unique_hashes);
    printf("%i\n", total_unique_size);
    exit(EXIT_SUCCESS);
}

// -f flag output
void do_single_file_comparison(char *filename_to_match) {
    char *hash_to_match = strSHA2(filename_to_match);
    // If file doesn't exist, or strSHA2 failed
    if (hash_to_match == NULL) {
        exit(EXIT_FAILURE);
    }
    LISTNODE *l = get_listnode_from_sha2hash(full_hashtable, hash_to_match);
    // If no listnode for that hash exists, exit failure
    if (l == NULL) {
        exit(EXIT_FAILURE);
    }
    // If listnode exists are there is more than 1
    if (l->nfiles > 1) {
        // List all duplicates
        for (int i = 0; i < l->nfiles; ++i) {
            // Other than original file
            char *fullpath1 = realpath(l->files[i].pathname, NULL);
            char *fullpath2 = realpath(filename_to_match, NULL);

            if (strcmp(fullpath1, fullpath2) != 0) {
                printf("%s\n",l->files[i].pathname);
            }
        }
        exit(EXIT_SUCCESS);
    } else {
        // Otherwise no duplicates exist
        exit(EXIT_FAILURE);
    }
}

// -h flag output
void do_single_hash_comparison(char *hash_to_match) {

    if (hash_to_match == NULL) {
        exit(EXIT_FAILURE);
    }
    LISTNODE *l = get_listnode_from_sha2hash(full_hashtable, hash_to_match);
    // If no listnode for that hash exists, exit failure
    if (l == NULL) {
        exit(EXIT_FAILURE);
    }
    // If listnode exists are there is more than 1
    if (l->nfiles > 1) {
        // List all duplicates
        for (int i = 0; i < l->nfiles; ++i) {
            printf("%s\n",l->files[i].pathname);
        }
        exit(EXIT_SUCCESS);
    } else {
        // Otherwise no duplicates exist
        exit(EXIT_FAILURE);
    }
}

// -l flag output
void do_list_all_files(bool wrap_in_quotes, bool seperate_with_tabs) {
    char* seperator = "  ";
    if (seperate_with_tabs) {
        seperator = "\t";
    }
    // Loops through listnodes
    for(int i = 0; i < n_unique_hashes; ++i) {
        LISTNODE *l = get_listnode_from_sha2hash(full_hashtable, unique_hashes[i]);          
        // Checks if the amount of files at a listnode is > 1, hence a duplicate
        if(l->nfiles > 1) {
            // Loops through each file at a listnode
            for(int j = 0; j < l->nfiles; ++j) {
                // Prints the files in the listnode
                if (wrap_in_quotes) {
                    printf("\"%s\"%s", l->files[j].pathname, seperator);
                } else {
                    printf("%s%s", l->files[j].pathname, seperator);
                }
            }
            printf("\n");
        }
    }
    exit(EXIT_SUCCESS);
}

// -q flag output
void do_quiet_output(void) {
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
    bool wrap_in_quotes = false;
    bool seperate_with_tabs = false;
    char *filename_to_match = NULL;
    char *hash_to_match = NULL;

    // Processes CLI args
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
                filename_to_match = strdup(optarg);
                single_file_comparison = true;
                standard_output = false;
                break;
            case 'h':
                hash_to_match = strdup(optarg);
                single_hash_comparison = true;
                standard_output = false;
                break;
            case 'l':
                standard_output = false;
                list_all_files = true;
                break;
            case 'q':
                standard_output = false;
                quiet_output = true;
                break;
            case 'Q':
                wrap_in_quotes = true;
                break;
            case 'T':
                seperate_with_tabs = true;
                break;
                
        }
    }

    // For cases where no directory is given
    if (optind > argc-1) {
        usage();
        exit(EXIT_FAILURE);
    }

    scan_directory(argv[optind]); // Looks through all the files in a given directory, stores them in files[]    
    full_hashtable = hashtable_new(); // Creates empty hashtable

    // Populates the hashtable with files
    for (int i = 0; i < nfiles; ++i) {
        hashtable_add(full_hashtable, &files[i]);
    }

    // Produces the output dependant upon the inputed flags
    // This handles them in alphabetical order, imcompatible flag usage will
    // preference by alphabetical order.
    if (standard_output == true) {
        do_standard_output();
    } else if (single_file_comparison == true) {
        do_single_file_comparison(filename_to_match);
    } else if (single_hash_comparison == true) {
        do_single_hash_comparison(hash_to_match);
    } else if (list_all_files == true) {
        do_list_all_files(wrap_in_quotes, seperate_with_tabs);
    } else if (quiet_output == true) {
        do_quiet_output();
    } else {
        usage();
        exit(EXIT_FAILURE);
    }
    // Shouldn't reach here
    exit(EXIT_FAILURE);
}
