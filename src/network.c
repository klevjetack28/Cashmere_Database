#include "network.h"

int network_create_server_socket(int port) {
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // accept connections from any LAN IP
    address.sin_port = htons(port);


    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

int network_accept_client(int server_fd) {
    int client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    if ((client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
    }

    return client_fd;
}

int network_client_connect(const char *server_ip, int port) {
    int client_fd;
    struct sockaddr_in server;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("Socket failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server.sin_addr);

    if (connect(client_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Connect failed");
        return 1;
    }   
    
    return client_fd;
}

 int network_send_all(int socket_fd, const unsigned char *byte_array, int array_length) {
    int total_sent = 0;
    send(socket_fd, &array_length, sizeof(int), 0);
    while (total_sent < array_length) {
        int bytes_sent = send(socket_fd, byte_array + total_sent, array_length - total_sent, 0);
        
        if (bytes_sent == -1) {
            return -1;
        }
        total_sent += bytes_sent;
    }
    return total_sent;
}

int network_recv_all(int socket_fd, unsigned char* byte_array, int array_length) {
    int total_recieved = 0;
    int bytes_read;
    while ((bytes_read = recv(socket_fd, &byte_array[total_recieved], array_length - total_recieved, 0)) > 0) {
        total_recieved += bytes_read;

        if (total_recieved >= array_length - 1) {
            break;
        }
    }
    if (bytes_read == 0) {
        return 0;
    } else if (bytes_read < 0) {
        return -1;
    }
    return total_recieved;
}

void network_send_packet(int socket_fd, const Packet *packet) {
    unsigned char serialized_packet[BUFFER_LENGTH];
    int packet_length = packet_serialize(packet, serialized_packet);
    
    network_send_all(socket_fd, serialized_packet, packet_length);
}

void network_recv_packet(int socket_fd, Packet *packet) {
    unsigned char byte_array[BUFFER_LENGTH];
    int packet_length = 0;
    
    network_recv_all(socket_fd, &packet_length, sizeof(int));
    network_recv_all(socket_fd, byte_array, packet_length);
    packet_deserialize(byte_array, packet_length, packet);
}
