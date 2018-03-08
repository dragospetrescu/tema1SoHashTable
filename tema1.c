
#include "hashtable.h"


void parse_arguments(int argc, char **argv, int *hash_size, int *no_input_files, char ***input_files);

void parse_arguments(int argc, char **argv, int *hash_size, int *no_input_files, char ***input_files) {
    DIE(argc < 2, "Invalid number of arguments");

    (*hash_size) = atoi(argv[1]);
    DIE(hash_size <= 0, "Invalid hash table size");

    if (argc > 2) {
        (*no_input_files) = argc - 2;
        (*input_files) = malloc(sizeof(char *) * ((*no_input_files)));
        DIE((*input_files) == NULL, "Memory allocation for input files failed");

        int i;
        for (i = 0; i < (*no_input_files); ++i) {

            (*input_files)[i] = malloc(sizeof(char) * (strlen(argv[i + 2]) + 1));
            DIE((*input_files)[i] == NULL, "Memory allocation for input files failed");
            strcpy((*input_files)[i], argv[i + 2]);
        }
    }
}


void parse_command(char command_buffer[20000], HASHTABLE **hashtable) {

    const char s[3] = " \n";
    char *token;

    /* get the first token */
    token = strtok(command_buffer, s);
    DIE(token == NULL, "Invalid input");

    char *command_name = malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(command_name, token);

    char *argument = NULL;
    token = strtok(NULL, s);
    if (token != NULL) {
        argument = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(argument, token);
    }

    if (strcmp(command_name, "add") == 0) {
        BUCKET *bucket = get_bucket_with_hash(*hashtable, hash(argument, (*hashtable)->hash_size));
        add_word_to_bucket(&bucket, argument);
    }

    if(strcmp(command_name, "remove") == 0) {
        BUCKET *bucket = get_bucket_with_hash(*hashtable, hash(argument, (*hashtable)->hash_size));
        if(buc)
    }

    if (strcmp(command_name, "print") == 0) {
        print_hashtable((*hashtable), argument);
    }



    free(command_name);
    if (argument != NULL) {
        free(argument);
    }


}


int main(int argc, char **argv) {

    int hash_size;
    int no_input_files;
    char **input_files;

    parse_arguments(argc, argv, &hash_size, &no_input_files, &input_files);
    HASHTABLE *hashtable = create_hashtable(hash_size);

    char command_buffer[20000];

    if (no_input_files > 0) {
        for (int i = 0; i < no_input_files; ++i) {
            FILE *file = fopen(input_files[i], "r");
            DIE(file < 0, "Opening file failed");

            while (fgets(command_buffer, 20000, file)) {
//                printf("%s\n",command_buffer);
                parse_command(command_buffer, &hashtable);
            }


        }
    } else {

    }


    free_hashtable(hashtable);
    int i;
    for (i = 0; i < no_input_files; ++i) {
        free(input_files[i]);
    }
    free(input_files);
    return 0;
}