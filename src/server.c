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
#include "query.h"

#define UPPERCASE_OFFSET -32

void normalize_key(char *out, char *in) {
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

Packet exit_database(Packet *request) {

}

Packet export_database(Packet *request) {

}

Packet import_database(Packet *request) {

}

Packet delete_record(Packet *request) {
    Packet response
    switch (request->header.table) {
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
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }

    return response;
}

Packet update_record(Packet *request) {
    Packet response
    switch (request->header.table) {
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

Packet info_record(Packet *request) {
    Packet response
    switch (request->header.table) {
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
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }

    return response;
}

Packet read_records(Packet *request) {
    Packet response
    switch (request->header.table) {
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
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }

    return response;
}

void cashmere_database(int client_fd) {
    while (1) {
        Packet request, response;
        network_recv_packet(client_fd, &request);
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
                response = import_record(&request);
                break;
            case REQUEST_TYPE_EXPORT:
                response = export_record(&request);
                break;
            case REQUEST_TYPE_EXIT:
                response = exit_record(&request);
                break;
            default:
        }

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
