//
// Created by dragos on 09.03.2018.
//

#include "hashtable_interface.h"
#include "hashtable.h"

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

void add_word_to_hashtable(HASHTABLE *hashtable, char *word) {
    int calculated_hash = hash(word, hashtable->hash_size);
    BUCKET *bucket = get_bucket_with_hash(hashtable, calculated_hash);
    if (bucket == NULL) {
        bucket = create_bucket_with_hash(hashtable, calculated_hash);
    }
    add_word_to_bucket(&bucket, word);
}

void remove_word_from_hashtable(HASHTABLE **hashtable, char *word, int hash) {
    BUCKET *bucket = get_bucket_with_hash(*hashtable, hash);
    if (bucket == NULL) {
        return;
    }

    remove_word_from_bucket(bucket, word);
    if (bucket_is_empty(bucket)) {
        remove_empty_bucket(*hashtable, bucket);
    }
}

void print_hashtable(HASHTABLE *hashtable, FILE *file) {

    BUCKET *bucket = hashtable->first_bucket;

    while (bucket != NULL) {
        print_bucket(bucket, file);
        bucket = bucket->next_bucket;
    }
    if (file != stdout)
        fclose(file);
}

void print_bucket_with_key(HASHTABLE *hashtable, int bucket_key, FILE *file) {
    BUCKET *bucket = get_bucket_with_hash(hashtable, bucket_key);
    if (bucket != NULL) {
        print_bucket(bucket, file);

    }
}

int hashtable_contains_word(HASHTABLE *hashtable, char *word) {

    BUCKET *bucket = hashtable->first_bucket;

    while (bucket != NULL) {
        if (bucket_contains_word(bucket, word)) {
            return 1;
        }
        bucket = bucket->next_bucket;
    }
    return 0;
}

void clear_hashtable(HASHTABLE **hashtable) {
    BUCKET *bucket = (*hashtable)->first_bucket;

    while (bucket != NULL) {
        BUCKET_ENTRY *bucket_entry = bucket->first_entry;

        while (bucket_entry != NULL) {
            BUCKET_ENTRY *next_bucket_entry = bucket_entry->next;
            remove_word_from_bucket(bucket, bucket_entry->value);
            bucket_entry = next_bucket_entry;
        }
        BUCKET *next_bucket = bucket->next_bucket;
        remove_empty_bucket((*hashtable), bucket);
        bucket = next_bucket;
    }
}

void move_words_to_new_hashtable(HASHTABLE *old_hashtable, HASHTABLE **new_hashtable) {

    BUCKET *bucket = old_hashtable->first_bucket;

    while (bucket != NULL) {
        BUCKET_ENTRY *bucket_entry = bucket->first_entry;

        while (bucket_entry != NULL) {
            add_word_to_hashtable((*new_hashtable), bucket_entry->value);
            bucket_entry = bucket_entry->next;
        }
        bucket = bucket->next_bucket;
    }

}