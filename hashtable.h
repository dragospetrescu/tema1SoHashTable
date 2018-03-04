//
// Created by dragos on 05.03.2018.
//

#ifndef TEMA1_HASHTABLE_H
#define TEMA1_HASHTABLE_H


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
    int key_size;
    BUCKET *first_bucket;
} HASHTABLE;


#endif //TEMA1_HASHTABLE_H
