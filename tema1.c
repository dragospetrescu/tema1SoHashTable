#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "utils/utils.h"


void parse_arguments(int argc, char **argv, int *hashtable_size, int *no_input_files, char ***input_files) {
    DIE(argc < 2, "Invalid number of arguments");

    (*hashtable_size) = atoi(argv[1]);
    DIE(hashtable_size <= 0, "Invalid hash table size");


    (*no_input_files) = argc - 1;
    (*input_files) = malloc(sizeof(char *) * ((*no_input_files)));

    if (argc == 2) {
        (*input_files)[0] = malloc(sizeof(char) * 5);
        strcpy((*input_files)[0], "stdin");
    } else {
        int i;
        for (i = 0; i < (*no_input_files); ++i) {
            (*input_files)[i] = malloc(sizeof(char) * strlen(argv[i + 2]));
            strcpy((*input_files)[i], argv[i+2]);
        }
    }
}


int main(int argc, char **argv) {

    int hashtable_size;
    int no_input_files;
    char **input_files;

    parse_arguments(argc, argv, &hashtable_size, &no_input_files, &input_files);

    printf("%d", hash("Ionut", 256));

    int i;
    for (i = 0; i < no_input_files; ++i) {
        free(input_files[i]);
    }
    free(input_files);
    return 0;
}