#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#include "0xca75.h"
#include "network.h"
#include "packet.h"
#include "payload.h"
#include "database.h"
#include "constants.h"
#include "db_tables.h"
#include "misc.h"

#define PORT 5000


void normalize_key(char *out, char *in) {
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

void add_token(char* token_str, char* token) {
    if (token_str[0] == 0) {
        sprintf(token_str, "%s", token);
    } else {
        strcat(token_str, ":");
        strcat(token_str, token);
    }
}

// ----------------------------------------------------------------------------
// Start Tokenizing Table

void tokenize_sweater(char *token_str, Sweater *sweater) {
    char tmp[KEY_LENGTH] = {0};
    add_token(token_str, "SWEATER");
    add_token(token_str, "ID");
    sprintf(tmp, "%d", sweater->id);
    add_token(token_str, tmp);
    add_token(token_str, "BRAND ID");
    add_token(token_str, sweater->brand_id);
    add_token(token_str, "COLOR ID");
    add_token(token_str, sweater->color_id);
    add_token(token_str, "NECKLINE ID");
    add_token(token_str, sweater->neckline_id);
    add_token(token_str, "SLEEVES ID");
    add_token(token_str, sweater->sleeves_id);
    add_token(token_str, "TYPE ID");
    add_token(token_str, sweater->type_id);
    add_token(token_str, "CONDITION ID");
    add_token(token_str, sweater->condition_id);
    add_token(token_str, "SIZE");
    add_token(token_str, sweater->size_id);
}

void tokenize_note(char *token_str, Note *note) {
    char tmp[KEY_LENGTH] = {0};
    add_token(token_str, "NOTE");
    add_token(token_str, "ID");
    sprintf(tmp, "%d", note->id);
    add_token(token_str, tmp);
    add_token(token_str, "SWEATER ID");
    add_token(token_str, note->sweater_id);
    add_token(token_str, "CONTENT");
    add_token(token_str, note->content);
}

void tokenize_piece(char *token_str, Piece *piece) {
    char tmp[KEY_LENGTH] = {0};
    add_token(token_str, "PIECE");
    add_token(token_str, "ID");
    sprintf(tmp, "%d", piece->id);
    add_token(token_str, tmp);
    add_token(token_str, "SWEATER ID");
    add_token(token_str, piece->sweater_id);
    add_token(token_str, "PIECE ID");
    add_token(token_str, piece->piece_type_id);
    add_token(token_str, "ORIGINAL WEIGHT");
    add_token(token_str, piece->original_weight);
    add_token(token_str, "CURRENT WEIGHT");
    add_token(token_str, piece->current_weight);
    add_token(token_str, "CONTINUOUS");
    add_token(token_str, piece->continuous);
    add_token(token_str, "SCRAPED");
    add_token(token_str, piece->scraped);
}

void tokenize_piece_type(char *token_str, PieceType *piece_type) {
    char tmp[KEY_LENGTH] = {0};
    add_token(token_str, "PIECE_TYPE");
    add_token(token_str, "ID");
    sprintf(tmp, "%d", piece_type->id);
    add_token(token_str, tmp);
    add_token(token_str, "PIECE_TYPE");
    add_token(token_str, piece_type->piece_type);
}

void tokenize_brand(char *token_str, Brand *brand) {
    char tmp[KEY_LENGTH] = {0};
    add_token(token_str, "BRAND");
    add_token(token_str, "ID");
    sprintf(tmp, "%d", brand->id);
    add_token(token_str, tmp);
    add_token(token_str, "BRAND");
    add_token(token_str, brand->brand);
}

void tokenize_color(char *token_str, Color *color) {
    char tmp[KEY_LENGTH] = {0};
    add_token(token_str, "COLOR");
    add_token(token_str, "ID");
    sprintf(tmp, "%d", color->id);
    add_token(token_str, tmp);
    add_token(token_str, "COLOR");
    add_token(token_str, color->color);

}

void tokenize_neckline(char *token_str, Neckline *neckline) {
    char tmp[KEY_LENGTH] = {0};
    add_token(token_str, "NECKLINE");
    add_token(token_str, "ID");
    sprintf(tmp, "%d", neckline->id);
    add_token(token_str, tmp);
    add_token(token_str, "NECKLINE");
    add_token(token_str, neckline->neckline);
}

void tokenize_sleeves(char *token_str, Sleeves *sleeves) {
    char tmp[KEY_LENGTH] = {0};
    add_token(token_str, "SLEEVES");
    add_token(token_str, "ID");
    sprintf(tmp, "%d", sleeves->id);
    add_token(token_str, tmp);
    add_token(token_str, "SLEEVES");
    add_token(token_str, sleeves->sleeves);
}

void tokenize_type(char *token_str, Type *type) {
    char tmp[KEY_LENGTH] = {0};
    add_token(token_str, "TYPE");
    add_token(token_str, "ID");
    sprintf(tmp, "%d", type->id);
    add_token(token_str, tmp);
    add_token(token_str, "TYPE");
    add_token(token_str, type->type);
}

void tokenize_condition(char *token_str, Condition *condition) {
    char tmp[KEY_LENGTH] = {0};
    add_token(token_str, "CONDITION");
    add_token(token_str, "ID");
    sprintf(tmp, "%d", condition->id);
    add_token(token_str, tmp);
    add_token(token_str, "CONDITION");
    add_token(token_str, condition->condition);
}

void tokenize_size(char *token_str, Size *size) {
    char tmp[KEY_LENGTH] = {0};
    add_token(token_str, "SIZE");
    add_token(token_str, "ID");
    sprintf(tmp, "%d", size->id);
    add_token(token_str, tmp);
    add_token(token_str, "SIZE");
    add_token(token_str, size->size);
}
// End Tokenizing Table

// ----------------------------------------------------------------------------
// Start Parsing Tokens
Table table_from_string(const char *token_str) {
    for (int i = 0; i < NUM_TABLES; i++) {
        if (strcmp(token_str, TABLE_NAMES[i]) == 0) {
            return (Table)i;
        }
    }
    return TABLE_NULL;
}

void parse_search_sweater(char **tokens, Sweater *sweater) {

}

void parse_search_note(char **tokens, Note *note) {

}

void parse_search_piece(char **tokens, Piece *piece) {

}

void parse_search_piece_type(char **tokens, PieceType *piece_type) {
    if (strcmp(tokens[0], "ALL") == 0) {
        piece_type->id = -1;
    }
    else {
        piece_type->id = atoi(tokens[2]);
    }
}

void parse_search_brand(char **tokens, Brand *brand) {
    if (strcmp(tokens[0], "ALL") == 0) {
        brand->id = -1;
    }
    else {
        brand->id = atoi(tokens[2]);
    }
}

void parse_search_color(char **tokens, Color *color) {
    if (strcmp(tokens[0], "ALL") == 0) {
        color->id = -1;
    }
    else {
        color->id = atoi(tokens[2]);
    }
}

void parse_search_neckline(char **tokens, Neckline *neckline) {
    if (strcmp(tokens[0], "ALL") == 0) {
        neckline->id = -1;
    }
    else {
        neckline->id = atoi(tokens[2]);
    }
}

void parse_search_sleeves(char **tokens, Sleeves *sleeves) {
    if (strcmp(tokens[0], "ALL") == 0) {
        sleeves->id = -1;
    }
    else {
        sleeves->id = atoi(tokens[2]);
    }
}

void parse_search_type(char **tokens, Type *type) {
    if (strcmp(tokens[0], "ALL") == 0) {
        type->id = -1;
    }
    else {
        type->id = atoi(tokens[2]);
    }
}

void parse_search_condition(char **tokens, Condition *condition) {
    if (strcmp(tokens[0], "ALL") == 0) {
        condition->id = -1;
    }
    else {
        condition->id = atoi(tokens[2]);
    }
}

void parse_search_size(char **tokens, Size *size) {
    if (strcmp(tokens[0], "ALL") == 0) {
        size->id = -1;
    }
    else {
        size->id = atoi(tokens[2]);
    }
}

void parse_add_sweater(char **tokens, Sweater *sweater) {
    sweater->brand_id = atoi(tokens[1]);
    sweater->color_id = atoi(tokens[3]);
    sweater->neckline_id = atoi(tokens[5]);
    sweater->sleeves_id = atoi(tokens[7]);
    sweater->type_id = atoi(tokens[9]);
    sweater->weight = atoi(tokens[11]);
    sweater->condition_id = atoi(tokens[13]);
    sweater->size_id = atoi(tokens[15]);
}

void parse_add_note(char **tokens, Note *note) {
    note->sweater_id = atoi(tokens[1]);
    strcpy(note->content, tokens[3]);
}

void parse_add_piece(char **tokens, Piece *piece) {
    piece->sweater_id = atoi(tokens[1]);
    piece->piece_type_id = atoi(tokens[3]);
    piece->original_weight = atoi(tokens[5]);
    piece->current_weight = atoi(tokens[7]);
    piece->continuous = atoi(tokens[9]); 
    piece->scraped = atoi(tokens[11]);
}

void parse_add_piece_type(char **tokens, PieceType *piece_type) {
    strcpy(piece_type->piece_type, tokens[1]);
}

void parse_add_brand(char **tokens, Brand *brand) {
    strcpy(brand->brand, tokens[1]);
}

void parse_add_color(char **tokens, Color *color) {
    strcpy(color->color, tokens[1]);
}

void parse_add_neckline(char **tokens, Neckline *neckline) {
    strcpy(neckline->neckline, tokens[1]);
}

void parse_add_sleeves(char **tokens, Sleeves *sleeves) {
    strcpy(sleeves->sleeves, tokens[1]);
}

void parse_add_type(char **tokens, Type *type) {
    strcpy(type->type, tokens[1]);
}

void parse_add_condition(char **tokens, Condition *condition) {
    strcpy(condition->condition, tokens[1]);
}

void parse_add_size(char **tokens, Size *size) {
    strcpy(size->size, tokens[0]);
}

void free_tokens(char **tokens) {
    if (tokens) {
        for (int i = 0; *(tokens + i); i++) {
            free(*(tokens + i));
        }
        free(tokens);
    }
}


// End Parsing Tokens

//-----------------------------------------------------------------------------
// Start SQLite Functions

// End SQLite Functions

// ----------------------------------------------------------------------------
// Start Search Item

typedef enum {
    SEARCH_BY_ID,
    SEARCH_BY_FILTER,
    SEARCH_ALL,
    NUM_SEARCH_TYPE
} TypeSearch;

const char *type_search_token[NUM_SEARCH_TYPE] = {
    "ID",
    "FILTER",
    "ALL"
};

TypeSearch type_search_from_string(const char* string) {
    for (int i = 0; i < NUM_SEARCH_TYPE; i++) {
        if (strcmp(string, type_search_token[i]) == 0) {
            return (TypeSearch)i;
        }
    }
}

void search_sweater(size_t client_fd, Sweater *sweater, TypeSearch type_search) {
    char token_str[BUFFER_LENGTH] = {0};
    switch (type_search) {
        case SEARCH_BY_ID:
            db_select_sweater(sweater);
            break;
        case SEARCH_ALL:
            db_select_all_sweater();          
            break;
        case SEARCH_BY_FILTER:
        default:
    }
    strcat(token_str, "\r\n\r\n");
    //send_message(client_fd, token_str);   
}

void search_note(size_t client_fd, Note *note, TypeSearch type_search) {
    char token_str[BUFFER_LENGTH] = {0};
    switch (type_search) {
        case SEARCH_BY_ID:
            db_select_note(note);
            break;
        case SEARCH_ALL:
            db_select_all_note();          
            break;
        case SEARCH_BY_FILTER:
        default:
    }
    strcat(token_str, "\r\n\r\n");
    //send_message(client_fd, token_str);
}

void search_piece(size_t client_fd, Piece *piece, TypeSearch type_search) {
    char token_str[BUFFER_LENGTH] = {0};
    switch (type_search) {
        case SEARCH_BY_ID:
            db_select_piece(piece);
            break;
        case SEARCH_ALL:
            db_select_all_piece();          
            break;
        case SEARCH_BY_FILTER:
        default:
    }
    strcat(token_str, "\r\n\r\n");
    //send_message(client_fd, token_str);
}

void search_piece_type(size_t client_fd, PieceType *piece_type, TypeSearch type_search) {
    char token_str[BUFFER_LENGTH] = {0};
    switch (type_search) {
        case SEARCH_BY_ID:
            db_select_piece_type(piece_type);
            break;
        case SEARCH_ALL:
            db_select_all_piece_type();          
            break;
        case SEARCH_BY_FILTER:
        default:
    }
    strcat(token_str, "\r\n\r\n");
    //send_message(client_fd, token_str);
}

void search_brand(size_t client_fd, Brand *brand, TypeSearch type_search) {
    char token_str[BUFFER_LENGTH] = {0};
    switch (type_search) {
        case SEARCH_BY_ID:
            db_select_brand(brand);
            break;
        case SEARCH_ALL:
            db_select_all_brand();          
            break;
        case SEARCH_BY_FILTER:
        default:
            printf("SOMETHING WRONG\n");
    }
    strcat(token_str, "\r\n\r\n");
    //send_message(client_fd, token_str);
}

void search_color(size_t client_fd, Color *color, TypeSearch type_search) {
    char token_str[BUFFER_LENGTH] = {0};
    switch (type_search) {
        case SEARCH_BY_ID:
            db_select_color(color);
            break;
        case SEARCH_ALL:
            db_select_all_color();          
            break;
        case SEARCH_BY_FILTER:
        default:
    }
    strcat(token_str, "\r\n\r\n");
    //send_message(client_fd, token_str);
}

void search_neckline(size_t client_fd, Neckline *neckline, TypeSearch type_search) {
    char token_str[BUFFER_LENGTH] = {0};
    switch (type_search) {
        case SEARCH_BY_ID:
            db_select_neckline(neckline);
            break;
        case SEARCH_ALL:
            db_select_all_neckline();          
            break;
        case SEARCH_BY_FILTER:
        default:
    }
    strcat(token_str, "\r\n\r\n");
    //send_message(client_fd, token_str);
}

void search_sleeves(size_t client_fd, Sleeves *sleeves, TypeSearch type_search) {
    char token_str[BUFFER_LENGTH] = {0};
    switch (type_search) {
        case SEARCH_BY_ID:
            db_select_sleeves(sleeves);
            break;
        case SEARCH_ALL:
            db_select_all_sleeves();          
            break;
        case SEARCH_BY_FILTER:
        default:
    }
    strcat(token_str, "\r\n\r\n");
    //send_message(client_fd, token_str);
}

void search_type(size_t client_fd, Type *type, TypeSearch type_search) {
    char token_str[BUFFER_LENGTH] = {0};
    switch (type_search) {
        case SEARCH_BY_ID:
            db_select_type(type);
            break;
        case SEARCH_ALL:
            db_select_all_type();          
            break;
        case SEARCH_BY_FILTER:
        default:
    }
    strcat(token_str, "\r\n\r\n");
    //send_message(client_fd, token_str);
}

void search_condition(size_t client_fd, Condition *condition, TypeSearch type_search) {
    char token_str[BUFFER_LENGTH] = {0};
    switch (type_search) {
        case SEARCH_BY_ID:
            db_select_condition(condition);
            break;
        case SEARCH_ALL:
            db_select_all_condition();          
            break;
        case SEARCH_BY_FILTER:
        default:
    }
    strcat(token_str, "\r\n\r\n");
    //send_message(client_fd, token_str);
}

void search_size(size_t client_fd, Size *size, TypeSearch type_search) {
    char token_str[BUFFER_LENGTH] = {0};
    switch (type_search) {
        case SEARCH_BY_ID:
            db_select_size(size);
            break;
        case SEARCH_ALL:
            db_select_all_size();          
            break;
        case SEARCH_BY_FILTER:
        default:
    }
    strcat(token_str, "\r\n\r\n");
    //send_message(client_fd, token_str);
}

void search_item(size_t client_fd, char **tokens) {
    Table table = table_from_string(tokens[1]);
    TypeSearch type_search = type_search_from_string(tokens[2]);
    switch (table) {
        case TABLE_SWEATER:
            Sweater sweater = {0};
            parse_search_sweater(&tokens[2], &sweater);
            search_sweater(client_fd, &sweater, type_search);
            break;
        case TABLE_NOTE:
            Note note = {0};
            parse_search_note(&tokens[2], &note);
            search_note(client_fd, &note, type_search);
            break;
        case TABLE_PIECE:
            Piece piece = {0};
            parse_search_piece(&tokens[2], &piece);
            search_piece(client_fd, &piece, type_search);
            break;
        case TABLE_PIECE_TYPE:
            PieceType piece_type = {0};
            parse_search_piece_type(&tokens[2], &piece_type);
            search_piece_type(client_fd, &piece_type, type_search);
            break;
        case TABLE_BRAND:
            Brand brand = {0};
            parse_search_brand(&tokens[2], &brand);
            search_brand(client_fd, &brand, type_search);
            break;
        case TABLE_COLOR:
            Color color = {0};
            parse_search_color(&tokens[2], &color);
            search_color(client_fd, &color, type_search);
            break;
        case TABLE_NECKLINE:
            Neckline neckline = {0};
            parse_search_neckline(&tokens[2], &neckline);
            search_neckline(client_fd, &neckline, type_search);
            break;
        case TABLE_SLEEVES:
            Sleeves sleeves = {0};
            parse_search_sleeves(&tokens[2], &sleeves);
            search_sleeves(client_fd, &sleeves, type_search);
            break;
        case TABLE_TYPE:
            Type type = {0};
            parse_search_type(&tokens[2], &type);
            search_type(client_fd, &type, type_search);
            break;
        case TABLE_CONDITION:
            Condition condition = {0};
            parse_search_condition(&tokens[2], &condition);
            search_condition(client_fd, &condition, type_search);
            break;
        case TABLE_SIZE:
            Size size = {0};
            parse_search_size(&tokens[2], &size);
            search_size(client_fd, &size, type_search);
            break;
        default:
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }
}
// End Search Item
void info_item(size_t client_fd, char **tokens) {
}

// ----------------------------------------------------------------------------
// Start Add Item
void add_sweater(size_t client_fd, Sweater *sweater) {
    sweater->id = db_insert_sweater(sweater);
    char message[STR_LENGTH] = {0};
    sprintf(message, "SWEATER:ID:%d\r\n\r\n", sweater->id);
    printf("%s\n", message);
    //send_all(client_fd, message, strlen(message));
}

void add_note(size_t client_fd, Note *note) {
    note->id = db_insert_note(note);
    char message[STR_LENGTH] = {0};
    sprintf(message, "Note:ID:%d\r\n\r\n", note->id);
    printf("%s\n", message);
    //send_all(client_fd, message, strlen(message));
}

void add_piece(size_t client_fd, Piece *piece) {
    piece->id = db_insert_piece(piece);
    char message[STR_LENGTH] = {0};
    sprintf(message, "PIECE:ID:%d\r\n\r\n", piece->id);
    printf("%s\n", message);
    //send_all(client_fd, message, strlen(message));
}

void add_piece_type(size_t client_fd, PieceType *piece_type) {
    piece_type->id = db_insert_piece_type(piece_type);
    char message[STR_LENGTH] = {0};
    sprintf(message, "PIECE TYPE:ID:%d\r\n\r\n", piece_type->id);
    printf("%s\n", message);
    //send_all(client_fd, message, strlen(message));
}

void add_brand(size_t client_fd, Brand *brand) {
    brand->id = db_insert_brand(brand);
    char message[STR_LENGTH] = {0};
    sprintf(message, "BRAND:ID:%d\r\n\r\n", brand->id);
    printf("%s\n", message);
    //send_all(client_fd, message, strlen(message));
}

void add_color(size_t client_fd, Color *color) {
    color->id = db_insert_color(color);
    char message[STR_LENGTH] = {0};
    sprintf(message, "COLOR:ID:%d\r\n\r\n", color->id);
    printf("%s\n", message);
    //send_all(client_fd, message, strlen(message));
}

void add_neckline(size_t client_fd, Neckline *neckline) {
    neckline->id = db_insert_neckline(neckline);
    char message[STR_LENGTH] = {0};
    sprintf(message, "NECKLINE:ID:%d\r\n\r\n", neckline->id);
    printf("%s\n", message);
    //send_all(client_fd, message, strlen(message));
}

void add_sleeves(size_t client_fd, Sleeves *sleeves) {
    sleeves->id = db_insert_sleeves(sleeves);
    char message[STR_LENGTH] = {0};
    sprintf(message, "SLEEVES:ID:%d\r\n\r\n", sleeves->id);
    printf("%s\n", message);
    //send_all(client_fd, message, strlen(message));
}

void add_type(size_t client_fd, Type *type) {
    type->id = db_insert_type(type);
    char message[STR_LENGTH] = {0};
    sprintf(message, "TYPE:ID:%d\r\n\r\n", type->id);
    printf("%s\n", message);
    //send_all(client_fd, message, strlen(message));
}

void add_condition(size_t client_fd, Condition *condition) {
    condition->id = db_insert_condition(condition);
    char message[STR_LENGTH] = {0};
    sprintf(message, "CONDITION:ID:%d\r\n\r\n", condition->id);
    printf("%s\n", message);
    //send_all(client_fd, message, strlen(message));
}

void add_size(size_t client_fd, Size *size) {
    size->id = db_insert_size(size);
    char message[STR_LENGTH] = {0};
    sprintf(message, "SIZE:ID:%d\r\n\r\n", size->id);
    printf("%s\n", message);
    //send_all(client_fd, message, strlen(message));
}

#define TABLE_IDX 1

void add_item(size_t client_fd, char **tokens) {
    Table table = table_from_string(tokens[TABLE_IDX]);
    switch (table) {
        case TABLE_SWEATER:
            Sweater sweater = {0};
            parse_add_sweater(&tokens[2], &sweater);
            add_sweater(client_fd, &sweater);
            break;
        case TABLE_NOTE:
            Note note = {0};
            parse_add_note(&tokens[2], &note);
            add_note(client_fd, &note);
            break;
        case TABLE_PIECE:
            Piece piece = {0};
            parse_add_piece(&tokens[2], &piece);
            add_piece(client_fd, &piece);
            break;
        case TABLE_PIECE_TYPE:
            PieceType piece_type = {0};
            parse_add_piece_type(&tokens[2], &piece_type);
            add_piece_type(client_fd, &piece_type);
            break;
        case TABLE_BRAND:
            Brand brand = {0};
            parse_add_brand(&tokens[2], &brand);
            add_brand(client_fd, &brand);
            break;
        case TABLE_COLOR:
            Color color = {0};
            parse_add_color(&tokens[2], &color);
            add_color(client_fd, &color);
            break;
        case TABLE_NECKLINE:
            Neckline neckline = {0};
            parse_add_neckline(&tokens[2], &neckline);
            add_neckline(client_fd, &neckline);
            break;
        case TABLE_SLEEVES:
            Sleeves sleeves = {0};
            parse_add_sleeves(&tokens[2], &sleeves);
            add_sleeves(client_fd, &sleeves);
            break;
        case TABLE_TYPE:
            Type type = {0};
            parse_add_type(&tokens[2], &type);
            add_type(client_fd, &type);
            break;
        case TABLE_CONDITION:
            Condition condition = {0};
            parse_add_condition(&tokens[2], &condition);
            add_condition(client_fd, &condition);
            break;
        case TABLE_SIZE:
            Size size = {0};
            parse_add_size(&tokens[2], &size);
            add_size(client_fd, &size);
            break;
        default:
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }
}
// End Add Item

void edit_item(size_t client_fd, char **tokens) {
}

void remove_item(size_t client_fd, char **tokens) {
}

// ----------------------------------------------------------------------------
// Sart Print Functions
/*
void print_sweater(Sweater *s) {
    printf("%s ", search_brand(s.brand_id));
    printf("%s ", search_color(s->color_id));
    printf("%s ", search_neckline(s->neckline_id));
    printf("%s ", search_type(s->type_id));
    printf("with %s sleeves ", search_sleeves(s->sleeves_id));
    printf("in %s condition ", search_condition(s->condition_id));
    printf("size %s.", search_size(s->size_id));
}
*/
// End Print Functions

int main() {
    int server_fd, client_fd;
    server_fd = network_create_server_socket(PORT);
    
    db_init("../data/database_init.sql");

    bool exit_client = false;
    while (1) {
        client_fd = network_accept_client(server_fd);

        char buffer[BUFFER_LENGTH] = {0};
        Packet packet;
        while (1) {
            network_recv_packet(client_fd, &packet);
            packet_print(&packet);
            char tmp[BUFFER_LENGTH];
            strcpy(tmp, &packet.payload);
            char **tokens = str_split(tmp, " ");
            if (tokens) {
                
                printf("Tokens: \n");
                int i;
                for (i = 0; tokens[i] != NULL ; i++) {
                    printf("%s\n", tokens[i]);
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
    db_close();

    close(server_fd);
    return 0;
}
