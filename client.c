#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>       
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdbool.h>

#define PORT 5000

typedef enum {
    TABLE_NULL,
    TABLE_SWEATER,
    TABLE_NOTE,
    TABLE_PIECE,
    TABLE_PIECE_TYPE,
    TABLE_BRAND,
    TABLE_COLOR,
    TABLE_NECKLINE,
    TABLE_SLEEVES,
    TABLE_TYPE,
    TABLE_CONDITION,
    TABLE_SIZE,
    NUM_TABLES
} Tables;



const char* tables[NUM_TABLES] = {
    "NULL",
    "SWEATER",
    "NOTE",
    "PIECE",
    "PIECE_TYPE",
    "BRAND",
    "COLOR",
    "NECKLINE",
    "SLEEVES",
    "TYPE",
    "CONDITION",
    "SIZE",
};

typedef struct {
    int id;
    char* cashmere_code;
    char* label;
    int brand_id;
    int color_id;
    int neckline_id;
    int sleeves_id;
    int type_id;
    int weight;
    int condition_id;
    int size_id;
    bool in_inventory;
    // some form of date
} Sweater;

typedef struct {
    int id;
    int sweater_id;
    char* content;
    // some form of date;
} Note;

typedef struct {
    int id;
    int sweater_id;
    int piece_type_id;
    int original_weight;
    int current_weight;
    bool continuous;
    bool scraped;
    // some form of date;
} Piece;

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

void system_status() {

}

void logs() {

}

void print_table_options() {
    for (int i = 1; i < (int)NUM_TABLES; i++) {
        printf("%d> %s\n", i, tables[i]);
    }
}

void add_token(char* tokens) {
    char input[64];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    sprintf("%s:%s", tokens, input);
}

void exit_db(size_t server_fd) {
    send_all(server_fd, "EXIT\r\n\r\n", strlen("EXIT\r\n\r\n"));
    printf("EXIT\n");
}

void remove_item(size_t server_fd) {
    send_all(server_fd, "REMOVE_ITEM\r\n\r\n", strlen("REMOVE_ITEM\r\n\r\n"));
    printf("REMOVE_ITEM\n");

}

void edit_item(size_t server_fd) {
    send_all(server_fd, "EDIT_ITEM\r\n\r\n", strlen("EDIT_ITEM\r\n\r\n"));
    printf("EDIT_ITEM\n");
}

void add_item(size_t server_fd) {
    send_all(server_fd, "ADD_ITEM\r\n\r\n", strlen("ADD_ITEM\r\n\r\n"));
    printf("ADD_ITEM\n");

    bool adding = true;
    char buffer[8];
    while (adding) {
        print_table_options();
        fgets(buffer, sizeof(buffer), stdin);
        
        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] == '\0') {
            continue;
        }

        Tables table = atoi(buffer); // TODO: Use proper validation to make sure client does not enter characters
        switch(table) {
            case TABLE_SWEATER:
                    printf("The %s table.\n", tables[table]);
                break;
            default:
                printf("Something went wrong...\n");
                continue;
        }
        //adding = false;
    }
}

void info(size_t server_fd) {
    send_all(server_fd, "INFO\r\n\r\n", strlen("INFO\r\n\r\n"));
    printf("INFO\n");
}

void search(size_t server_fd) {
    send_all(server_fd, "SEARCH\r\n\r\n", strlen("SEARCH\r\n\r\n"));
    printf("SEARCH\n");

}

void database_menu() {
    printf("1> Search\n2> Info\n3> Add Item\n4> Edit\n5> Remove\n6> Exit\n");
}

void cashmere_database(size_t server_fd) {
    database_menu();

    char c = getchar();
    getchar();
    switch (c) {
        case '1':
            search(server_fd);
            break;
        case '2':
            info(server_fd);
            break;
        case '3':
            add_item(server_fd);
            break;
        case '4':
            edit_item(server_fd);
            break;
        case '5':
            remove_item(server_fd);
            break;
        case '6':
            exit_db(server_fd);
            break;
        default:
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
        printf("1> Cashmere Database\n2> Logs\n3> System Status\n4> Exit\n5> BONUS!!! Add two numbers.\n");
                    
        switch(getchar()) {
            case '1':
                getchar();
                printf("Loading Cashmere Database...\n");
                cashmere_database(sock);
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
