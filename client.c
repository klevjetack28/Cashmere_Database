#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>       // read() and close()
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdbool.h>

#define PORT 5000

void system_status() {

}

void logs() {

}

void cashmere_database() {

}

ssize_t send_all(int socket, const char *data, size_t length) {
    size_t total_sent = 0;
    while (total_sent < length) {
        // Send from the current offset in the data buffer
        ssize_t sent = send(socket, data + total_sent, length - total_sent, 0);
        
        if (sent == -1) {
            return -1; // Handle error (e.g., connection lost)
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

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[8192] = {0};
    bool exit_client = false;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Connect failed");
        return 1;
    }

    recv_all(sock, buffer, sizeof(buffer));
    printf("%s", buffer);
    char* id = "Client Lukas Laptop is joinging the server.\r\n\r\n";
    send_all(sock, id, strlen(id));
    while (!exit_client) {
        printf("1> Cashmere Database\n2> Logs\n3> System Status\n4> Exit\n5> BONUS!!! Add two numbers.");
                    
        switch(getchar()) {
            case '1':
                printf("Going to cashmere database...\n");
            
                //cashmere_database();
                break;
            case '2':
                // logs();
                break;
            case '3':
                // system_status();
                break;
            case '4':
                exit_client = true;
                break;
            case '5':
                getchar();
                printf("Enter two positive, single digit, numbers.\nNumbers: ");
                char num1 = getchar();
                getchar();
                char num2 =getchar();
                char message[256];
                sprintf(message, "ADD:%c:%c\r\n\r\n", num1, num2);
                send_all(sock, message, strlen(message));
                recv_all(sock, buffer, sizeof(buffer));
                printf("%s\n", buffer);
                break;
            default:
        }
    }

    close(sock);
    return 0;
}
