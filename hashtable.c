//
// Created by dragos on 05.03.2018.
//

#include "hashtable.h"

void add_word_to_bucket(BUCKET **bucket, char *new_word) {

    if(bucket_contains_word((*bucket), new_word)) {
        return;
    }

    if ((*bucket)->first_entry == NULL) {
        (*bucket)->first_entry = malloc(sizeof(BUCKET_ENTRY));
        (*bucket)->first_entry->value = malloc((sizeof(char) * (strlen(new_word) + 1)));
        strcpy((*bucket)->first_entry->value, new_word);
        (*bucket)->first_entry->next = NULL;
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

    if (hashtable->first_bucket == NULL) {
        hashtable->first_bucket = create_bucket(key);
        hashtable->first_bucket->first_entry = NULL;
        hashtable->first_bucket->next_bucket = NULL;
        return hashtable->first_bucket;
    }

    BUCKET *bucket = hashtable->first_bucket;
    BUCKET *last_bucket;
    while (bucket != NULL) {
        if (bucket->key == key) {
            return bucket;
        }
        last_bucket = bucket;
        bucket = bucket->next_bucket;
    }
    last_bucket->next_bucket = create_bucket(key);
    last_bucket->next_bucket->prev_bucket = last_bucket;
    last_bucket = last_bucket->next_bucket;
    last_bucket->next_bucket = NULL;
    return last_bucket;
}



void print_hashtable(HASHTABLE *hashtable, char *file_name) {

    BUCKET *bucket = hashtable->first_bucket;

    FILE *file;
    if(file_name != NULL) {
        file = fopen(file_name, "a");
    } else {
        file = stdout;
    }

    while (bucket != NULL) {
        print_bucket(bucket, file);
        bucket = bucket->next_bucket;
    }
}



void print_bucket(BUCKET *bucket, FILE *file) {
    BUCKET_ENTRY *bucketEntry = bucket->first_entry;
    while (bucketEntry != NULL) {
        fprintf(file, "%s ", bucketEntry->value);
        bucketEntry = bucketEntry->next;
    }
    fprintf(file, "\n");
}
