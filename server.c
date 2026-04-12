#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <assert.h>

#define PORT 5000

void remove_message_delimeter(char* buffer) {
    char* end = strstr(buffer, "\r\n\r\n");
    if (end) {
        *end = '\0';  // terminate string at start of delimiter
    }
}

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

    while ((bytes_read = recv(client_id, &buffer[total_recieved], buffer_size - total_recieved - 1, 0)) > 0) {
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

char** str_split(char* str, char delimeter) {
    char** result = 0;
    size_t count = 0;
    char* last_delim = 0;
    char delim[2];
    delim[0] = delimeter;
    delim[1] = 0;
    
    char* tmp = strdup(str);
    char* tmp_start = tmp;
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

size_t send_message(const int client_fd, const char *message) {
    return send_all(client_fd, message, strlen(message));
}

void search(size_t client_fd, char** tokens) {
   send_message(client_fd, "SEARCH\n"); 
}

void info(size_t client_fd, char** tokens) {
    send_message(client_fd, "INFO\n");
}

void add_item(size_t client_fd, char** tokens) {
    send_message(client_fd, "ADD ITEM\n");
}

void edit_item(size_t client_fd, char** tokens) {
    send_message(client_fd, "EDIT ITEM\n");
}

void remove_item(size_t client_fd, char** tokens) {
    send_message(client_fd, "REMOVE ITEM\n");
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
            remove_message_delimeter(buffer);
            // TODO: want to add a way to have multiple connections
            /* TODO: Merge out of main function into a handle_command helper*/
            printf("%s\n", buffer);
            char** tokens = str_split(buffer, ':');
            // TODO: add logging so i know what commands are being used with what tokens
            // TODO: token count + tokens safety
            // TODO: we should know how many tokens are required for a search or an add just like a C function parameters.
            if (tokens) {
                printf("Tokens: \n");
                int i;
                char token_str[256];
                // Tokens are nothing being printed but it knows it is SEARCHING
                for (i = 0; *(tokens + i + 1); i++) {
                    sprintf(token_str, "%s\n", *(tokens + i));
                }
                if (*(tokens + i)) {
                    sprintf(token_str, "%s\n", *(tokens + i));
                }
                printf("%s\n", token_str);
                if (strcmp(tokens[0], "SEARCH") == 0) {
                    search(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "INFO") == 0) {
                    info(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "ADD_ITEM") == 0) {
                    add_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "EDIT_ITEM") == 0) {
                    edit_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "REMOVE_ITEM") == 0) {
                    remove_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "ADD") == 0) {
                    int num1 = atoi(*(tokens + 1));
                    int num2 = atoi(*(tokens + 2));
                    int result = num1 + num2;
                    char message[256];
                    sprintf(message, "Adding numbers %d + %d = %d.\r\n\r\n", num1, num2, result);
                    printf("%s", message);
                    send_all(client_fd, message, strlen(message));
                }
                else if (strcmp(tokens[0], "EXIT") == 0) {
                    free_tokens(tokens);
                    close(client_fd);
                    break;
                }
                else {
                    printf("WHAT HAVE YOU DONE LUKAS!!\n");
                }
                free_tokens(tokens);
                /* End of handle_command helper*/
            }
        }
    }

    close(server_fd);
    return 0;
}
