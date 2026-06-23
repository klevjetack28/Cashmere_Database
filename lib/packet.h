#ifndef PACKET_H

#define PACKET_H

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "constants.h"
#include "db_tables.h"
#include "query.h"

typedef enum {
    PACKET_TYPE_CONNECT = 0,
    PACKET_TYPE_DISCONNECT,
    PACKET_TYPE_REQUEST,
    PACKET_TYPE_RESPONSE,
} PacketType;

typedef enum {
    REQUEST_TYPE_NONE = 0,
    REQUEST_TYPE_READ,
    REQUEST_TYPE_INFO,
    REQUEST_TYPE_CREATE,
    REQUEST_TYPE_UPDATE,
    REQUEST_TYPE_DELETE,
    REQUEST_TYPE_IMPORT,
    REQUEST_TYPE_EXPORT,
    REQUEST_TYPE_EXIT
} RequestType;

typedef enum {
    PACKET_STATUS_OK = 0,
    PACKEY_STATUS_ERROR,
} PacketStatus;

typedef struct {
    PacketType packet_type;
    RequestType request_type;
    Table table;
    PacketStatus status;
    int payload_length;
} PacketHeader;

#define HEADER_LENGTH sizeof(PacketHeader)
#define PAYLOAD_MAX_LENGTH BUFFER_LENGTH - HEADER_LENGTH

typedef struct {
    PacketHeader header;
    char payload[PAYLOAD_MAX_LENGTH];
} Packet;

void packet_print(Packet *packet);

PacketHeader packet_header_init(PacketType packet_type, RequestType request_type, Table table, PacketStatus status, int payload_length);
Packet packet_init(PacketHeader header, char *payload);

Packet packet_connect_init(char *payload);
Packet packet_disconnect_init(char *payload);

Packet packet_request_init(RequestType request_type, Table table, char *payload);
Packet packet_create_request_init(Table table, char *payload);
Packet packet_read_request_init(Table table, char *payload);
Packet packet_info_request_init(Table table, char *payload);
Packet packet_update_request_init(Table table, char *payload);
Packet packet_delete_request_init(Table table, char *payload);
Packet packet_import_request_init(char *payload);
Packet packet_export_request_init(char *payload);

Packet packet_response_init(RequestType request_type, Table table, PacketStatus status, char *payload);
Packet packet_create_response_init(Table table, PacketStatus status, char *payload);
Packet packet_read_response_init(Table table, PacketStatus status, char *payload);
Packet packet_info_response_init(Table table, PacketStatus status, char *payload);
Packet packet_update_response_init(Table table, PacketStatus status, char *payload);
Packet packet_delete_response_init(Table table, PacketStatus status, char *payload);
Packet packet_import_response_init(PacketStatus status, char *payload);
Packet packet_export_response_init(PacketStatus status, char *payload);

int packet_serialize(const Packet *packet, unsigned char byte_array[BUFFER_LENGTH]);
void packet_deserialize(const unsigned char byte_array[BUFFER_LENGTH], int bytes_read, Packet *packet);

#endif // PACKET_H
