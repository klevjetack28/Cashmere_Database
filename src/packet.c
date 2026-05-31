#include <stdio.h>

#include "packet.h"

PacketHeader packet_header_init(PacketType packet_type, RequestType request_type, PacketStatus status, int payload_size) {
    PacketHeader header;
    memset(&header, 0, sizeof(PacketHeader));

    header.packet_type = packet_type;
    header.request_type = request_type;
    header.status = status;
    header.payload_size = payload_size;

    return header;
}

Packet packet_init(PacketHeader header, char *payload) {
    Packet packet;

    memset(&packet, 0, sizeof(Packet));

    packet.header = header;
    strncpy(packet.payload, payload, sizeof(payload) - 1);
    
    return packet;
}

Packet packet_connect_init(char *payload) {
    PacketHeader header;
    header = packet_header_init(PACKET_TYPE_CONNECT, REQUEST_TYPE_NONE, PACKET_STATUS_OK, strlen(payload));
    return packet_init(header, payload);
}

Packet packet_disconnect_init(char* payload) {
    PacketHeader header;
    header = packet_header_init(PACKET_TYPE_DISCONNECT, REQUEST_TYPE_NONE, PACKET_STATUS_OK, strlen(payload));
    return packet_init(header, payload);
}

Packet packet_request_init(RequestType request_type, char *payload) {
    PacketHeader header;
    header = packet_header_init(PACKET_TYPE_REQUEST, request_type, PACKET_STATUS_OK, strlen(payload));
    return packet_init(header, payload);
}

Packet packet_create_request_init(char *payload) {
    return packet_request_init(REQUEST_TYPE_CREATE, payload);
}

Packet packet_read_request_init(char *payload) {
    return packet_request_init(REQUEST_TYPE_READ, payload);
}

Packet packet_update_request_init(char *payload) {
    return packet_request_init(REQUEST_TYPE_UPDATE, payload);
}

Packet packet_delete_request_init(char *payload) {
    return packet_request_init(REQUEST_TYPE_DELETE, payload);
}

Packet packet_import_request_init(char *payload) {
    return packet_request_init(REQUEST_TYPE_IMPORT, payload);
}
Packet packet_export_request_init(char *payload) {
    return packet_request_init(REQUEST_TYPE_EXPORT, payload);
}

Packet packet_response_init(char *payload) {
    PacketHeader header;
    header = packet_header_init(PACKET_TYPE_RESPONSE, REQUEST_TYPE_NONE, PACKET_STATUS_OK, strlen(payload));
    return packet_init(header, payload);
}

int packet_serialize(Packet *packet, unsigned char byte_array[BUFFER_LENGTH]) {
    int offset = 0;

    PacketType packet_type = htons(packet->header.packet_type);
    RequestType request_type = htons(packet->header.request_type);
    PacketStatus status = htons(packet->header.packet_type);
    int payload_size = htons(packet->header.payload_size);

    memcpy(byte_array + offset, &packet_type, sizeof(packet_type));
    offset += sizeof(packet_type);

    memcpy(byte_array + offset, &request_type, sizeof(request_type));
    offset += sizeof(request_type);

    memcpy(byte_array + offset, &status, sizeof(status));
    offset += sizeof(status);

    memcpy(byte_array + offset, &payload_size, sizeof(payload_size));
    offset += sizeof(payload_size);

    memcpy(byte_array + offset, packet->payload, packet->header.payload_size);
    offset += packet->header.payload_size;

    return offset;
}

void packet_deserialize(unsigned char byte_array[BUFFER_LENGTH], int bytes_received, Packet *packet) {
    int offset = 0;

    PacketType packet_type;
    RequestType request_type;
    PacketStatus status;
    int payload_size;

    memcpy(&packet_type, byte_array + offset, sizeof(packet_type));
    offset += sizeof(packet_type);

    memcpy(&request_type, byte_array + offset, sizeof(request_type));
    offset += sizeof(request_type);

    memcpy(&status, byte_array + offset, sizeof(status));
    offset += sizeof(status);

    memcpy(&payload_size, byte_array + offset, sizeof(payload_size));
    offset += sizeof(payload_size);

    PacketHeader tmp;
    tmp = packet_header_init(ntohs(packet_type), ntohs(request_type), ntohs(status), ntohs(payload_size));
    memcpy(&packet->header, &tmp, sizeof(tmp));
    memcpy(&packet->payload, byte_array + offset, bytes_received - offset);
}
