#include "0xca75.h"

char* read_entire_file(const char* filename) {
    // 1. Open the file in binary mode to prevent line-ending translations
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // 2. Move the file pointer to the end to find the size
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error seeking file");
        fclose(file);
        return NULL;
    }

    long file_size = ftell(file);
    if (file_size < 0) {
        perror("Error telling file size");
        fclose(file);
        return NULL;
    }

    // 3. Reset the file pointer back to the beginning
    rewind(file);

    // 4. Allocate memory for the file content plus a null terminator
    char* buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // 5. Read the contents into the allocated buffer
    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read < (size_t)file_size) {
        if (ferror(file)) {
            perror("Error reading file");
            free(buffer);
            fclose(file);
            return NULL;
        }
    }

    // 6. Add the null terminator and clean up
    buffer[bytes_read] = '\0';
    fclose(file);

    return buffer;
}


char *trim_whitespace(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

size_t ptr_array_length(void **ptr) {
    size_t count = 0; 
    while (ptr[count] != NULL) { 
        count++; 
    }
    
    return count;
}
