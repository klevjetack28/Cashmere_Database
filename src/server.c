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
#include "query.h"
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
        case TABLE_SWEATER:
            break;
        case TABLE_NOTE:
            break;
        case TABLE_PIECE:
            break;
        case TABLE_PIECE_TYPE:
            break;
        case TABLE_BRAND: {
            int id = payload_decode_id(request->payload);            
            int status = db_delete_brand(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_id(payload, PAYLOAD_MAX_LENGTH, status);
            response = packet_create_response_init(TABLE_BRAND, PACKET_STATUS_OK, payload);
            break;
        }
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
    Packet response;
    switch (request->header.table) {
        case TABLE_SWEATER:
            break;
        case TABLE_NOTE:
            break;
        case TABLE_PIECE:
            break;
        case TABLE_PIECE_TYPE:
            break;
        case TABLE_BRAND: {
            Brand brand = payload_decode_brand(request->payload);            
            db_update_brand(&brand);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_brand(payload, PAYLOAD_MAX_LENGTH, &brand);
            response = packet_create_response_init(TABLE_BRAND, PACKET_STATUS_OK, payload);
            break;
        }
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
        case TABLE_SWEATER:
        case TABLE_NOTE:
        case TABLE_PIECE:
        case TABLE_PIECE_TYPE:
        case TABLE_BRAND: {
            Brand brand = payload_decode_brand(request->payload);            
            print_brand(&brand);
            brand.id = db_create_brand(&brand);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_brand(payload, PAYLOAD_MAX_LENGTH, &brand);
            response = packet_create_response_init(TABLE_BRAND, PACKET_STATUS_OK, payload);
            break;
        }
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

Packet info_record(Packet *request) {
    Packet response;
    switch (request->header.table) {
        case TABLE_SWEATER:
            break;
        case TABLE_NOTE:
            break;
        case TABLE_PIECE:
            break;
        case TABLE_PIECE_TYPE:
            break;
        case TABLE_BRAND: {
            int id = payload_decode_id(request->payload);            
            Brand brand = db_info_brand(id);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_brand(payload, PAYLOAD_MAX_LENGTH, &brand);
            response = packet_create_response_init(TABLE_BRAND, PACKET_STATUS_OK, payload);
            break;
        }
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
    Packet response;
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
            Pagination pagination = payload_decode_pagination(request->payload);
            Brand brand_rows[MAX_TOKENS];
            int count = db_read_brand(&brand_rows, &pagination);
            char payload[PAYLOAD_MAX_LENGTH];
            int payload_length = payload_encode_brand_rows(payload, PAYLOAD_MAX_LENGTH, &brand_rows);
            response = packet_create_response_init(TABLE_BRAND, PACKET_STATUS_OK, payload);
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
