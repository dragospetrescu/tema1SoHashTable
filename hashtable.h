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
#include "hashtable_interface.h"


void add_word_to_bucket(BUCKET **bucket, char *new_word);

BUCKET *create_bucket(int key);

BUCKET *get_bucket_with_hash(HASHTABLE *hashtable, int key);

void print_bucket(BUCKET *bucket, FILE *file);

int bucket_contains_word(BUCKET *bucket, char *word);

BUCKET *create_bucket_with_hash(HASHTABLE *hashtable, int key);

void remove_word_from_bucket(BUCKET *bucket, char *word);

int bucket_is_empty(BUCKET *bucket);

void remove_empty_bucket(HASHTABLE *hashtable, BUCKET *to_be_removed_bucket);


#endif //TEMA1_HASHTABLE_H
