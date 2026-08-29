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
#include "db_core.h"
#include "constants.h"
#include "db_tables.h"
#include "misc.h"
#include "seed.h" 
#include "db_filters.h"
#include "db_print.h"

Packet exit_database(Packet *request) {

}

Packet export_database(Packet *request) {

}

Packet import_database(Packet *request) {

}

Packet delete_record(Packet *request) {
    Packet response;
    switch (request->header.table) {
        case TABLE_SWEATER: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_sweater(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_NOTE: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_note(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_PIECE: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_piece(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_PIECE_TYPE: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_piece_type(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_BRAND: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_brand(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_COLOR_FAMILY: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_color_family(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_COLOR: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_color(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_NECKLINE: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_neckline(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_SLEEVES: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_sleeves(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_TYPE: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_type(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_CONDITION: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_condition(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_SIZE: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_size(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        default:
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }

    return response;
}

Packet update_record(Packet *request) {
    Packet response;
    switch (request->header.table) {
        case TABLE_SWEATER: {
            Sweater sweater = payload_decode_sweater(request->payload);            
            db_update_sweater(&sweater);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_sweater(payload, PAYLOAD_MAX_LENGTH, &sweater);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_NOTE: {
            Note note = payload_decode_note(request->payload);            
            db_update_note(&note);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_note(payload, PAYLOAD_MAX_LENGTH, &note);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_PIECE: {
            Piece piece = payload_decode_piece(request->payload);            
            db_update_piece(&piece);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_piece(payload, PAYLOAD_MAX_LENGTH, &piece);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_PIECE_TYPE: {
            PieceType piece_type = payload_decode_piece_type(request->payload);            
            db_update_piece_type(&piece_type);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_piece_type(payload, PAYLOAD_MAX_LENGTH, &piece_type);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_BRAND: {
            Brand brand = payload_decode_brand(request->payload);            
            db_update_brand(&brand);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_brand(payload, PAYLOAD_MAX_LENGTH, &brand);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_COLOR_FAMILY: {
            ColorFamily color_family = payload_decode_color_family(request->payload);            
            db_update_color_family(&color_family);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_color_family(payload, PAYLOAD_MAX_LENGTH, &color_family);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_COLOR: {
            Color color = payload_decode_color(request->payload);            
            db_update_color(&color);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_color(payload, PAYLOAD_MAX_LENGTH, &color);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_NECKLINE: {
            Neckline neckline = payload_decode_neckline(request->payload);            
            db_update_neckline(&neckline);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_neckline(payload, PAYLOAD_MAX_LENGTH, &neckline);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_SLEEVES: {
            Sleeves sleeves = payload_decode_sleeves(request->payload);            
            db_update_sleeves(&sleeves);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_sleeves(payload, PAYLOAD_MAX_LENGTH, &sleeves);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_TYPE: {
            Type type = payload_decode_type(request->payload);            
            db_update_type(&type);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_type(payload, PAYLOAD_MAX_LENGTH, &type);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_CONDITION: {
            Condition condition = payload_decode_condition(request->payload);            
            db_update_condition(&condition);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_condition(payload, PAYLOAD_MAX_LENGTH, &condition);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_SIZE: {
            Size size = payload_decode_size(request->payload);            
            db_update_size(&size);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_size(payload, PAYLOAD_MAX_LENGTH, &size);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        default:
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }

    return response;
}


// Handle creating packet for when inserting fails with, payload = error message, and (TABLE_NULL, PACKET_STATUS_ERROR, payload)
Packet create_record(Packet *request) {
    Packet response;
    switch (request->header.table) {
        case TABLE_SWEATER: {
            Sweater sweater = payload_decode_sweater(request->payload);            
            print_sweater(&sweater);
            sweater.id = db_create_sweater(&sweater);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_sweater(payload, PAYLOAD_MAX_LENGTH, &sweater);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_NOTE: {
            Note note = payload_decode_note(request->payload);            
            print_note(&note);
            note.id = db_create_note(&note);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_note(payload, PAYLOAD_MAX_LENGTH, &note);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_PIECE: {
            Piece piece = payload_decode_piece(request->payload);            
            print_piece(&piece);
            piece.id = db_create_piece(&piece);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_piece(payload, PAYLOAD_MAX_LENGTH, &piece);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_PIECE_TYPE: {
            PieceType piece_type = payload_decode_piece_type(request->payload);            
            print_piece_type(&piece_type);
            piece_type.id = db_create_piece_type(&piece_type);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_piece_type(payload, PAYLOAD_MAX_LENGTH, &piece_type);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_BRAND: {
            Brand brand = payload_decode_brand(request->payload);            
            print_brand(&brand);
            brand.id = db_create_brand(&brand);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_brand(payload, PAYLOAD_MAX_LENGTH, &brand);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_COLOR_FAMILY: {
            ColorFamily color_family = payload_decode_color_family(request->payload);            
            print_color_family(&color_family);
            color_family.id = db_create_color_family(&color_family);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_color_family(payload, PAYLOAD_MAX_LENGTH, &color_family);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_COLOR: {
            Color color = payload_decode_color(request->payload);            
            print_color(&color);
            color.id = db_create_color(&color);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_color(payload, PAYLOAD_MAX_LENGTH, &color);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_NECKLINE: {
            Neckline neckline = payload_decode_neckline(request->payload);            
            print_neckline(&neckline);
            neckline.id = db_create_neckline(&neckline);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_neckline(payload, PAYLOAD_MAX_LENGTH, &neckline);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_SLEEVES: {
            Sleeves sleeves = payload_decode_sleeves(request->payload);            
            print_sleeves(&sleeves);
            sleeves.id = db_create_sleeves(&sleeves);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_sleeves(payload, PAYLOAD_MAX_LENGTH, &sleeves);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_TYPE: {
            Type type = payload_decode_type(request->payload);            
            print_type(&type);
            type.id = db_create_type(&type);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_type(payload, PAYLOAD_MAX_LENGTH, &type);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_CONDITION: {
            Condition condition = payload_decode_condition(request->payload);            
            print_condition(&condition);
            condition.id = db_create_condition(&condition);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_condition(payload, PAYLOAD_MAX_LENGTH, &condition);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_SIZE: {
            Size size = payload_decode_size(request->payload);            
            print_size(&size);
            size.id = db_create_size(&size);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_size(payload, PAYLOAD_MAX_LENGTH, &size);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        default:
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }

    return response;
}

Packet info_record(Packet *request) {
    Packet response;
    switch (request->header.table) {
        case TABLE_SWEATER: {
            int id = payload_decode_id(request->payload);            
            Sweater sweater = db_info_sweater(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_sweater(payload, PAYLOAD_MAX_LENGTH, &sweater);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_NOTE: {
            int id = payload_decode_id(request->payload);            
            Note note = db_info_note(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_note(payload, PAYLOAD_MAX_LENGTH, &note);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_PIECE: {
            int id = payload_decode_id(request->payload);            
            Piece piece = db_info_piece(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_piece(payload, PAYLOAD_MAX_LENGTH, &piece);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_PIECE_TYPE: {
            int id = payload_decode_id(request->payload);            
            PieceType piece_type = db_info_piece_type(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_piece_type(payload, PAYLOAD_MAX_LENGTH, &piece_type);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_BRAND: {
            int id = payload_decode_id(request->payload);            
            Brand brand = db_info_brand(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_brand(payload, PAYLOAD_MAX_LENGTH, &brand);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_COLOR_FAMILY: {
            int id = payload_decode_id(request->payload);            
            ColorFamily color_family = db_info_color_family(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_color_family(payload, PAYLOAD_MAX_LENGTH, &color_family);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_COLOR: {
            int id = payload_decode_id(request->payload);            
            Color color = db_info_color(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_color(payload, PAYLOAD_MAX_LENGTH, &color);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_NECKLINE: {
            int id = payload_decode_id(request->payload);            
            Neckline neckline = db_info_neckline(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_neckline(payload, PAYLOAD_MAX_LENGTH, &neckline);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_SLEEVES: {
            int id = payload_decode_id(request->payload);            
            Sleeves sleeves = db_info_sleeves(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_sleeves(payload, PAYLOAD_MAX_LENGTH, &sleeves);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_TYPE: {
            int id = payload_decode_id(request->payload);            
            Type type = db_info_type(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_type(payload, PAYLOAD_MAX_LENGTH, &type);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_CONDITION: {
            int id = payload_decode_id(request->payload);            
            Condition condition = db_info_condition(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_condition(payload, PAYLOAD_MAX_LENGTH, &condition);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        case TABLE_SIZE: {
            int id = payload_decode_id(request->payload);            
            Size size = db_info_size(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_size(payload, PAYLOAD_MAX_LENGTH, &size);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        }
        default:
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }

    return response;
}

Packet read_records(Packet *request) {
    Packet response;
    switch (request->header.table) {
        case TABLE_SWEATER:
        case TABLE_NOTE:
        case TABLE_PIECE:
        case TABLE_PIECE_TYPE:
        case TABLE_BRAND:
            Pagination pagination = payload_decode_pagination(request->payload);
            Brand brand_rows[MAX_TOKENS];
            int count = db_read_brand(&brand_rows, &pagination);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_brand_rows(payload, PAYLOAD_MAX_LENGTH, &brand_rows);
            response = packet_create_response_init(request->header.table, PACKET_STATUS_OK, payload);
            break;
        case TABLE_COLOR_FAMILY:
        case TABLE_COLOR:
        case TABLE_NECKLINE:
        case TABLE_SLEEVES:
        case TABLE_TYPE:
        case TABLE_CONDITION:
        case TABLE_SIZE:
        default:
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }

    return response;
}

void cashmere_database(int client_fd) {
    while (1) {
        Packet request, response;
        network_recv_packet(client_fd, &request);
        print_packet(&request);
        switch (request.header.request_type) {
            case REQUEST_TYPE_READ:
                response = read_records(&request);
                break;
            case REQUEST_TYPE_INFO:
                response = info_record(&request);
                break;
            case REQUEST_TYPE_CREATE:
                response = create_record(&request);
                break;
            case REQUEST_TYPE_UPDATE:
                response = update_record(&request);
                break;
            case REQUEST_TYPE_DELETE:
                response = delete_record(&request);
                break;
            case REQUEST_TYPE_IMPORT:
                //response = import_record(&request);
                break;
            case REQUEST_TYPE_EXPORT:
                //response = export_record(&request);
                break;
            case REQUEST_TYPE_EXIT:
                //response = exit_record(&request);
                break;
            default:
        }
        print_packet(&response);
        network_send_packet(client_fd, &response);
    }
}

int main() {
    int server_fd, client_fd;
    server_fd = network_create_server_socket(PORT);

    remove_file("./cashmere.db"); 
    db_init("../data/database_init.sql");
    seed_load_all();

    while (1) {
        client_fd = network_accept_client(server_fd);
        cashmere_database(client_fd);
    }
    
    db_close();
    close(server_fd);
    return 0;
}
