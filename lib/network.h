# ifndef NETWORK_H
# define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "packet.h"
#include "constants.h"

#define LENGTH_PREFIX_BYTES 4

int network_create_server_socket(int port);
int network_accept_client(int server_fd);
int network_client_connect(const char *server_ip, int port);
int network_send_all(int socket_fd, const unsigned char* byte_array, int array_length);
int network_recv_all(int socket_fd, unsigned char* byte_array, int array_length);
void network_send_packet(int socket_fd, const Packet *packet);
void network_recv_packet(int socket_fd, Packet *packet);

# endif // NETWORK_H
