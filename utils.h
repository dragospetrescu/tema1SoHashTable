//
// Created by dragos on 09.03.2018.
//

#ifndef TEMA1_UTILS_H_H
#define TEMA1_UTILS_H_H


#include <errno.h>
#include <stdlib.h>

#define DIE(assertion, call_description)                \
    do {                                \
        if (assertion) {                    \
            fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);        \
			perror(call_description);            \
			exit(errno);                    \
        }                            \
    } while (0)

#endif //TEMA1_UTILS_H_H