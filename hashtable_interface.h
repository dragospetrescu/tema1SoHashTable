//
// Created by dragos on 09.03.2018.
//

#ifndef TEMA1_HASHTABLE_INTERFACE_H
#define TEMA1_HASHTABLE_INTERFACE_H

#include <stdio.h>

typedef struct values_list {

	char *value;
	struct values_list *next;
	struct values_list *prev;

} BUCKET_ENTRY;

typedef struct bucket {
	unsigned int key;
	int number_of_entries;
	BUCKET_ENTRY *first_entry;
	int is_empty;
} BUCKET;

typedef struct hashtable {
	int hash_size;
	BUCKET *buckets;
} HASHTABLE;

void add_word_to_hashtable(HASHTABLE *hashtable, char *word);

void remove_word_from_hashtable(HASHTABLE **hashtable, char *word,
								unsigned int hash);

void print_hashtable(HASHTABLE *hashtable, FILE *file);

int hashtable_contains_word(HASHTABLE *hashtable, char *word);

void clear_hashtable(HASHTABLE **hashtable);

HASHTABLE *create_hashtable(int hash_size);

void free_hashtable(HASHTABLE **hashtable);

void move_words_to_new_hashtable(HASHTABLE *old_hashtable,
								 HASHTABLE **new_hashtable);

void print_bucket_with_key(HASHTABLE *hashtable, int bucket_key, FILE *file);


#endif //TEMA1_HASHTABLE_INTERFACE_H
