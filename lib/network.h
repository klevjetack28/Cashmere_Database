# ifndef NETWORK_H
# define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "constants.h"

int network_create_server_socket(int port);
int network_accept_client(int server_fd);
int network_client_connect(const char *server_ip, int port);

# endif // NETWORK_H
