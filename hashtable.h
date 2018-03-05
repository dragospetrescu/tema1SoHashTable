//
// Created by dragos on 05.03.2018.
//

#ifndef TEMA1_HASHTABLE_H
#define TEMA1_HASHTABLE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "utils/utils.h"

typedef struct values_list {
    char *value;
    struct values_list *next;
    struct values_list *prev;
} VALUES_LIST;

typedef struct bucket {
    unsigned int key;
    int no_values;
    VALUES_LIST *first_value;
    struct bucket *next_bucket;
    struct bucket *prev_bucket;
} BUCKET;

typedef struct hashtable {
    int no_buckets;
    int hash_size;
    BUCKET *first_bucket;
} HASHTABLE;

void add_word_to_bucket(BUCKET *bucket, char *new_word);
HASHTABLE *create_hashtable(int hash_size);
void free_hashtable(HASHTABLE *hashtable);
BUCKET* create_bucket(int key);
BUCKET *get_bucket(HASHTABLE *hashtable, int key);

#endif //TEMA1_HASHTABLE_H
