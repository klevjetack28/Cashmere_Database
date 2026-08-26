#include "misc.h"

int str_split(char *str, const char *delim, char **tokens, int max_tokens) {
    int count = 0;
    char *saveptr = NULL;
    char *token = strtok_r(str, delim, &saveptr);

    while (token != NULL && count < max_tokens) {
        tokens[count++] = token;
        token = strtok_r(NULL, delim, &saveptr);
    }

    return count;
}
