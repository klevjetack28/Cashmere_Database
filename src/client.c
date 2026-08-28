#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>   
#include <ctype.h>
#include <stdbool.h>

#include "0xca75.h"
#include "db_core.h"
#include "network.h"
#include "packet.h"
#include "payload.h"
#include "constants.h"
#include "db_tables.h"
#include "misc.h"
#include "query.h"
#include "db_print.h"

void get_input(char *input) {
    char buffer[KEY_LENGTH] = {0};
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    normalize_key(input, buffer);
}

int get_int_input(char *prompt) {
    printf("%s", prompt);
    char input[KEY_LENGTH] = {0};
    get_input(input);
    return atoi(input);
}

int get_string_input(char *prompt, char* input) {
    printf("%s", prompt);
    get_input(input);
    int length = strlen(input);
    input[length] = '\0';
    return strlen(input);
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

int delete_sweater_input() {
    return get_int_input("Enter Sweater ID to delete: ");
}

int delete_note_input() {
    return get_int_input("Enter Note ID to delete: ");
}

int delete_piece_input() {
    return get_int_input("Enter Piece ID to delete: ");
}

int delete_piece_type_input() {
    return get_int_input("Enter Piece Type ID to delete: ");
}

int delete_brand_input() {
    return get_int_input("Enter Brand ID to delete: ");
}

int delete_color_family_input() {
    return get_int_input("Enter Color Family ID to delete: ");
}

int delete_color_input() {
    return get_int_input("Enter Color ID to delete: ");
}

int delete_neckline_input() {
    return get_int_input("Enter Neckline ID to delete: ");
}

int delete_sleeves_input() {
    return get_int_input("Enter Sleeves ID to delete: ");
}

int delete_type_input() {
    return get_int_input("Enter Type ID to delete: ");
}

int delete_condition_input() {
    return get_int_input("Enter Condition ID to delete: ");
}

int delete_size_input() {
    return get_int_input("Enter Size ID to delete: ");
}

Packet delete_record(Table table) {
    Packet request;

    while (1) {
        switch(table) {
            case TABLE_SWEATER: {
                int id = delete_sweater_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            case TABLE_NOTE: {
                int id = delete_note_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            case TABLE_PIECE: {
                int id = delete_piece_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            case TABLE_PIECE_TYPE: {
                int id = delete_piece_type_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            case TABLE_BRAND: {
                int id = delete_brand_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            case TABLE_COLOR_FAMILY: {
                int id = delete_color_family_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            case TABLE_COLOR: {
                int id = delete_color_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            case TABLE_NECKLINE: {
                int id = delete_neckline_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            case TABLE_SLEEVES: {
                int id = delete_sleeves_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            case TABLE_TYPE: {
                int id = delete_type_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            case TABLE_CONDITION: {
                int id = delete_condition_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            case TABLE_SIZE: {
                int id = delete_size_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_delete_request_init(table, payload);
                return request;
            }
            default:
                printf("Something went wrong...\n");
                continue;
        }
    }
}

Sweater update_sweater_input() {
    Sweater sweater;
    
    sweater.brand_id = get_int_input("BrandID: ");
    sweater.color_id = get_int_input("ColorID: ");
    sweater.neckline_id = get_int_input("NecklineID: ");
    sweater.sleeves_id = get_int_input("SleevesID: ");
    sweater.type_id = get_int_input("TypeID: ");
    sweater.weight = get_int_input("Weight(g): ");
    sweater.condition_id = get_int_input("ConditionID: ");
    sweater.size_id = get_int_input("SizeID: ");
    
    return sweater;
}

Note update_note_input() {
    Note note;

    note.sweater_id = get_int_input("SweaterID: ");
    get_string_input("Enter Contents: ", note.content);

    return note;
}

Piece update_piece_input() {
    Piece piece;

    piece.sweater_id = get_int_input("Sweater ID: ");
    piece.piece_type_id = get_int_input("Piece Type ID: ");
    piece.original_weight = get_int_input("Original Weight: ");
    piece.current_weight = piece.original_weight;
    piece.continuous = get_int_input("Continuos True(1)/False(0): ");

    return piece;
}

PieceType update_piece_type_input() {
    PieceType piece_type;
    get_string_input("PieceType: ", piece_type.piece_type);
    return piece_type;
}

Brand update_brand_input() {
    Brand brand = {0};
    brand.id = get_int_input("Brand ID to Update: ");
    get_string_input("Brand: ", brand.brand);
    return brand;   
}

ColorFamily update_color_family_input() {
    ColorFamily color_family;
    get_string_input("Color Family: ", color_family.color_family);   
    return color_family;   
}

Color update_color_input() {
    Color color;
    
    color.color_family_id = get_int_input("Color Family ID: ");
    get_string_input("Color: ", color.color);
    
    return color;   
}

Neckline update_neckline_input() {
    Neckline neckline;
    get_string_input("Neckline: ", neckline.neckline);
    return neckline;   
}

Sleeves update_sleeves_input() {
    Sleeves sleeves;
    get_string_input("Sleeves: ", sleeves.sleeves);
    return sleeves;
}

Type update_type_input() {
    Type type;
    get_string_input("Type: ", type.type);
    return type;
}

Condition update_condition_input() {
    Condition condition;
    get_string_input("Condition: ", condition.condition);
    return condition;
}

Size update_size_input() {
    Size size;
    get_string_input("Size: ", size.size);
    return size;
}

Packet update_record(Table table) {
    Packet request;

    while (1) {
        switch(table) {
            case TABLE_SWEATER: {
                Sweater sweater = update_sweater_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_sweater(payload, PAYLOAD_MAX_LENGTH, &sweater);
                request = packet_update_request_init(table, payload);
                return request;
            }
            case TABLE_NOTE: {
                Note note = update_note_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_note(payload, PAYLOAD_MAX_LENGTH, &note);
                request = packet_update_request_init(table, payload);
                return request;
            }
            case TABLE_PIECE: {
                Piece piece = update_piece_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_piece(payload, PAYLOAD_MAX_LENGTH, &piece);
                request = packet_update_request_init(table, payload);
                return request;
            }
            case TABLE_PIECE_TYPE: {
                PieceType piece_type = update_piece_type_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_piece_type(payload, PAYLOAD_MAX_LENGTH, &piece_type);
                request = packet_update_request_init(table, payload);
                return request;
            }
            case TABLE_BRAND: {
                Brand brand = update_brand_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_brand(payload, PAYLOAD_MAX_LENGTH, &brand);
                request = packet_update_request_init(table, payload);
                return request;
            }
            case TABLE_COLOR_FAMILY: {
                ColorFamily color_family = update_color_family_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_color_family(payload, PAYLOAD_MAX_LENGTH, &color_family);
                request = packet_update_request_init(table, payload);
                return request;
            }
            case TABLE_COLOR: {
                Color color = update_color_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_color(payload, PAYLOAD_MAX_LENGTH, &color);
                request = packet_update_request_init(table, payload);
                return request;
            }
            case TABLE_NECKLINE: {
                Neckline neckline = update_neckline_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_neckline(payload, PAYLOAD_MAX_LENGTH, &neckline);
                request = packet_update_request_init(table, payload);
                return request;
            }
            case TABLE_SLEEVES: {
                Sleeves sleeves = update_sleeves_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_sleeves(payload, PAYLOAD_MAX_LENGTH, &sleeves);
                request = packet_update_request_init(table, payload);
                return request;
            }
            case TABLE_TYPE: {
                Type type = update_type_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_type(payload, PAYLOAD_MAX_LENGTH, &type);
                request = packet_update_request_init(table, payload);
                return request;
            }
            case TABLE_CONDITION: {
                Condition condition = update_condition_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_condition(payload, PAYLOAD_MAX_LENGTH, &condition);
                request = packet_update_request_init(table, payload);
                return request;
            }
            case TABLE_SIZE: {
                Size size = update_size_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_size(payload, PAYLOAD_MAX_LENGTH, &size);
                request = packet_update_request_init(table, payload);
                return request;
            }
            default:
                printf("Something went wrong...\n");
                continue;
        }
    }
}





Sweater create_sweater_input() {
    Sweater sweater;
    
    sweater.brand_id = get_int_input("BrandID: ");
    sweater.color_id = get_int_input("ColorID: ");
    sweater.neckline_id = get_int_input("NecklineID: ");
    sweater.sleeves_id = get_int_input("SleevesID: ");
    sweater.type_id = get_int_input("TypeID: ");
    sweater.weight = get_int_input("Weight(g): ");
    sweater.condition_id = get_int_input("ConditionID: ");
    sweater.size_id = get_int_input("SizeID: ");
    
    return sweater;
}

Note create_note_input() {
    Note note;

    note.sweater_id = get_int_input("SweaterID: ");
    get_string_input("Enter Contents: ", note.content);

    return note;
}

Piece create_piece_input() {
    Piece piece;

    piece.sweater_id = get_int_input("Sweater ID: ");
    piece.piece_type_id = get_int_input("Piece Type ID: ");
    piece.original_weight = get_int_input("Original Weight: ");
    piece.current_weight = piece.original_weight;
    piece.continuous = get_int_input("Continuos True(1)/False(0): ");

    return piece;
}

PieceType create_piece_type_input() {
    PieceType piece_type;
    get_string_input("PieceType: ", piece_type.piece_type);
    return piece_type;
}

Brand create_brand_input() {
    Brand brand = {0};
    get_string_input("Brand: ", brand.brand);
    printf("Immediately after input: '%s'\n", brand.brand);
    return brand;   
}

ColorFamily create_color_family_input() {
    ColorFamily color_family;
    get_string_input("Color Family: ", color_family.color_family);   
    return color_family;   
}

Color create_color_input() {
    Color color;
    
    color.color_family_id = get_int_input("Color Family ID: ");
    get_string_input("Color: ", color.color);
    
    return color;   
}

Neckline create_neckline_input() {
    Neckline neckline;
    get_string_input("Neckline: ", neckline.neckline);
    return neckline;   
}

Sleeves create_sleeves_input() {
    Sleeves sleeves;
    get_string_input("Sleeves: ", sleeves.sleeves);
    return sleeves;
}

Type create_type_input() {
    Type type;
    get_string_input("Type: ", type.type);
    return type;
}

Condition create_condition_input() {
    Condition condition;
    get_string_input("Condition: ", condition.condition);
    return condition;
}

Size create_size_input() {
    Size size;
    get_string_input("Size: ", size.size);
    return size;
}

Packet create_record(Table table) {
    Packet request;

    while (1) {
        switch(table) {
            case TABLE_SWEATER: {
                Sweater sweater = create_sweater_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_sweater(payload, PAYLOAD_MAX_LENGTH, &sweater);
                request = packet_create_request_init(table, payload);
                return request;
            }
            case TABLE_NOTE: {
                Note note = create_note_input();
                char *payload[PAYLOAD_MAX_LENGTH];
                payload_encode_note(payload, PAYLOAD_MAX_LENGTH, &note);
                request = packet_create_request_init(table, payload);
                return request;
            }
            case TABLE_PIECE: {
                Piece piece = create_piece_input();
                char *payload[PAYLOAD_MAX_LENGTH];
                payload_encode_piece(payload, PAYLOAD_MAX_LENGTH, &piece);
                request = packet_create_request_init(table, payload);
                return request;
            }
            case TABLE_PIECE_TYPE: { 
                PieceType piece_type = create_piece_type_input();
                char *payload[PAYLOAD_MAX_LENGTH];
                payload_encode_piece_type(payload, PAYLOAD_MAX_LENGTH, &piece_type);
                request = packet_create_request_init(table, payload);
                return request;
            }
            case TABLE_BRAND: {
                Brand brand = create_brand_input();
                char *payload[PAYLOAD_MAX_LENGTH];
                payload_encode_brand(payload, PAYLOAD_MAX_LENGTH, &brand);
                request = packet_create_request_init(table, payload);
                return request;
            }
            case TABLE_COLOR_FAMILY: {
                ColorFamily color_family = create_color_family_input();
                char *payload[PAYLOAD_MAX_LENGTH];
                payload_encode_color_family(payload, PAYLOAD_MAX_LENGTH, &color_family);
                request = packet_create_request_init(table, payload);
                return request;
            }
            case TABLE_COLOR: {
                Color color = create_color_input();
                char *payload[PAYLOAD_MAX_LENGTH];
                payload_encode_color(payload, PAYLOAD_MAX_LENGTH, &color);
                request = packet_create_request_init(table, payload);
                return request;
            }
            case TABLE_NECKLINE: {
                Neckline neckline = create_neckline_input();
                char *payload[PAYLOAD_MAX_LENGTH];
                payload_encode_neckline(payload, PAYLOAD_MAX_LENGTH, &neckline);
                request = packet_create_request_init(table, payload);
                return request;
            }
            case TABLE_SLEEVES: {
                Sleeves sleeves = create_sleeves_input();
                char *payload[PAYLOAD_MAX_LENGTH];
                payload_encode_sleeves(payload, PAYLOAD_MAX_LENGTH, &sleeves);
                request = packet_create_request_init(table, payload);
                return request;
            }
            case TABLE_TYPE: {
                Type type = create_type_input();
                char *payload[PAYLOAD_MAX_LENGTH];
                payload_encode_type(payload, PAYLOAD_MAX_LENGTH, &type);
                request = packet_create_request_init(table, payload);
                return request;
            }
            case TABLE_CONDITION: {
                Condition condition = create_condition_input();
                char *payload[PAYLOAD_MAX_LENGTH];
                payload_encode_condition(payload, PAYLOAD_MAX_LENGTH, &condition);
                request = packet_create_request_init(table, payload);
                return request;
            }
            case TABLE_SIZE: {
                Size size = create_size_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_size(payload, PAYLOAD_MAX_LENGTH, &size);
                request = packet_create_request_init(table, payload);
                return request;
            }
            default:
                // Create error packet
                printf("Something went wrong...\n");
                continue;
        }
    }
}

int info_sweater_input() {
    return get_int_input("Info Sweater ID: ");
}

int info_note_input() {
    return get_int_input("Info Note ID: ");
}

int info_piece_input() {
    return get_int_input("Info Piece ID: ");
}

int info_piece_type_input() {
    return get_int_input("Info Piece Type ID: ");
}

int info_brand_input() {
    return get_int_input("Info Brand ID: ");
}

int info_color_family_input() {
    return get_int_input("Info Color Family ID: ");
}

int info_color_input() {
    return get_int_input("Info Color ID: ");
}

int info_neckline_input() {
    return get_int_input("Info Neckline ID: ");
}

int info_sleeves_input() {
    return get_int_input("Info Sleeves ID: ");
}

int info_type_input() {
    return get_int_input("Info Type ID: ");
}

int info_condition_input() {
    return get_int_input("Info Condition ID: ");
}

int info_size_input() {
    return get_int_input("Info Size ID: ");
}

Packet info_record(Table table) {
    Packet request;

    while (1) {
        switch(table) {
            case TABLE_SWEATER: {
                int id = info_sweater_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            case TABLE_NOTE: {
                int id = info_note_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            case TABLE_PIECE: {
                int id = info_piece_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            case TABLE_PIECE_TYPE: {
                int id = info_piece_type_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            case TABLE_BRAND: {
                int id = info_brand_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            case TABLE_COLOR_FAMILY: {
                int id = info_color_family_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            case TABLE_COLOR: {
                int id = info_color_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            case TABLE_NECKLINE: {
                int id = info_neckline_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            case TABLE_SLEEVES: {
                int id = info_sleeves_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            case TABLE_TYPE: {
                int id = info_type_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            case TABLE_CONDITION: {
                int id = info_condition_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            case TABLE_SIZE: {
                int id = info_size_input();
                char payload[PAYLOAD_MAX_LENGTH];
                payload_encode_id(payload, PAYLOAD_MAX_LENGTH, id);
                request = packet_info_request_init(table, payload);
                return request;
            }
            default:
                printf("Something went wrong...\n");
                continue;
        }
    }
}

SweaterSearch read_sweater_input() {
    
}

NoteSearch read_note_input() {

}

PieceSearch read_piece_input() {

}

Pagination read_piece_type_input() {

}

Pagination read_brand_input() {

}

Pagination read_color_family_input() {

}

Pagination read_color_input() {

}

Pagination read_neckline_input() {

}

Pagination read_sleeves_input() {

}

Pagination read_condition_input() {

}

Pagination read_size_input() {

}

Packet read_records(Table table) {
    Packet request;

    while (1) {
        switch(table) {
            case TABLE_SWEATER:
            case TABLE_NOTE:
            case TABLE_PIECE:
            case TABLE_PIECE_TYPE:
            case TABLE_BRAND:
            case TABLE_COLOR_FAMILY:
            case TABLE_COLOR:
            case TABLE_NECKLINE:
            case TABLE_SLEEVES:
            case TABLE_TYPE:
            case TABLE_CONDITION:
            case TABLE_SIZE:
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
        RequestType request_type = (RequestType)get_int_input("");

        print_table_options();
        Table table = (Table)get_int_input("");

        switch (request_type) {
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
    
        print_packet(&request);
        network_send_packet(server_fd, &request);
        network_recv_packet(server_fd, &response);
        print_packet(&response);
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
