

#ifndef TEMA1_FILE_UTILS_H
#define TEMA1_FILE_UTILS_H

#include <stdio.h>
#include <string.h>
#include "utils.h"

FILE *get_output_file(char *file_name) {
	FILE *file;
	if (file_name != NULL) {
		file = fopen(file_name, "a");
		DIE(file < 0, "Opening file failed");
	} else
		file = stdout;

	return file;
}

#endif
