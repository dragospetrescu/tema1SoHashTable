//
// Created by dragos on 05.03.2018.
//

#include "hashtable.h"

void add_word_to_bucket(BUCKET *bucket, char *new_word) {

    if (bucket->first_value == NULL) {
        bucket->first_value = malloc(sizeof(VALUES_LIST));
        bucket->first_value->value = malloc((sizeof(char) * strlen(new_word)));
        strcpy(bucket->first_value->value, new_word);
        return;
    }
    VALUES_LIST *last_value = bucket->first_value;
    while (last_value->next != NULL) {
        last_value = last_value->next;
    }

    last_value->next = malloc(sizeof(VALUES_LIST));
    last_value->next->prev = last_value;
    last_value = last_value->next;
    last_value->value = malloc((sizeof(char) * strlen(new_word)));
    strcpy(last_value->value, new_word);
}

HASHTABLE *create_hashtable(int hash_size) {
    HASHTABLE *hashtable = malloc(sizeof(HASHTABLE));
    DIE(hashtable == NULL, "Memory allocation for hashtable failed");
    hashtable->hash_size = hash_size;
    return hashtable;
}


void free_hashtable(HASHTABLE *hashtable) {
    free(hashtable);
}

BUCKET *create_bucket(int key) {
    BUCKET *bucket = malloc(sizeof(BUCKET));
    bucket->key = key;
    return bucket;
}

BUCKET *get_bucket(HASHTABLE *hashtable, int key) {

    if (hashtable->first_bucket == NULL) {
        hashtable->first_bucket = create_bucket(key);
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
    return last_bucket;
}

