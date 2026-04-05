#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <assert.h>

#define PORT 5000
ssize_t send_all(int socket, const char *data, size_t length) {
    size_t total_sent = 0;
    while (total_sent < length) {
        // Send from the current offset in the data buffer
        ssize_t sent = send(socket, data + total_sent, length - total_sent, 0);
        
        if (sent == -1) {
            return -1;
        }
        total_sent += sent;
    }
    return total_sent;
}

void recv_all(const int client_id, char* buffer, int buffer_size) {
    int total_recieved = 0;
    int bytes_read;

    while (bytes_read = recv(client_id, &buffer[total_recieved], buffer_size - total_recieved - 1, 0)) {
        total_recieved += bytes_read;
        buffer[total_recieved] = '\0';

        if (strstr(buffer, "\r\n\r\n")) {
            break; 
        }
        if (total_recieved >= buffer_size - 1) {
            break;
        }
    }
    if (bytes_read == 0) {
    // Connection was closed by the client
    } else if (bytes_read < 0) {
    // Handle error (e.g., perror("recv"))
    }
}

void free_tokens(char** tokens) {
    if (tokens) {
        for (int i = 0; *(tokens + i); i++) {
            free(*(tokens + i));
        }
        free(tokens);
    }
}

char** str_split(char* str, const char delimeter) {
    char** result = 0;
    size_t count = 0;
    char* last_delim = 0;
    char delim[2];
    delim[0] = delimeter;
    delim[1] = 0;
    
    char* tmp = strdup(str);
    if (!tmp) {
        return NULL;
    }
    
    while (*tmp)
    {
        if (delimeter == *tmp)
        {
            count++;
            last_delim = tmp;
        }
        tmp++;
    }

    count += last_delim < (str + strlen(str) - 1);

    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx = 0;
        char* token = strtok(str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(NULL, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int send_message(int client_fd, char *message) {
    send_all(client_fd, message, strlen(message));
}

void hello_from_server(int client_fd) {
    printf("Connection Accepted.\n");
    send_message(client_fd, "Hello from the Cashmere Database server!\r\n\r\n");
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[8192] = {0};
    bool exit_client = false;

    // 1. Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Bind to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // accept connections from any LAN IP
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 3. Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d\n", PORT);

    // 4. Accept connections in a loop
    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
       
        hello_from_server(client_fd);
        recv_all(client_fd, buffer, sizeof(buffer));
        printf("%s\n", buffer);
       
        while (1) {
            recv_all(client_fd, buffer, sizeof(buffer));
            char** tokens;
            tokens = str_split(buffer, ':');

            if (tokens) {
                printf("Token: ");
                for (int i = 0; *(tokens + i); i++) {
                    printf("%s, ", *(tokens + i));
                }
                printf("\n");
                int num1 = atoi(*(tokens + 1));
                int num2 = atoi(*(tokens + 2));
                int result = num1 + num2;
                char message[256];
                sprintf(message, "Adding numbers %d + %d = %d.\r\n\r\n", num1, num2, result);
                printf("%s", message);
                send_all(client_fd, message, strlen(message));
                free_tokens(tokens);
            }
        }
    }

    close(server_fd);
    return 0;
}
