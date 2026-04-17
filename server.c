#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define PORT 5000
#define KEY_LENGTH 32
#define STR_LENGTH 256

typedef enum {
    TABLE_NULL,
    TABLE_SWEATER,
    TABLE_NOTES,
    TABLE_PIECES,
    TABLE_PIECE_TYPE,
    TABLE_BRAND,
    TABLE_COLOR,
    TABLE_NECKLINE,
    TABLE_SLEEVES,
    TABLE_TYPE,
    TABLE_CONDITION,
    TABLE_SIZE,
    NUM_TABLES
} Tables;

const char* tables[NUM_TABLES] = {
    "NULL",
    "SWEATER",
    "NOTES",
    "PIECES",
    "PIECE_TYPE",
    "BRAND",
    "COLOR",
    "NECKLINE",
    "SLEEVES",
    "TYPE",
    "CONDITION",
    "SIZE",
};

typedef struct {
    int id;
    char cashmere_code[KEY_LENGTH];
    int brand_id;
    int color_id;
    int neckline_id;
    int sleeves_id;
    int type_id;
    int weight;
    int condition_id;
    int size_id;
    bool in_inventory;
    // some form of date
} Sweater;

typedef struct {
    int id;
    int sweater_id;
    char content[STR_LENGTH];
    // some form of date;
} Notes;

typedef struct {
    int id;
    int sweater_id;
    int piece_type_id;
    int original_weight;
    int current_weight;
    bool continuous;
    bool scraped;
    // some form of date;
} Pieces;

typedef struct {
    int id;
    char piece_type[KEY_LENGTH];
} PieceType;

typedef struct {
    int id;
    char brand[KEY_LENGTH];
} Brand;

typedef struct {
    int id;
    char color[KEY_LENGTH];
} Color;

typedef struct {
    int id;
    char neckline[KEY_LENGTH];
} Neckline;

typedef struct {
    int id;
    char sleeves[KEY_LENGTH];
} Sleeves;

typedef struct {
    int id;
    char type[KEY_LENGTH];
} Type;

typedef struct {
    int id;
    char condition[KEY_LENGTH];
} Condition;

typedef struct {
    int id;
    char size[KEY_LENGTH];
} Size;

// ----------------------------------------------------------------------------
// Start Miscellaneous Functions
char *trim_whitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

void normalize_key(char* out, char* in) {
    int index = 0;
    in = trim_whitespace(in);
    
    for(int i = 0; i < strlen(in); i++) {
        if (in[i] == '.' || in[i] == ',') {
            continue;
        } else if (in[i] >= 'a' && in[i] <= 'z') {
            out[index++] = in[i] - 32;
        } else {
            out[index++] = in[i];
        }
    }
    out[index] = '\0';
}

void remove_message_delimeter(char* buffer) {
    char* end = strstr(buffer, "\r\n\r\n");
    if (end) {
        *end = '\0';  // terminate string at start of delimiter
    }
}

ssize_t send_all(int socket, const char *data, size_t length) {
    size_t total_sent = 0;
    while (total_sent < length) {
        // Send from the current offset in the data buffer
        ssize_t sent = send(socket, data + total_sent, length - total_sent, 0);
        
        if (sent == -1) {
            return -1; // Handle error (e.g., connection lost)
        }
        total_sent += sent;
    }
    return total_sent;
}

void recv_all(const int client_id, char* buffer, int buffer_size) {
    int total_recieved = 0;
    int bytes_read;
    while ((bytes_read = recv(client_id, &buffer[total_recieved], buffer_size - total_recieved - 1, 0)) > 0) {
        total_recieved += bytes_read;
        buffer[total_recieved] = '\0';

        if (strstr(buffer, "\r\n\r\n")) {
            break; 
        }
        if (total_recieved >= buffer_size - 1) {
            break;
        }
    }
    if (bytes_read == 0) {
    // Connection was closed by the client
    } else if (bytes_read < 0) {
    // Handle error (e.g., perror("recv"))
    }
}

size_t send_message(const int client_fd, const char *message) {
    return send_all(client_fd, message, strlen(message));
}
// End Miscellaneous Functions

// ----------------------------------------------------------------------------
// Start Tokenizing Tables

void tokenize_sweater(Sweater *sweater) {

}

void tokenize_notes(Notes *note) {

}

void tokenize_pieces(Pieces *piece) {

}

void tokenize_piece_type(PieceType *piece_type) {

}

void tokenize_brand(Brand *brand) {

}

void tokenize_color(Color *color) {

}

void tokenize_neckline(Neckline *neckline) {

}

void tokenize_sleeves(Sleeves *sleeve) {

}

void tokenize_type(Type *type) {

}

void tokenize_condition(Condition *condition) {

}

void tokenize_size(Size *size) {

}
// End Tokenizing Tables

// ----------------------------------------------------------------------------
// Start Parsing Tokens
Tables table_from_string(const char* token) {
    for (int i = 0; i < NUM_TABLES; i++) {
        if (strcmp(token, tables[i]) == 0) {
            return (Tables)i;
        }
    }
    return TABLE_NULL; // fallback / error
}

void parse_sweater(char** tokens, Sweater *out) {
    
}

void parse_notes(char** tokens, Notes *out) {
    
}

void parse_pieces(char** tokens, Pieces *out) {
    
}

void parse_piece_type(char** tokens, PieceType *out) {
    
}

void parse_brand(char** tokens, Brand *out) {
    
}

void parse_color(char** tokens, Color *out) {
    
}

void parse_neckline(char** tokens, Neckline *out) {
    
}

void parse_sleeves(char** tokens, Sleeves *out) {
    
}

void parse_type(char** tokens, Type *out) {
    
}

void parse_condition(char** tokens, Condition *out) {
    
}

void parse_size(char** tokens, Size *out) {
    
}

void free_tokens(char** tokens) {
    if (tokens) {
        for (int i = 0; *(tokens + i); i++) {
            free(*(tokens + i));
        }
        free(tokens);
    }
}

char** str_split(char* str, char delimeter) {
    char** result = 0;
    size_t count = 0;
    char* last_delim = 0;
    char delim[2];
    delim[0] = delimeter;
    delim[1] = 0;
    
    char* tmp = strdup(str);
    char* tmp_start = tmp;
    if (!tmp) {
        return NULL;
    }
    
    while (*tmp)
    {
        if (delimeter == *tmp)
        {
            count++;
            last_delim = tmp;
        }
        tmp++;
    }

    count += last_delim < (str + strlen(str) - 1);

    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx = 0;
        char* token = strtok(str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(NULL, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
// End Parsing Tokens

//-----------------------------------------------------------------------------
// Start SQLite Functions

int db_insert_sweater(Sweater *sweater) {

}

int db_insert_notes(Notes *note) {

}

int db_insert_pieces(Pieces *piece) {

}

int db_insert_piece_type(PieceType *piece_type) {

}

int db_insert_brand(Brand *brand) {

}

int db_insert_color(Color *color) {

}

int db_insert_neckline(Neckline *neckline) {

}

int db_insert_sleeves(Sleeves *sleeves) {

}

int db_insert_type(Type *type) {

}

int db_insert_condition(Condition *condition) {

}

int db_insert_size(Size *size) {

}

// End SQLite Functions

void search_item(size_t client_fd, char** tokens) {
}

void info_item(size_t client_fd, char** tokens) {
}

// ----------------------------------------------------------------------------
// Start Add Item
void add_sweater(Sweater *sweater) {
    sweater->id = db_insert_sweater(sweater);
}

void add_notes(Notes *note) {

}

void add_pieces(Pieces *piece) {

}

void add_piece_type(PieceType *piece_type) {

}

void add_brand(Brand *brand) {

}

void add_color(Color *color) {

}

void add_neckline(Neckline *neckline) {

}

void add_sleeves(Sleeves *sleeve) {
    
}

void add_type(Type *type) {

}

void add_condition(Condition *condition) {

}

void add_size(Size *size) {

}

#define TABLE_IDX 1

void add_item(size_t client_fd, char** tokens) {
    Tables table = table_from_string(tokens[TABLE_IDX]);
    switch (table) {
        case TABLE_SWEATER:
            Sweater sweater = {0};
            parse_sweater(&tokens[2], &sweater);
            sweater.id = db_insert_sweater(&sweater);
            break;
        case TABLE_NOTES:
            Notes note = {0};
            parse_notes(&tokens[2], &note);
            note.id = db_insert_notes(&note);
            break;
        case TABLE_PIECES:
            Pieces piece = {0};
            parse_pieces(&tokens[2], &piece);
            piece.id = db_insert_pieces(&piece);
            break;
        case TABLE_PIECE_TYPE:
            PieceType piece_type = {0};
            parse_piece_type(&tokens[2], &piece_type);
            piece_type.id = db_insert_piece_type(&piece_type);
            break;
        case TABLE_BRAND:
            Brand brand = {0};
            parse_brand(&tokens[2], &brand);
            brand.id = db_insert_brand(&brand);
            break;
        case TABLE_COLOR:
            Color color = {0};
            parse_color(&tokens[2], &color);
            color.id = db_insert_color(&color);
            break;
        case TABLE_NECKLINE:
            Neckline neckline = {0};
            parse_neckline(&tokens[2], &neckline);
            neckline.id = db_insert_neckline(&neckline);
            break;
        case TABLE_SLEEVES:
            Sleeves sleeves = {0};
            parse_sleeves(&tokens[2], &sleeves);
            sleeves.id = db_insert_sleeves(&sleeves);
            break;
        case TABLE_TYPE:
            Type type = {0};
            parse_type(&tokens[2], &type);
            type.id = db_insert_type(&type);
            break;
        case TABLE_CONDITION:
            Condition condition = {0};
            parse_condition(&tokens[2], &condition);
            condition.id = db_insert_condition(&condition);
            break;
        case TABLE_SIZE:
            Size size = {0};
            parse_size(&tokens[2], &size);
            size.id = db_insert_size(&size);
            break;
        default:
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }
    
    
    send_message(client_fd, "Added item into database.");
}
// End Add Item

void edit_item(size_t client_fd, char** tokens) {
}

void remove_item(size_t client_fd, char** tokens) {
}

void hello_from_server(int client_fd) {
    printf("Connection Accepted.\n");
    send_message(client_fd, "Hello from the Cashmere Database server!\r\n\r\n");
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[8192] = {0};
    bool exit_client = false;

    // 1. Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Bind to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // accept connections from any LAN IP
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 3. Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d\n", PORT);

    // 4. Accept connections in a loop
    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
       
        hello_from_server(client_fd);
        recv_all(client_fd, buffer, sizeof(buffer));
        printf("%s\n", buffer);
       
        while (1) {
            recv_all(client_fd, buffer, sizeof(buffer));
            remove_message_delimeter(buffer);
            // TODO: want to add a way to have multiple connections
            /* TODO: Merge out of main function into a handle_command helper*/
            printf("%s\n", buffer);
            char** tokens = str_split(buffer, ':');
            // TODO: add logging so i know what commands are being used with what tokens
            // TODO: token count + tokens safety
            // TODO: we should know how many tokens are required for a search or an add just like a C function parameters.
            if (tokens) {
                printf("Tokens: \n");
                int i;
                // Tokens are nothing being printed but it knows it is SEARCHING
                for (i = 0; *(tokens + i); i++) {
                    printf("%s\n", *(tokens + i));
                }

                if (strcmp(tokens[0], "SEARCH ITEM") == 0) {
                    search_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "INFO ITEM") == 0) {
                    info_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "ADD ITEM") == 0) {
                    add_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "EDIT ITEM") == 0) {
                    edit_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "REMOVE ITEM") == 0) {
                    remove_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "EXIT") == 0) {
                    free_tokens(tokens);
                    close(client_fd);
                    break;
                }
                else {
                    printf("WHAT HAVE YOU DONE LUKAS!!\n");
                }
                free_tokens(tokens);
                /* End of handle_command helper*/
            }
        }
    }

    close(server_fd);
    return 0;
}
