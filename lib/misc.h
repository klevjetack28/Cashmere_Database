#ifndef MISC_H
#define MISC_H

#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

int str_split(char *str, const char *delim, char **tokens, int max_tokens);
bool str_to_int(const char *str, int *value_out);

#endif // MISC_H
