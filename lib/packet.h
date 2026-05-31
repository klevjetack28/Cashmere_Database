#ifndef PACKET_H

#define PACKET_H

#include <stdio.h>
#include <string.h>

#include "constants.h"

typedef enum {
    PACKET_TYPE_CONNECT = 0,
    PACKET_TYPE_DISCONNECT,
    PACKET_TYPE_REQUEST,
    PACKET_TYPE_RESPONSE,
} PacketType;

typedef enum {
    REQUEST_TYPE_NONE = 0,
    REQUEST_TYPE_CREATE,
    REQUEST_TYPE_READ,
    REQUEST_TYPE_UPDATE,
    REQUEST_TYPE_DELETE,
    REQUEST_TYPE_IMPORT,
    REQUEST_TYPE_EXPORT
} RequestType;

typedef enum {
    PACKET_STATUS_OK = 0,
    PACKEY_STATUS_ERROR,
} PacketStatus;

typedef struct {
    PacketType packet_type;
    RequestType request_type;
    PacketStatus status;
    int payload_size;
} PacketHeader;

typedef struct {
    PacketHeader header;
    char payload[BUFFER_LENGTH];
} Packet;

PacketHeader packet_header_init(PacketType packet_type, RequestType request_type, PacketStatus status, int payload_size);
Packet packet_init(PacketHeader header, char *payload);
Packet packet_connect_init(char *payload);
Packet packet_disconnect_init(char *payload);
Packet packet_request_init(RequestType request_type, char *payload);
Packet packet_response_init(char *payload);

#endif // PACKET_H
