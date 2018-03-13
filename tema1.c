
#include "hashtable_interface.h"
#include "file_utils.h"
#include "hash.h"

void parse_arguments(int argc, char **argv, int *hash_size, int *no_input_files,
					 char ***input_files);

void parse_arguments(int argc, char **argv, int *hash_size, int *no_input_files,
					 char ***input_files)
{
	int i;
	char *ptr;


	DIE(argc < 2, "Invalid number of arguments");

	(*hash_size) = strtol(argv[1], &ptr, 10);
	DIE((*ptr) != '\0' || *hash_size <= 0, "Invalid hash table size");

	if (argc > 2) {
		(*no_input_files) = argc - 2;
		(*input_files) = malloc(sizeof(char *) * ((*no_input_files)));
		DIE((*input_files) == NULL,
			"Memory allocation for input files failed");


		for (i = 0; i < (*no_input_files); ++i) {

			(*input_files)[i] = malloc(
					sizeof(char) *
					(strlen(argv[i + 2]) + 1));
			DIE((*input_files)[i] == NULL,
				"Memory allocation for input files failed");
			strcpy((*input_files)[i], argv[i + 2]);
		}
	} else {
		(*no_input_files) = 0;
	}
}


void parse_command(char command_buffer[20000], HASHTABLE **hashtable)
{
	const char s[3] = "\n ";
	char *token;
	char *command_name;
	char *argument1 = NULL;
	char *argument2 = NULL;
	char *ptr;
	FILE *file;
	int bucket_key;
	int new_hash_size;
	HASHTABLE *new_hashtable;

	if (strcmp(command_buffer, "\n") == 0)
		return;
	token = strtok(command_buffer, s);
	if (token == NULL)
		return;

	command_name = malloc(sizeof(char) * (strlen(token) + 1));
	DIE(command_name == NULL, "Memory allocation failed");
	strcpy(command_name, token);


	token = strtok(NULL, s);
	if (token != NULL) {
		argument1 = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(argument1, token);

		token = strtok(NULL, s);
		if (token != NULL) {
			argument2 = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(argument2, token);
		}
	}

	if (strcmp(command_name, "add") == 0) {

		DIE(argument1 == NULL || strcmp(argument1, "") == 0,
			"Invalid add command");
		add_word_to_hashtable((*hashtable), argument1);

	} else if (strcmp(command_name, "remove") == 0) {

		DIE(argument1 == NULL || strcmp(argument1, "") == 0,
			"Invalid remove command");
		remove_word_from_hashtable(
				hashtable,
				argument1,
				hash(argument1, (*hashtable)->hash_size));

	} else if (strcmp(command_name, "print") == 0) {

		FILE *file = get_output_file(argument1);

		print_hashtable((*hashtable), file);

	} else if (strcmp(command_name, "print_bucket") == 0) {
		DIE(argument1 == NULL || strcmp(argument1, "") == 0,
			"Invalid print_bucket command");
		bucket_key = strtol(argument1, &ptr, 10);
		DIE(*ptr != '\0', "Invalid number for print_bucket");

		file = get_output_file(argument2);
		print_bucket_with_key((*hashtable), bucket_key, file);

	} else if (strcmp(command_name, "find") == 0) {

		FILE *file = get_output_file(argument2);

		DIE(argument1 == NULL || strcmp(argument1, "") == 0,
			"Invalid find command");
		if (hashtable_contains_word(*hashtable, argument1))
			fprintf(file, "True\n");
		else
			fprintf(file, "False\n");


	} else if (strcmp(command_name, "clear") == 0)

		clear_hashtable(hashtable);

	else if (strcmp(command_name, "resize") == 0) {
		DIE(argument1 == NULL || strcmp(argument1, "") == 0,
			"Invalid find command");
		if (strcmp(argument1, "double") == 0)
			new_hash_size = (*hashtable)->hash_size * 2;
		else if (strcmp(argument1, "halve") == 0)
			new_hash_size = (*hashtable)->hash_size / 2;
		else
			DIE(1, "Invalid resize command");

		new_hashtable = create_hashtable(new_hash_size);
		move_words_to_new_hashtable((*hashtable), &new_hashtable);
		clear_hashtable(hashtable);
		free_hashtable(hashtable);
		*hashtable = new_hashtable;

	} else
		DIE(1, "Invalid command");


	free(command_name);
	if (argument1 != NULL)
		free(argument1);

	if (argument2 != NULL)
		free(argument2);
}


int main(int argc, char **argv)
{
	int hash_size;
	int no_input_files = 0;
	char **input_files;
	int i;
	HASHTABLE *hashtable;
	FILE *file;
	char command_buffer[20000];

	parse_arguments(argc, argv, &hash_size, &no_input_files, &input_files);
	hashtable = create_hashtable(hash_size);



	if (no_input_files > 0) {
		for (i = 0; i < no_input_files; ++i) {
			file = fopen(input_files[i], "r");
			if (file < 0)
				continue;

			while (fgets(command_buffer, 20000, file))
				parse_command(command_buffer, &hashtable);


			fclose(file);
		}
	} else
		while (fgets(command_buffer, 20000, stdin))
			parse_command(command_buffer, &hashtable);

	clear_hashtable(&hashtable);
	free_hashtable(&hashtable);

	for (i = 0; i < no_input_files; ++i)
		free(input_files[i]);
	if (no_input_files > 0)
		free(input_files);
	return 0;
}
