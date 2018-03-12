
#ifndef TEMA1_HASHTABLE_H
#define TEMA1_HASHTABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "utils.h"
#include "hashtable_interface.h"


void add_word_to_bucket(BUCKET **bucket, char *new_word);

BUCKET *get_bucket_with_hash(HASHTABLE *hashtable, int key);

void print_bucket(BUCKET *bucket, FILE *file);

int bucket_contains_word(BUCKET *bucket, char *word);

void remove_word_from_bucket(BUCKET *bucket, char *word);

int bucket_is_empty(BUCKET *bucket);

#endif
