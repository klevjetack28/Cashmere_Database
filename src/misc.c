#include "misc.h"

int str_split(char *str, const char *delim, char **tokens, int max_tokens) {
    int count = 0;
    char *saveptr = NULL;
    char *token = strtok_r(str, delim, &saveptr);

    while (token != NULL && count < max_tokens) {
        tokens[count++] = token;
        token = strtok_r(NULL, delim, &saveptr);
    }

    if (token != NULL) {
        return -1;
    }

    return count;
}

bool str_to_int(const char *str, int *value_out) {
    if (str == NULL || value_out == NULL || str[0] == '\0') {
        return false;
    }

    errno = 0;
    char *end = NULL;
    long value = strtol(str, &end, 10);

    if (errno == ERANGE || end == str || *end != '\0' ||
        value < INT_MIN || value > INT_MAX) {
        return false;
    }

    *value_out = (int)value;
    return true;
}
