#include "misc.h"

char **str_split(char *str, char *delim) {
    char **result = malloc(2 * STR_LENGTH * sizeof(char*));
    int i = 0;

    char *token = strtok(str, delim);
    while (token && i < KEY_LENGTH) {
        result[i++] = strdup(token);
        token = strtok(NULL, delim);
    }

    result[i] = NULL;
    return result;
}
