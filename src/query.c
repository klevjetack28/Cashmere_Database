#include "query.h"

int normalize_key(char *out, char *in) {
    int index = 0;
    in = trim_whitespace(in);
    
    for(int i = 0; i < strlen(in); i++) {
        if (in[i] == '.' || in[i] == ',') {
            continue;
        } else if (in[i] >= 'a' && in[i] <= 'z') {
            out[index++] = in[i] + UPPERCASE_OFFSET;
        } else {
            out[index++] = in[i];
        }
    }
    out[index] = '\0';
}
