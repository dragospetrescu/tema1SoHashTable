//
// Created by dragos on 09.03.2018.
//

#include "hashtable_interface.h"
#include "hashtable.h"

HASHTABLE *create_hashtable(int hash_size) {
	int i;
	HASHTABLE *hashtable = malloc(sizeof(HASHTABLE));

	DIE(hashtable == NULL,
		"Memory allocation for hashtable failed");

	hashtable->hash_size = hash_size;
	hashtable->buckets = malloc(sizeof(BUCKET) * hash_size);
	for (i = 0; i < hash_size; ++i) {
		hashtable->buckets[i].is_empty = 1;
		hashtable->buckets[i].key = i;
		hashtable->buckets[i].first_entry = NULL;
		hashtable->buckets[i].number_of_entries = 0;
	}

	return hashtable;
}

void free_hashtable(HASHTABLE **hashtable) {

	free((*hashtable)->buckets);
	free(*hashtable);
}

void add_word_to_hashtable(HASHTABLE *hashtable, char *word) {
	unsigned int calculated_hash = hash(word, hashtable->hash_size);
	BUCKET *bucket = get_bucket_with_hash(hashtable, calculated_hash);
	add_word_to_bucket(&bucket, word);
	bucket->is_empty = 0;
}

void remove_word_from_hashtable(HASHTABLE **hashtable, char *word,
								unsigned int hash) {
	BUCKET *bucket = get_bucket_with_hash(*hashtable, hash);
	if (bucket == NULL)
		return;

	remove_word_from_bucket(bucket, word);
	if (bucket_is_empty(bucket))
		bucket->is_empty = 1;

}

void print_hashtable(HASHTABLE *hashtable, FILE *file) {
	for (int i = 0; i < hashtable->hash_size; ++i) {
		BUCKET *bucket = get_bucket_with_hash(hashtable, i);
		if (!bucket->is_empty)
			print_bucket(bucket, file);
	}
	if (file != stdout)
		fclose(file);
}

void print_bucket_with_key(HASHTABLE *hashtable, int bucket_key, FILE *file) {
	BUCKET *bucket = get_bucket_with_hash(hashtable, bucket_key);
	if (bucket != NULL && !bucket_is_empty(bucket))
		print_bucket(bucket, file);

	if (file != stdout)
		fclose(file);
}

int hashtable_contains_word(HASHTABLE *hashtable, char *word) {
	unsigned int word_hash = hash(word, hashtable->hash_size);

	BUCKET *bucket = get_bucket_with_hash(hashtable, word_hash);
	if (bucket_contains_word(bucket, word))
		return 1;
	return 0;
}

void clear_hashtable(HASHTABLE **hashtable) {
	int i;
	for (i = 0; i < (*hashtable)->hash_size; ++i) {
		BUCKET *bucket = get_bucket_with_hash((*hashtable), i);

		BUCKET_ENTRY *bucket_entry = bucket->first_entry;

		while (bucket_entry != NULL) {
			BUCKET_ENTRY *next_bucket_entry = bucket_entry->next;
			remove_word_from_bucket(bucket, bucket_entry->value);
			bucket_entry = next_bucket_entry;
		}
	}
}

void move_words_to_new_hashtable(HASHTABLE *old_hashtable,
								 HASHTABLE **new_hashtable) {
	int i;
	for (i = 0; i < old_hashtable->hash_size; ++i) {
		BUCKET *bucket = get_bucket_with_hash(old_hashtable, i);
		BUCKET_ENTRY *bucket_entry = bucket->first_entry;

		while (bucket_entry != NULL) {
			add_word_to_hashtable((*new_hashtable), bucket_entry->value);
			bucket_entry = bucket_entry->next;
		}
	}
}