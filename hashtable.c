//
// Created by dragos on 05.03.2018.
//

#include "hashtable.h"

void remove_word_from_bucket(BUCKET *bucket, char *word);
int bucket_is_empty(BUCKET *bucket);
void remove_bucket(HASHTABLE *hashtable, BUCKET *to_be_removed_bucket);


void add_word_to_bucket(BUCKET **bucket, char *new_word) {

    if(bucket_contains_word((*bucket), new_word)) {
        return;
    }

    if ((*bucket)->first_entry == NULL) {
        (*bucket)->first_entry = malloc(sizeof(BUCKET_ENTRY));
        (*bucket)->first_entry->value = malloc((sizeof(char) * (strlen(new_word) + 1)));
        strcpy((*bucket)->first_entry->value, new_word);
        (*bucket)->first_entry->next = NULL;
        (*bucket)->first_entry->prev = NULL;
        (*bucket)->number_of_entries++;
        return;
    }
    BUCKET_ENTRY *last_bucket_entry = (*bucket)->first_entry;
    while (last_bucket_entry->next != NULL) {
        last_bucket_entry = last_bucket_entry->next;
    }

    last_bucket_entry->next = malloc(sizeof(BUCKET_ENTRY));
    last_bucket_entry->next->prev = last_bucket_entry;
    last_bucket_entry = last_bucket_entry->next;
    last_bucket_entry->value = malloc((sizeof(char) * (strlen(new_word) + 1)));
    strcpy(last_bucket_entry->value, new_word);
    (*bucket)->number_of_entries++;
    last_bucket_entry->next = NULL;
}


int bucket_contains_word(BUCKET *bucket, char *word) {

    BUCKET_ENTRY *bucketEntry = bucket->first_entry;
    while (bucketEntry != NULL) {
        if(strcmp(word, bucketEntry->value) == 0) {
            return 1;
        }
        bucketEntry = bucketEntry->next;
    }
    return 0;
}


HASHTABLE *create_hashtable(int hash_size) {
    HASHTABLE *hashtable = malloc(sizeof(HASHTABLE));
    DIE(hashtable == NULL, "Memory allocation for hashtable failed");
    hashtable->hash_size = hash_size;
    hashtable->first_bucket = NULL;
    return hashtable;
}


void free_hashtable(HASHTABLE *hashtable) {
    free(hashtable);
}


BUCKET *create_bucket(int key) {
    BUCKET *bucket = malloc(sizeof(BUCKET));
    bucket->key = key;
    bucket->first_entry = NULL;
    return bucket;
}


BUCKET *get_bucket_with_hash(HASHTABLE *hashtable, int key) {
    if(hashtable->first_bucket == NULL) {
        return NULL;
    }

    BUCKET *bucket = hashtable->first_bucket;
    while (bucket != NULL) {
        if (bucket->key == key) {
            return bucket;
        }
        bucket = bucket->next_bucket;
    }
    return NULL;
}


BUCKET *create_bucket_with_hash(HASHTABLE *hashtable, int key) {
    if (hashtable->first_bucket == NULL) {
        hashtable->first_bucket = create_bucket(key);
        hashtable->first_bucket->first_entry = NULL;
        hashtable->first_bucket->next_bucket = NULL;
        hashtable->first_bucket->prev_bucket = NULL;
        hashtable->first_bucket->number_of_entries = 0;
        return hashtable->first_bucket;
    }

    BUCKET *bucket = hashtable->first_bucket;
    while (bucket->next_bucket != NULL) {
        bucket = bucket->next_bucket;
    }
    bucket->next_bucket = create_bucket(key);
    bucket->next_bucket->prev_bucket = bucket;
    bucket = bucket->next_bucket;
    bucket->next_bucket = NULL;
    bucket->number_of_entries = 0;
    return bucket;
}


void print_hashtable(HASHTABLE *hashtable, FILE *file) {

    BUCKET *bucket = hashtable->first_bucket;

    while (bucket != NULL) {
        print_bucket(bucket, file);
        bucket = bucket->next_bucket;
    }
    if(file!= stdout)
        fclose(file);
}


void print_bucket(BUCKET *bucket, FILE *file) {
    BUCKET_ENTRY *bucketEntry = bucket->first_entry;
    printf("BUCKET %d: ", bucket->key);
    while (bucketEntry != NULL) {
        fprintf(file, "%s ", bucketEntry->value);
        bucketEntry = bucketEntry->next;
    }
    fprintf(file, "\n");
}


void remove_word_from_hashtable(HASHTABLE **hashtable, char *word, int hash) {
    BUCKET *bucket = get_bucket_with_hash(*hashtable, hash);
    if (bucket == NULL) {
        return;
    }

    remove_word_from_bucket(bucket, word);
    if(bucket_is_empty(bucket)) {
        remove_bucket(*hashtable, bucket);
    }
}





void remove_word_from_bucket(BUCKET *bucket, char *word) {
    if(bucket->first_entry == NULL) {
        return;
    }

    if (strcmp(bucket->first_entry->value, word) == 0) {
        BUCKET_ENTRY *bucket_entry_to_be_freed = bucket->first_entry;
        bucket->first_entry = bucket->first_entry->next;
        free(bucket_entry_to_be_freed);
        bucket->number_of_entries--;
        return;
    }

    BUCKET_ENTRY *bucketEntry = bucket->first_entry;
    while (bucketEntry != NULL) {
        if(strcmp(bucketEntry->value, word) == 0) {
            bucketEntry->prev->next = bucketEntry->next;
            free(bucketEntry);
            bucket->number_of_entries--;
            return;

        }

        bucketEntry = bucketEntry->next;
    }

}

int bucket_is_empty(BUCKET *bucket) {
    if(bucket->number_of_entries > 0) {
        return 0;
    }
    return 1;
}

void remove_bucket(HASHTABLE *hashtable, BUCKET *to_be_removed_bucket) {

    if(hashtable->first_bucket == NULL) {
        return;
    }

    if(hashtable->first_bucket->key == to_be_removed_bucket->key) {

        hashtable->first_bucket = hashtable->first_bucket->next_bucket;
        free(to_be_removed_bucket);
        return;
    }

    BUCKET *bucket = hashtable->first_bucket;
    while (bucket != NULL) {
        if(bucket->key == to_be_removed_bucket->key) {
            bucket->prev_bucket->next_bucket = bucket->next_bucket;
            free(to_be_removed_bucket);
            return;
        }
        bucket = bucket->next_bucket;
    }
}

int hashtable_contains_word(HASHTABLE *hashtable, char *word) {

    BUCKET *bucket = hashtable->first_bucket;

    while (bucket != NULL) {
        if(bucket_contains_word(bucket, word)) {
            return 1;
        }
        bucket = bucket->next_bucket;
    }
    return 0;
}