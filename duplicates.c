//  CITS2002 Project 2 2021
//  Name(s):             Zach Manson, Dempsey Thompson
//  Student number(s):   22903345, 22988643

#include "duplicates.h"
#include <getopt.h>

#define OPTLIST "aAfhlmq"

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

int main(int argc, char *argv[]) {
    
    // Requires at least 1 arg
    if (argc < 2) {
        usage();
        exit(EXIT_FAILURE);
    }
    
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
                break;
            case 'h':
                break;
            case 'l':
                break;
            //case 'm': // unsure if supposed to process this as an arg
            //    break;// for basic version of project
            case 'q':
                break;
        }
    }

    scan_directory(argv[optind]);
    // temp debug
    for (int i = 0; i < nfiles; ++i) {
        printf("%s\t %s\n", files[i].pathname,files[i].hash);
    }

    exit(EXIT_SUCCESS);
}