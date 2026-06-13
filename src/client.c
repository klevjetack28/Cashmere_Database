#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>   
#include <ctype.h>
#include <stdbool.h>

#include "0xca75.h"
#include "database.h"
#include "network.h"
#include "packet.h"
#include "payload.h"
#include "constants.h"
#include "db_tables.h"
#include "misc.h"

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

void get_search_sweater_input(char* input, Sweater* sweater) {
    
}

void get_search_piece_input(char* input, Piece* piece) {

}
void get_search_note_input(char* input, Note* note) {

}



Sweater get_create_sweater_input() {
    Sweater sweater;
    char input[STR_LENGTH] = {0};
    
    printf("BrandID: ");
    sweater.brand_id = get_int_input(input);
    printf("ColorID: ");
    sweater.color_id = get_int_input(input);
    printf("NecklineID: ");
    sweater.neckline_id = get_int_input(input);
    printf("SleevesID: ");
    sweater.sleeves_id = get_int_input(input);
    printf("TypeID: ");
    sweater.type_id = get_int_input(input);
    printf("Weight(g): ");
    sweater.weight = get_int_input(input);
    printf("ConditionID: ");
    sweater.condition_id = get_int_input(input);
    printf("SizeID: ");
    sweater.size_id = get_int_input(input);
    
    return sweater;
}

Note get_create_note_input() {
    Note note;
    char input[STR_LENGTH] = {0};

    printf("SweaterID: ");
    note.sweater_id = get_int_input(input);
    printf("Enter Contents: ");
    get_string_input(note.content);

    return note;
}

Piece get_create_piece_input() {
    Piece piece;
    char input[STR_LENGTH] = {0};

    printf("Sweater ID: ");
    piece.sweater_id = get_int_input(input);
    printf("Piece Type ID: ");
    piece.piece_type_id = get_int_input(input);
    printf("Original Weight: ");
    piece.original_weight = get_int_input(input);
    piece.current_weight = piece.original_weight;
    printf("Continuos True(1)/False(0): ");
    piece.continuous = get_int_input(input);
    piece.scraped = 0; 

    return piece;
}

PieceType get_create_piece_type_input() {
    PieceType piece_type;
    char input[STR_LENGTH] = {0};

    printf("PieceType: ");
    get_string_input(input);
    strcpy(piece_type.piece_type, input);

    return piece_type;
}

Brand get_create_brand_input() {
    Brand brand;
    char input[STR_LENGTH] = {0};

    printf("Brand: ");
    get_string_input(input);
    strcpy(brand.brand, input);

    return brand;   
}

Color get_create_color_input() {
    Color color;
    char input[STR_LENGTH] = {0};

    printf("color: ");
    get_string_input(input);   
    strcpy(color.color, input);

    return color;   
}

Neckline get_create_neckline_input() {
    Neckline neckline;
    char input[STR_LENGTH] = {0};

    printf("Neckline: ");
    get_string_input(input);
    strcpy(neckline.neckline, input);

    return neckline;   
}

Sleeves get_create_sleeves_input() {
    Sleeves sleeves;
    char input[STR_LENGTH] = {0};

    printf("Sleeves: ");
    get_string_input(input);
    strcpy(sleeves.sleeves, input);

    return sleeves;
}

Type get_create_type_input() {
    Type type;
    char input[STR_LENGTH] = {0};

    printf("Type: ");
    get_string_input(input);
    strcpy(type.type, input);

    return type;
}

Condition get_create_condition_input() {
    Condition condition;
    char input[STR_LENGTH] = {0};

    printf("Condition: ");
    get_string_input(input);
    strcpy(condition.condition, input);

    return condition;
}

Size get_create_size_input() {
    Size size;
    char input[STR_LENGTH] = {0};

    printf("Size: ");
    get_string_input(input);
    strcpy(size.size, input);

    return size;
}

// End Get Input Functions


void system_status() {

}

void logs() {

}

void print_table_options() {
    for (int i = 1; i < (int)NUM_TABLES; i++) {
        printf("%d> %s\n", i, TABLE_NAMES[i]);
    }
}

void exit_db(char* token_str) {
}

// ----------------------------------------------------------------------------
// Start Remove Item

void remove_item(char* token_str) {
}
// End Remove Item

// ----------------------------------------------------------------------------
// Start Edit Item

void edit_item(char* token_str) {
}
// End Edit Item

// ----------------------------------------------------------------------------
// Start Add Item

Packet create_item() {
    Packet packet;

    while (1) {
        print_table_options();

        char table_id[KEY_LENGTH];
        Table table = (Table)get_int_input(table_id);
        switch(table) {
            case TABLE_SWEATER: {
                Sweater sweater = get_create_sweater_input();
                char *payload = payload_encode_sweater(&sweater);
                packet = packet_create_request_init(table, payload);
                free(payload);
                return packet;
            }
            case TABLE_NOTE: {
                Note note = get_create_note_input();
                char *payload = payload_encode_note(&note);
                packet = packet_create_request_init(table, payload);
                free(payload);
                return packet;
            }
            case TABLE_PIECE: {
                Piece piece = get_create_piece_input();
                char *payload = payload_encode_piece(&piece);
                packet = packet_create_request_init(table, payload);
                free(payload);
                return packet;
            }
            case TABLE_PIECE_TYPE: { 
                PieceType piece_type = get_create_piece_type_input();
                char *payload = payload_encode_piece_type(&piece_type);
                packet = packet_create_request_init(table, payload);
                free(payload);
                return packet;
            }
            case TABLE_BRAND: {
                Brand brand = get_create_brand_input();
                char *payload = payload_encode_brand(&brand);
                packet = packet_create_request_init(table, payload);
                free(payload);
                packet_print(&packet);
                return packet;
            }
            case TABLE_COLOR: {
                Color color = get_create_color_input();
                char *payload = payload_encode_color(&color);
                packet = packet_create_request_init(table, payload);
                free(payload);
                return packet;
            }
            case TABLE_NECKLINE: {
                Neckline neckline = get_create_neckline_input();
                char *payload = payload_encode_neckline(&neckline);
                packet = packet_create_request_init(table, payload);
                free(payload);
                return packet;
            }
            case TABLE_SLEEVES: {
                Sleeves sleeves = get_create_sleeves_input();
                char *payload = payload_encode_sleeves(&sleeves);
                packet = packet_create_request_init(table, payload);
                free(payload);
                return packet;
            }
            case TABLE_TYPE: {
                Type type = get_create_type_input();
                char *payload = payload_encode_type(&type);
                packet = packet_create_request_init(table, payload);
                free(payload);
                return packet;
            }
            case TABLE_CONDITION: {
                Condition condition = get_create_condition_input();
                char *payload = payload_encode_condition(&condition);
                packet = packet_create_request_init(table, payload);
                free(payload);
                return packet;
            }
            case TABLE_SIZE: {
                Size size = get_create_size_input();
                char *payload = payload_encode_size(&size);
                packet = packet_create_request_init(table, payload);
                free(payload);
                return packet;
            }
            default:
                printf("Something went wrong...\n");
                continue;
        }
    }
    print_packet(packet);
    return packet;
}
// End Add Item


// ----------------------------------------------------------------------------
// Start Info Item

void info_item(char* token_str) {
}
// End Info Item

// ----------------------------------------------------------------------------
// Start Search Item

void search_sweater(char* token_str) {
    // TODO
}

void search_note(char* token_str) {
    // TODO
}

void search_piece(char* token_str) {
    // TODO
}

void search_piece_type(char* token_str, int piece_type_id) {
    char tokens[KEY_LENGTH];
    if (piece_type_id == -1) {
        sprintf(tokens, "ALL:PIECE_TYPE");
    }
    else {
        sprintf(tokens, "ID:PIECE_TYPE:%d", piece_type_id);
    }
}

void search_brand(char* token_str, int brand_id) {
    char tokens[KEY_LENGTH];
    if (brand_id == -1) {
        sprintf(tokens, "ALL:BRAND");
    }
    else {
        sprintf(tokens, "ID:BRAND:%d", brand_id);
    }
}

void search_color(char* token_str, int color_id) {
    char tokens[KEY_LENGTH];
    if (color_id == -1) {
        sprintf(tokens, "ALL:COLOR");
    }
    else {
        sprintf(tokens, "ID:COLOR:%d", color_id);
    }
}

void search_neckline(char* token_str, int neckline_id) {
    char tokens[KEY_LENGTH];
    if (neckline_id == -1) {
        sprintf(tokens, "ALL:NECKLINE");
    }
    else {
        sprintf(tokens, "ID:NECKLINE:%d", neckline_id);
    }
}

void search_sleeves(char* token_str, int sleeves_id) {
    char tokens[KEY_LENGTH];
    if (sleeves_id == -1) {
        sprintf(tokens, "ALL:SLEEVES");
    }
    else {
        sprintf(tokens, "ID:SLEEVES:%d", sleeves_id);
    }
}

void search_type(char* token_str, int type_id) {
    char tokens[KEY_LENGTH];
    if (type_id == -1) {
        sprintf(tokens, "ALL:TYPE");
    }
    else {
        sprintf(tokens, "ID:TYPE:%d", type_id);
    }
}

void search_condition(char* token_str, int condition_id) {
    char tokens[KEY_LENGTH];
    if (condition_id == -1) {
        sprintf(tokens, "ALL:CONDITION");
    }
    else {
        sprintf(tokens, "ID:CONDITION:%d", condition_id);
    }
}

void search_size(char* token_str, int size_id) {
    char tokens[KEY_LENGTH];
    if (size_id == -1) {
        printf(tokens, "ALL:SIZE");
    }
    else {
        sprintf(tokens, "ID:SIZE:%d", size_id);
    }
}

void search_item(char* token_str) {
    bool searching = true;
    while (searching) {
        print_table_options();

        char table_id[KEY_LENGTH] = {0};
        Table table = (Table)get_int_input(table_id);
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

void cashmere_database(int server_fd) {
    char buffer[STR_LENGTH] = {0};
    bool exit = false;
    while(!exit) {
        Packet packet;
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
                packet = create_item();
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
    
        network_send_packet(server_fd, &packet);
        network_recv_packet(server_fd, &packet);
        packet_print(&packet);
        printf("%s\n", packet.payload);
    }
}

int main() {
    int client_fd;

    client_fd = network_client_connect("127.0.0.1", PORT);

    bool exit_client = false;
    while (!exit_client) {
        printf("1> Cashmere Database\n2> Logs\n3> System Status\n4> Exit\n");
                    
        switch(getchar()) {
            case '1':
                getchar();
                printf("Loading Cashmere Database...\n");
                cashmere_database(client_fd);
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
            default:
        }
    }

    close(client_fd);
    return 0;
}
