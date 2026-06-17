#ifndef ZEROXCA75_H
#define ZEROXCA75_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

int remove_file(const char *path);
char *read_entire_file(const char* filename);
char *trim_whitespace(char *str);
char **str_split(char *str, char *delim);
size_t ptr_array_length(void **ptr);

#endif // ZEROxCA75_H
