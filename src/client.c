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
#include "query.h"

void get_input(char *input) {
    char buffer[KEY_LENGTH] = {0};
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    normalize_key(input, buffer);
    return buffer;
}

int get_int_input() {
    char input[KEY_LENGTH] = {0};
    get_input(input);
    return atoi(input);
}

int get_string_input(char* input) {
    get_input(input);
    return strlen(input);
}

void get_search_sweater_input(char* input, Sweater* sweater) {
    
}

void get_search_piece_input(char* input, Piece* piece) {

}
void get_search_note_input(char* input, Note* note) {

}





void system_status() {

}

void logs() {

}

Packet exit_database(void) {

}

Packet export_database(void) {

}





Packet import_database(void) {

}





int delete_sweater_by_id_input() {

}

int delete_note_by_id_input() {

}

int delete_piece_by_id_input() {

}

int delete_piece_type_by_id_input() {

}

int delete_brand_by_id_input() {

}

int delete_color_family_by_id_input() {

}

int delete_color_by_id_input() {

}

int delete_neckline_by_id_input() {

}

int delete_sleeves_by_id_input() {

}

int delete_type_by_id_input() {

}

int delete_condition_by_id_input() {

}

int delete_size_by_id_input() {

}

Packet delete_record(void) {

}





Sweater update_sweater_input() {

}

Note update_note_input() {

}

Piece update_piece_input() {

}

PieceType update_piece_type_input() {

}

Brand update_brand_input() {

}

ColorFamily update_color_family_input() {

}

Color update_color_input() {

}

Neckline update_neckline_input() {

}

Sleeves update_sleeves_input() {

}

Type update_type_input() {

}

Condition update_condition_input() {

}

Size update_size_input() {

}

Packet update_record(void) {

}





Sweater create_sweater_input() {
    Sweater sweater;
    
    printf("BrandID: ");
    sweater.brand_id = get_int_input();
    printf("ColorID: ");
    sweater.color_id = get_int_input();
    printf("NecklineID: ");
    sweater.neckline_id = get_int_input();
    printf("SleevesID: ");
    sweater.sleeves_id = get_int_input();
    printf("TypeID: ");
    sweater.type_id = get_int_input();
    printf("Weight(g): ");
    sweater.weight = get_int_input();
    printf("ConditionID: ");
    sweater.condition_id = get_int_input();
    printf("SizeID: ");
    sweater.size_id = get_int_input();
    
    return sweater;
}

Note create_note_input() {
    Note note;

    printf("SweaterID: ");
    note.sweater_id = get_int_input();
    printf("Enter Contents: ");
    get_string_input(note.content);

    return note;
}

Piece create_piece_input() {
    Piece piece;

    printf("Sweater ID: ");
    piece.sweater_id = get_int_input();
    printf("Piece Type ID: ");
    piece.piece_type_id = get_int_input();
    printf("Original Weight: ");
    piece.original_weight = get_int_input();
    piece.current_weight = piece.original_weight;
    printf("Continuos True(1)/False(0): ");
    piece.continuous = get_int_input();

    return piece;
}

PieceType create_piece_type_input() {
    PieceType piece_type;
    printf("PieceType: ");
    get_string_input(piece_type.piece_type);
    return piece_type;
}

Brand create_brand_input() {
    Brand brand;
    printf("Brand: ");
    get_string_input(brand.brand);
    return brand;   
}

ColorFamily create_color_family_input() {
    ColorFamily color_family;
    printf("Color Family: ");
    get_string_input(color_family.color_family);   
    return color_family;   
}

Color create_color_input() {
    Color color;
    char input[STR_LENGTH] = {0};
    
    printf("Color Family ID: ");
    color.color_family_id = get_int_input();
    printf("Color: ");
    get_string_input(color.color);
    
    return color;   
}

Neckline create_neckline_input() {
    Neckline neckline;
    printf("Neckline: ");
    get_string_input(neckline.neckline);
    return neckline;   
}

Sleeves create_sleeves_input() {
    Sleeves sleeves;
    printf("Sleeves: ");
    get_string_input(sleeves.sleeves);
    return sleeves;
}

Type create_type_input() {
    Type type;
    printf("Type: ");
    get_string_input(type.type);
    return type;
}

Condition create_condition_input() {
    Condition condition;
    printf("Condition: ");
    get_string_input(condition.condition);
    return condition;
}

Size create_size_input() {
    Size size;
    printf("Size: ");
    get_string_input(size.size);
    return size;
}

Packet create_record(Table table) {
    Packet request;

    while (1) {
        switch(table) {
            case TABLE_SWEATER: {
                Sweater sweater = create_sweater_input();
                char *payload = payload_encode_sweater(&sweater);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_NOTE: {
                Note note = create_note_input();
                char *payload = payload_encode_note(&note);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_PIECE: {
                Piece piece = create_piece_input();
                char *payload = payload_encode_piece(&piece);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_PIECE_TYPE: { 
                PieceType piece_type = create_piece_type_input();
                char *payload = payload_encode_piece_type(&piece_type);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_BRAND: {
                Brand brand = create_brand_input();
                char *payload = payload_encode_brand(&brand);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_COLOR_FAMILY: {
                ColorFamily color_family = create_color_family_input();
                char *payload = payload_encode_color_family(&color_family);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_COLOR: {
                Color color = create_color_input();
                char *payload = payload_encode_color(&color);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_NECKLINE: {
                Neckline neckline = create_neckline_input();
                char *payload = payload_encode_neckline(&neckline);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_SLEEVES: {
                Sleeves sleeves = create_sleeves_input();
                char *payload = payload_encode_sleeves(&sleeves);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_TYPE: {
                Type type = create_type_input();
                char *payload = payload_encode_type(&type);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_CONDITION: {
                Condition condition = create_condition_input();
                char *payload = payload_encode_condition(&condition);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_SIZE: {
                Size size = create_size_input();
                char *payload = payload_encode_size(&size);
                request = packet_create_request_init(table, payload);
                free(payload);
                return request;
            }
            default:
                // Create error packet
                printf("Something went wrong...\n");
                continue;
        }
    }
    return request;
}





int read_sweater_by_id() {

}

int read_note_by_id() {

}

int read_piece_by_id() {

}

int read_piece_type_by_id() {

}

int read_brand_by_id() {

}

int read_color_family_by_id() {

}

int read_color_by_id() {

}

int read_neckline_by_id() {

}

int read_sleeves_by_id() {

}

int read_type_by_id() {

}

int read_condition_by_id() {

}

int read_size_by_id() {

}

Packet info_reacord(Table table) {
    Packet request;

    while (1) {
        switch(table) {
            case TABLE_SWEATER: {
                int id = read_sweater_by_id();
                char *payload = payload_encode_id(id);
                request = request_read_packet_init(table, payload);
                free(payload);
                return request;
            }
            case TABLE_NOTE:
                break;
            case TABLE_PIECE:
                break;
            case TABLE_PIECE_TYPE:
                break;
            case TABLE_BRAND:
                break;
            case TABLE_COLOR_FAMILY:
                break;
            case TABLE_COLOR:
                break;
            case TABLE_NECKLINE:
                break;
            case TABLE_SLEEVES:
                break;
            case TABLE_TYPE:
                break;
            case TABLE_CONDITION:
                break;
            case TABLE_SIZE:
                break;
            default:
                printf("Something went wrong...\n");
                continue;
        }
    }
}





int read_sweater() {

}

int read_note() {

}

int read_piece() {

}

int read_piece_type() {

}

int read_brand() {

}

int read_color_family() {

}

int read_color() {

}

int read_neckline() {

}

int read_sleeves() {

}

int read_type() {

}

int read_condition() {

}

int read_size() {

}

Packet read_records(Table table) {
    Packet request;

    while (1) {
        switch(table) {
            case TABLE_SWEATER:
                break;
            case TABLE_NOTE:
                break;
            case TABLE_PIECE:
                break;
            case TABLE_PIECE_TYPE:
                break;
            case TABLE_BRAND:
                break;
            case TABLE_COLOR_FAMILY:
                break;
            case TABLE_COLOR:
                break;
            case TABLE_NECKLINE:
                break;
            case TABLE_SLEEVES:
                break;
            case TABLE_TYPE:
                break;
            case TABLE_CONDITION:
                break;
            case TABLE_SIZE:
                break;
            default:
                printf("Something went wrong...\n");
                continue;
        }
    }
}

void print_table_options() {
    for (int i = 1; i < (int)NUM_TABLES; i++) {
        printf("%d> %s\n", i, TABLE_NAMES[i]);
    }
}

void database_menu() {
    printf("1> Read\n2> Info\n3> Create\n4> Update\n5> Delete\n6> Import\n7> Export\n8> Exit\n");
}

void cashmere_database(int server_fd) {
    char buffer[STR_LENGTH] = {0};
    Packet request, response;
    while(1) {
        database_menu();
        RequestType request_type = (RequestType)get_int_input();

        print_table_options();
        Table table = (Table)get_int_input();

        switch (options) {
            case REQUEST_TYPE_READ:
                request = read_records(table);
                break;
            case REQUEST_TYPE_INFO:
                request = info_record(table);
                break;
            case REQUEST_TYPE_CREATE:
                request = create_record(table);
                break;
            case REQUEST_TYPE_UPDATE:
                request = update_record(table);
                break;
            case REQUEST_TYPE_DELETE:
                request = delete_record(table);
                break;
            case REQUEST_TYPE_IMPORT:
                request = import_database();
                break;
            case REQUEST_TYPE_EXPORT:
                request = export_database();
                break;
            case REQUEST_TYPE_EXIT:
                request = exit_database();
                break;
            default:
        }
    
        packet_print(&request);
        network_send_packet(server_fd, &request);
        network_recv_packet(server_fd, &response);
        packet_print(&response);
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
