
#include "bucket_interface.h"


void add_word_to_bucket(BUCKET **bucket, char *new_word)
{

	BUCKET_ENTRY *last_bucket_entry;

	if (bucket_contains_word((*bucket), new_word))
		return;

	if ((*bucket)->first_entry == NULL) {
		(*bucket)->first_entry = malloc(sizeof(BUCKET_ENTRY));
		(*bucket)->first_entry->value = malloc(
				(sizeof(char) * (strlen(new_word) + 1)));
		strcpy((*bucket)->first_entry->value, new_word);
		(*bucket)->first_entry->next = NULL;
		(*bucket)->first_entry->prev = NULL;
		(*bucket)->number_of_entries++;
		return;
	}
	last_bucket_entry = (*bucket)->first_entry;
	while (last_bucket_entry->next != NULL)
		last_bucket_entry = last_bucket_entry->next;


	last_bucket_entry->next = malloc(sizeof(BUCKET_ENTRY));
	last_bucket_entry->next->prev = last_bucket_entry;
	last_bucket_entry = last_bucket_entry->next;
	last_bucket_entry->value = malloc(
			(sizeof(char) *
			 (strlen(new_word) + 1)));
	strcpy(last_bucket_entry->value, new_word);
	(*bucket)->number_of_entries++;
	last_bucket_entry->next = NULL;
}


int bucket_contains_word(BUCKET *bucket, char *word)
{

	BUCKET_ENTRY *bucketEntry = bucket->first_entry;

	while (bucketEntry != NULL) {
		if (strcmp(word, bucketEntry->value) == 0)
			return 1;
		bucketEntry = bucketEntry->next;
	}
	return 0;
}


BUCKET *get_bucket_with_hash(HASHTABLE *hashtable, int key)
{
	if (hashtable->buckets == NULL && hashtable->hash_size <= key)
		return NULL;

	return &hashtable->buckets[key];
}

void print_bucket(BUCKET *bucket, FILE *file)
{
	int i;
	BUCKET_ENTRY *bucketEntry;

	if (!bucket_is_empty(bucket)) {
		bucketEntry = bucket->first_entry;
		for (i = 0; i < bucket->number_of_entries; ++i) {
			fprintf(file, "%s ", bucketEntry->value);
			bucketEntry = bucketEntry->next;
		}
		fprintf(file, "\n");
	}
}


void remove_word_from_bucket(BUCKET *bucket, char *word)
{
	BUCKET_ENTRY *bucketEntry;
	BUCKET_ENTRY *bucket_entry_to_be_freed;

	if (bucket->first_entry == NULL)
		return;

	if (strcmp(bucket->first_entry->value, word) == 0) {
		bucket_entry_to_be_freed = bucket->first_entry;
		bucket->first_entry = bucket->first_entry->next;
		free(bucket_entry_to_be_freed->value);
		free(bucket_entry_to_be_freed);
		bucket->number_of_entries--;
		return;
	}

	bucketEntry = bucket->first_entry;
	while (bucketEntry != NULL) {
		if (strcmp(bucketEntry->value, word) == 0) {
			bucketEntry->prev->next = bucketEntry->next;
			free(bucketEntry->value);
			free(bucketEntry);
			bucket->number_of_entries--;
			return;

		}

		bucketEntry = bucketEntry->next;
	}

}

int bucket_is_empty(BUCKET *bucket)
{
	if (bucket->number_of_entries > 0)
		return 0;
	return 1;
}





