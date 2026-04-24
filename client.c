#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>   
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdbool.h>

#define PORT 5000
#define KEY_LENGTH 32
#define STR_LENGTH 256

typedef enum {
    TABLE_NULL,
    TABLE_SWEATER,
    TABLE_NOTE,
    TABLE_PIECE,
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
    "NOTE",
    "PIECE",
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
    // some form of date
} Sweater;

typedef struct {
    int id;
    int sweater_id;
    char content[STR_LENGTH];
    // some form of date;
} Note;

typedef struct {
    int id;
    int sweater_id;
    int piece_type_id;
    int original_weight;
    int current_weight;
    int continuous;
    int scraped;
    // some form of date;
} Piece;

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
// Start Sweater Table

void tokenize_sweater(Sweater* s) {
    
}
/*
void print_sweater(Sweater* s) {
    printf("%s: ", s.cashmere_code);
    printf("%s ", search_brand(s->brand_id));
    printf("%s ", search_color(s->color_id));
    printf("%s ", search_neckline(s->neckline_id));
    printf("%s ", search_type(s->type_id));
    printf("with %s sleeves ", search_sleeves(s->sleeves_id));
    printf("in %s condition ", search_condition(s->condition_id));
    printf("size %s.", search_size(s->size_id));
}
*/// End Sweater Table

// ----------------------------------------------------------------------------
// Start Miscellaneous Functions

// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
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
// Start Get Input Functions
void get_input(char* input) {
    char buffer[KEY_LENGTH] = {0};
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    normalize_key(input, buffer);
}

int get_int_input(char* input) {
    get_input(input);
    return atoi(input);
}

char* get_string_input(char* input) {
    get_input(input);
}

void get_add_piece_input(char* input, Piece* piece) {
    printf("Sweater ID: ");
    piece->sweater_id = get_int_input(input);
    printf("Piece Type ID: ");
    piece->piece_type_id = get_int_input(input);
    printf("Original Weight: ");
    piece->original_weight = get_int_input(input);
    piece->current_weight = piece->original_weight;
    printf("Continuos True(1)/False(0): ");
    piece->continuous = get_int_input(input);
    piece->scraped = 0; 
}

void get_search_piece_input(char* input, Piece* piece) {

}

void get_add_note_input(char* input, Note* note) {
    printf("SweaterID: ");
    note->sweater_id = get_int_input(input);
    printf("Enter Contents: ");
    get_string_input(note->content);
}

void get_search_note_input(char* input, Note* note) {

}

void get_add_sweater_input(char* input, Sweater* sweater) {
    // get_cashmere_code(sweater.cashmere_code);
    printf("BrandID: ");
    sweater->brand_id = get_int_input(input);
    printf("ColorID: ");
    sweater->color_id = get_int_input(input);
    printf("NecklineID: ");
    sweater->neckline_id = get_int_input(input);
    printf("SleevesID: ");
    sweater->sleeves_id = get_int_input(input);
    printf("TypeID: ");
    sweater->type_id = get_int_input(input);
    printf("Weight(g): ");
    sweater->weight = get_int_input(input);
    printf("ConditionID: ");
    sweater->condition_id = get_int_input(input);
    printf("SizeID: ");
    sweater->size_id = get_int_input(input);
}

void get_search_sweater_input(char* input, Sweater* sweater) {
    
}
// End Get Input Functions


void system_status() {

}

void logs() {

}

void print_table_options() {
    for (int i = 1; i < (int)NUM_TABLES; i++) {
        printf("%d> %s\n", i, tables[i]);
    }
}

void add_token(char* token_str, char* token) {
    if (token_str[0] == 0) {
        sprintf(token_str, "%s", token);
    } else {
        strcat(token_str, ":");
        strcat(token_str, token);
    }
}

void exit_db(char* token_str) {
    add_token(token_str, "EXIT");
}

// ----------------------------------------------------------------------------
// Start Remove Item

void remove_item(char* token_str) {
    add_token(token_str, "REMOVE ITEM");
    printf("REMOVE_ITEM\n");
}
// End Remove Item

// ----------------------------------------------------------------------------
// Start Edit Item

void edit_item(char* token_str) {
    add_token(token_str, "EDIT ITEM");
}
// End Edit Item

// ----------------------------------------------------------------------------
// Start Add Item

void add_sweater(char* token_str, Sweater* sweater) {
    add_token(token_str, "SWEATER");
    char token[KEY_LENGTH] = {0};
    sprintf(token, "BRAND:%d", sweater->brand_id);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "COLOR:%d", sweater->color_id);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "NECKLINE:%d", sweater->neckline_id);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "SLEEVES:%d", sweater->sleeves_id);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "TYPE:%d", sweater->type_id);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "WEIGHT:%d", sweater->weight);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "CONDITION:%d", sweater->condition_id);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "SIZE:%d", sweater->size_id);
    add_token(token_str, token);
    token[0] = 0;
}

void add_note(char* token_str, Note* note) {
    add_token(token_str, "NOTE");
    char token[STR_LENGTH * 2] = {0};
    sprintf(token, "NOTE:%d", note->sweater_id);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "CONTENT:%s", note->content);
    add_token(token_str, token);
    token[0] = 0;
}

void add_piece(char* token_str, Piece* piece) {
    add_token(token_str, "PIECE");
    char token[STR_LENGTH] = {0};
    sprintf(token, "PIECE:%d", piece->sweater_id);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "PIECE TYPE:%d", piece->piece_type_id);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "ORIGINAL WEIGHT:%d", piece->original_weight);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "CURRENT WEIGHT:%d", piece->current_weight);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "CONTINUOUS:%d", piece->continuous);
    add_token(token_str, token);
    token[0] = 0;
    sprintf(token, "SCRAPED:%d", piece->scraped);
    add_token(token_str, token);
    token[0] = 0;

}

void add_piece_type(char* token_str, char *input) {
    add_token(token_str, "PIECE TYPE");
    char tokens[KEY_LENGTH] = {0};
    sprintf(tokens, "PIECE TYPE:%s", input);
    add_token(token_str, tokens);
}

void add_brand(char* token_str, char *input) {
    add_token(token_str, "BRAND");
    char tokens[KEY_LENGTH] = {0};
    sprintf(tokens, "BRAND:%s", input);
    add_token(token_str, tokens);
}

void add_color(char* token_str, char *input) {
    add_token(token_str, "COLOR");
    char tokens[KEY_LENGTH] = {0};
    sprintf(tokens, "COLOR:%s", input);
    add_token(token_str, tokens);
}

void add_sleeves(char* token_str, char *input) {
    add_token(token_str, "SLEEVES");
    char tokens[KEY_LENGTH] = {0};
    sprintf(tokens, "SLEEVES:%s", input);
    add_token(token_str, tokens);
}

void add_neckline(char* token_str, char *input) {
    add_token(token_str, "NECKLINE");
    char tokens[KEY_LENGTH] = {0};
    sprintf(tokens, "NECKLINE:%s", input);
    add_token(token_str, tokens);
}

void add_type(char* token_str, char *input) {
    add_token(token_str, "TYPE");
    char tokens[KEY_LENGTH] = {0};
    sprintf(tokens, "TYPE:%s", input);
    add_token(token_str, tokens);
}

void add_condition(char* token_str, char *input) {
    add_token(token_str, "CONDITION");
    char tokens[KEY_LENGTH] = {0};
    sprintf(tokens, "CONDITION:%s", input);
    add_token(token_str, tokens);
}

void add_size(char* token_str, char *input) {
    add_token(token_str, "SIZE");
    char tokens[KEY_LENGTH] = {0};
    sprintf(tokens, "SIZE:%s", input);
    add_token(token_str, tokens);
}

void add_item(size_t server_fd, char* token_str) {
    add_token(token_str, "ADD ITEM");
    bool adding = true;
    static char buffer[KEY_LENGTH] = {0};
    while (adding) {
        print_table_options();

        char table_id[KEY_LENGTH];
        Tables table = (Tables)get_int_input(table_id);
        char input[STR_LENGTH] = {0};
        switch(table) {
            case TABLE_SWEATER:
                Sweater sweater;
                get_add_sweater_input(input, &sweater);
                add_sweater(token_str, &sweater);
                break;
            case TABLE_NOTE:
                Note note;
                get_add_note_input(input, &note);
                add_note(token_str, &note);
                break;
            case TABLE_PIECE:
                Piece piece;
                get_add_piece_input(input, &piece);
                add_piece(token_str, &piece);
                break;
            case TABLE_PIECE_TYPE:
                printf("Enter Piece Type: ");
                get_string_input(input);
                add_piece_type(token_str, input);
                break;
            case TABLE_BRAND:
                printf("Enter Brand: ");
                get_string_input(input);
                add_brand(token_str, input);
                break;
            case TABLE_COLOR:
                printf("Enter Color: ");
                get_string_input(input);
                add_color(token_str, input);
                break;
            case TABLE_NECKLINE:
                printf("Enter Neckline: ");
                get_string_input(input);
                add_neckline(token_str, input);
                break;
            case TABLE_SLEEVES:
                printf("Enter Sleeves: ");
                get_string_input(input);
                add_sleeves(token_str, input);
                break;
            case TABLE_TYPE:
                printf("Enter Type: ");
                get_string_input(input);
                add_type(token_str, input);
                break;
            case TABLE_CONDITION:
                printf("Enter Condition: ");
                get_string_input(input);
                add_condition(token_str, input);
                break;
            case TABLE_SIZE:
                printf("Enter Size: ");
                get_string_input(input);
                add_size(token_str, input);
                break;
            default:
                printf("Something went wrong...\n");
                continue;
        }
        adding = false;
    }
}
// End Add Item


// ----------------------------------------------------------------------------
// Start Info Item

void info_item(char* token_str) {
    add_token(token_str, "INFO ITEM");
}
// End Info Item

// ----------------------------------------------------------------------------
// Start Search Item
void search_size(char* token_str, int size_id) {
    char tokens[KEY_LENGTH];
    sprintf(tokens, "SIZE:%d", size_id);
    add_token(token_str, tokens);
}

void search_condition(char* token_str, int size_id) {
    char tokens[KEY_LENGTH];
    sprintf(tokens, "CONDITION:%d", size_id);
    add_token(token_str, tokens);
}

void search_type(char* token_str, int type_id) {
    char tokens[KEY_LENGTH];
    sprintf(tokens, "TYPE:%d", type_id);
    add_token(token_str, tokens);
}

void search_sleeves(char* token_str, int sleeves_id) {
    char tokens[KEY_LENGTH];
    sprintf(tokens, "SLEEVES:%d", sleeves_id);
    add_token(token_str, tokens);
}

void search_neckline(char* token_str, int neckline_id) {
    char tokens[KEY_LENGTH];
    sprintf(tokens, "NECKLINE:%d", neckline_id);
    add_token(token_str, tokens);
}

void search_color(char* token_str, int color_id) {
    char tokens[KEY_LENGTH];
    sprintf(tokens, "COLOR:%d", color_id);
    add_token(token_str, tokens);
}

void search_brand(char* token_str, int brand_id) {
    char tokens[KEY_LENGTH];
    sprintf(tokens, "BRAND:%d", brand_id);
    add_token(token_str, tokens);
}

void search_piece_type(char* token_str, int piece_type_id) {
    char tokens[KEY_LENGTH];
    sprintf(tokens, "PIECE TYPE:%d", piece_type_id);
    add_token(token_str, tokens);
}

void search_piece(char* token_str) {
    // TODO
}

void search_note(char* token_str) {
    // TODO
}

void search_sweater(char* token_str) {
    // TODO
}

void search_item(char* token_str) {
    add_token(token_str, "SEARCH ITEM");
    bool searching = true;
    while (searching) {
        print_table_options();

        char table_id[KEY_LENGTH] = {0};
        Tables table = (Tables)get_int_input(table_id);
        char input[KEY_LENGTH * 2] = {0};
        switch(table) {
            case TABLE_SWEATER:
                printf("Searching for sweater.");
                search_sweater(token_str);
                break;
            case TABLE_NOTE:
                printf("Searching for sweater.");
                search_note(token_str);
                break;
            case TABLE_PIECE:
                search_piece(token_str);
                break;
            case TABLE_PIECE_TYPE:
                printf("Enter Piece Type ID: ");
                search_piece_type(token_str, get_int_input(input));
                break;
            case TABLE_BRAND:
                printf("Enter Brand ID: ");
                search_brand(token_str, get_int_input(input));
                break;
            case TABLE_COLOR:
                printf("Enter Color ID: ");
                search_color(token_str, get_int_input(input));
                break;
            case TABLE_NECKLINE:
                printf("Enter Neckline ID: ");
                search_neckline(token_str, get_int_input(input));
                break;
            case TABLE_SLEEVES:
                printf("Enter Sleeves ID: ");
                search_sleeves(token_str, get_int_input(input));
                break;
            case TABLE_TYPE:
                printf("Enter Type ID: ");
                search_type(token_str, get_int_input(input));
                break;
            case TABLE_CONDITION:
                printf("Enter Condition ID: ");
                search_condition(token_str, get_int_input(input));
                break;
            case TABLE_SIZE:
                printf("Enter Size ID: ");
                search_size(token_str, get_int_input(input));
                break;
            default:
                printf("Something went wrong...\n");
                continue;
        }
        searching = false;
    }
}
// End Search Item

void database_menu() {
    printf("1> Search\n2> Info\n3> Add Item\n4> Edit\n5> Remove\n6> Exit\n");
}

void cashmere_database(size_t server_fd) {
    char buffer[STR_LENGTH] = {0};
    bool exit = false;
    while(!exit) {

        database_menu();

        char token_str[STR_LENGTH] = {0};
        char c = getchar();
        getchar();
        switch (c) {
            case '1':
                search_item(token_str);
                break;
            case '2':
                info_item(token_str);
                break;
            case '3':
                add_item(server_fd, token_str);
                break;
            case '4':
                edit_item(token_str);
                break;
            case '5':
                remove_item(token_str);
                break;
            case '6':
                exit_db(token_str);
                exit = true;
                break;
            default:
        }
    
        strcat(token_str, "\r\n\r\n");
        printf("%s\n", token_str);
    
        send_all(server_fd, token_str, strlen(token_str));
        recv_all(server_fd, buffer, sizeof(buffer));
        printf("%s\n", buffer);
    }
}

int main() {
    int sock;
    struct sockaddr_in server;
    static char buffer[8192] = {0};
    bool exit_client = false;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Connect failed");
        return 1;
    }

    recv_all(sock, buffer, sizeof(buffer));
    printf("%s", buffer);
    char* id = "Client Lukas Laptop is joinging the server.\r\n\r\n";
    send_all(sock, id, strlen(id));
    while (!exit_client) {
        printf("1> Cashmere Database\n2> Logs\n3> System Status\n4> Exit\n5> BONUS!!! Add two numbers.\n");
                    
        switch(getchar()) {
            case '1':
                getchar();
                printf("Loading Cashmere Database...\n");
                cashmere_database(sock);
                break;
            case '2':
                // logs();
                break;
            case '3':
                // system_status();
                break;
            case '4':
                exit_client = true;
                break;
            case '5':
                getchar();
                printf("Enter two positive, single digit, numbers.\nNumbers: ");
                char num1 = getchar();
                getchar();
                char num2 =getchar();
                char message[256];
                sprintf(message, "ADD:%c:%c\r\n\r\n", num1, num2);
                send_all(sock, message, strlen(message));
                recv_all(sock, buffer, sizeof(buffer));
                printf("%s\n", buffer);
                break;
            default:
        }
    }

    close(sock);
    return 0;
}
