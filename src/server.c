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
#include "seed.h" 

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
// Start Parsing Tokens

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
            //db_select_sweater(sweater);
            break;
        case SEARCH_ALL:
            //db_select_all_sweater();          
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
            //db_select_note(note);
            break;
        case SEARCH_ALL:
            //db_select_all_note();          
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
            //db_select_piece(piece);
            break;
        case SEARCH_ALL:
            //db_select_all_piece();          
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
            //db_select_piece_type(piece_type);
            break;
        case SEARCH_ALL:
            //db_select_all_piece_type();          
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
            //db_select_brand(brand);
            break;
        case SEARCH_ALL:
            //db_select_all_brand();          
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
            //db_select_color(color);
            break;
        case SEARCH_ALL:
            //db_select_all_color();          
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
            //db_select_neckline(neckline);
            break;
        case SEARCH_ALL:
            //db_select_all_neckline();          
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
            //db_select_sleeves(sleeves);
            break;
        case SEARCH_ALL:
            //db_select_all_sleeves();          
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
            //db_select_type(type);
            break;
        case SEARCH_ALL:
            //db_select_all_type();          
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
            //db_select_condition(condition);
            break;
        case SEARCH_ALL:
            //db_select_all_condition();          
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
            //db_select_size(size);
            break;
        case SEARCH_ALL:
            //db_select_all_size();          
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


// Handle creating packet for when inserting fails with, payload = error message, and (TABLE_NULL, PACKET_STATUS_ERROR, payload)
Packet create_item(Packet *request) {
    Packet response;
    switch (request->header.table) {
        case TABLE_SWEATER: {
            Sweater sweater = payload_decode_sweater(request->payload);            
            sweater.id = db_create_sweater(&sweater);
            char *payload = payload_encode_sweater(&sweater);
            response = packet_create_response_init(TABLE_SWEATER, PACKET_STATUS_OK, payload);
            free(payload);
            break;
        }
        case TABLE_NOTE: {
            Note note = payload_decode_note(request->payload);            
            note.id = db_create_note(&note);
            char *payload = payload_encode_note(&note);
            response = packet_create_response_init(TABLE_NOTE, PACKET_STATUS_OK, payload);
            free(payload);
            break;
            }

        case TABLE_PIECE: {
            Piece piece = payload_decode_piece(request->payload);            
            piece.id = db_create_piece(&piece);
            char *payload = payload_encode_piece(&piece);
            response = packet_create_response_init(TABLE_PIECE, PACKET_STATUS_OK, payload);
            free(payload);
            break;
        }

        case TABLE_PIECE_TYPE: {
            PieceType piece_type = payload_decode_piece_type(request->payload);            
            piece_type.id = db_create_piece_type(&piece_type);
            char *payload = payload_encode_piece_type(&piece_type);
            response = packet_create_response_init(TABLE_PIECE_TYPE, PACKET_STATUS_OK, payload);
            free(payload);
            break;
        }

        case TABLE_BRAND: {
            packet_print(request);
            Brand brand = payload_decode_brand(request->payload);            
            printf("%s\n", request->payload);
            brand.id = db_create_brand(&brand);
            char *payload = payload_encode_brand(&brand);
            printf("%s\n", payload);
            response = packet_create_response_init(TABLE_BRAND, PACKET_STATUS_OK, payload);
            packet_print(&response);
            free(payload);
            break;
        }
        
        case TABLE_COLOR_FAMILY: {
            ColorFamily color_family = payload_decode_color_family(request->payload);            
            color_family.id = db_create_color_family(&color_family);
            char *payload = payload_encode_color_family(&color_family);
            response = packet_create_response_init(TABLE_COLOR_FAMILY, PACKET_STATUS_OK, payload);
            free(payload);
            break;
        }

        case TABLE_COLOR: {
            Color color = payload_decode_color(request->payload);            
            color.id = db_create_color(&color);
            char *payload = payload_encode_color(&color);
            response = packet_create_response_init(TABLE_COLOR, PACKET_STATUS_OK, payload);
            free(payload);
            break;
        }

        case TABLE_NECKLINE: {
            Neckline neckline = payload_decode_neckline(request->payload);            
            neckline.id = db_create_neckline(&neckline);
            char *payload = payload_encode_neckline(&neckline);
            response = packet_create_response_init(TABLE_NECKLINE, PACKET_STATUS_OK, payload);
            free(payload);
            break;
        }

        case TABLE_SLEEVES: {
            Sleeves sleeves = payload_decode_sleeves(request->payload);            
            sleeves.id = db_create_sleeves(&sleeves);
            char *payload = payload_encode_sleeves(&sleeves);
            response = packet_create_response_init(TABLE_SLEEVES, PACKET_STATUS_OK, payload);
            free(payload);
            break;
        }

        case TABLE_TYPE: {
            Type type = payload_decode_type(request->payload);            
            type.id = db_create_type(&type);
            char *payload = payload_encode_type(&type);
            response = packet_create_response_init(TABLE_TYPE, PACKET_STATUS_OK, payload);
            free(payload);
            break;
        }

        case TABLE_CONDITION: {
            Condition condition = payload_decode_condition(request->payload);            
            condition.id = db_create_condition(&condition);
            char *payload = payload_encode_condition(&condition);
            response = packet_create_response_init(TABLE_CONDITION, PACKET_STATUS_OK, payload);
            free(payload);
            break;
        }

        case TABLE_SIZE: {
            Size size = payload_decode_size(request->payload);            
            size.id = db_create_size(&size);
            char *payload = payload_encode_size(&size);
            response = packet_create_response_init(TABLE_SIZE, PACKET_STATUS_OK, payload);
            free(payload);
            break;
        }

        default:
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }

    return response;
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

    remove_file("./cashmere.db"); 
    db_init("../data/database_init.sql");
    seed_load_all();

    bool exit_client = false;
    while (1) {
        client_fd = network_accept_client(server_fd);

        char tokens[BUFFER_LENGTH] = {0};
        while (1) {
            Packet request, response;
            network_recv_packet(client_fd, &request);
            if (strcmp(tokens, "SEARCH ITEM") == 0) {
                search_item(client_fd, tokens);
            }
            else if (strcmp(tokens, "INFO ITEM") == 0) {
                info_item(client_fd, tokens);
            }
            else if (request.header.request_type == REQUEST_TYPE_CREATE) {
                response = create_item(&request);
                network_send_packet(client_fd, &response);
            }
            else if (strcmp(tokens, "EDIT ITEM") == 0) {
                edit_item(client_fd, tokens);
            }
            else if (strcmp(tokens, "REMOVE ITEM") == 0) {
                remove_item(client_fd, tokens);
            }
            else if (strcmp(tokens, "EXIT") == 0) {
                close(client_fd);
                break;
            }
            else {
                printf("WHAT HAVE YOU DONE LUKAS!!\n");
            }
            /* End of handle_command helper*/
        }
    }
    db_close();

    close(server_fd);
    return 0;
}
