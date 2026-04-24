#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <sqlite3.h>

sqlite3 *db = NULL;

int db_init(const char *path) {
    if (sqlite3_open(path, &db) != SQLITE_OK) {
        printf("sqlite3_open: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *sql =
        "PRAGMA foreign_keys = ON;"
        
        "CREATE TABLE IF NOT EXISTS sweater ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  cashmere_code TEXT,"
        "  brand_id INTEGER,"
        "  color_id INTEGER,"
        "  neckline_id INTEGER,"
        "  sleeves_id INTEGER,"
        "  type_id INTEGER,"
        "  weight INTEGER,"
        "  condition_id INTEGER,"
        "  size_id INTEGER,"
        "  FOREIGN KEY(brand_id) REFERENCES brand(id)"
        ");"

        "CREATE TABLE IF NOT EXISTS note ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  sweater_id INTEGER,"
        "  content TEXT,"
        "  FOREIGN KEY(sweater_id) REFERENCES sweater(id)"
        ");"

        "CREATE TABLE IF NOT EXISTS piece ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  sweater_id INTEGER,"
        "  piece_type_id INTEGER,"
        "  original_weight INTEGER,"
        "  current_weight INTEGER,"
        "  continuous INTEGER,"
        "  scraped INTEGER,"
        "  FOREIGN KEY(sweater_id) REFERENCES sweater(id),"
        "  FOREIGN KEY(piece_type_id) REFERENCES piece_type(id)"
        ");"

        "CREATE TABLE IF NOT EXISTS piece_type ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  piece_type TEXT NOT NULL UNIQUE"
        ");"

        "CREATE TABLE IF NOT EXISTS brand ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  brand TEXT NOT NULL UNIQUE"
        ");"

        "CREATE TABLE IF NOT EXISTS color ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  color TEXT NOT NULL UNIQUE"
        ");"

        "CREATE TABLE IF NOT EXISTS neckline ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  neckline TEXT NOT NULL UNIQUE"
        ");"

        "CREATE TABLE IF NOT EXISTS sleeves ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  sleeves TEXT NOT NULL UNIQUE"
        ");"

        "CREATE TABLE IF NOT EXISTS type ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  type TEXT NOT NULL UNIQUE"
        ");"

        "CREATE TABLE IF NOT EXISTS condition ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  condition TEXT NOT NULL UNIQUE"
        ");"

        "CREATE TABLE IF NOT EXISTS size ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  size TEXT NOT NULL UNIQUE"
        ");";

        

    char *err = NULL;
    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        printf("sqlite3_exec: %s\n", err);
        sqlite3_free(err);
        return -1;
    }
    return 0;
}

void db_close() {
    if (db) sqlite3_close(db);
}

#define PORT 5000
#define KEY_LENGTH 32
#define STR_LENGTH 256

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

const char *tables[NUM_TABLES] = {
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
    char cashmere_code[KEY_LENGTH];
    int brand_id;
    int color_id;
    int neckline_id;
    int sleeves_id;
    int type_id;
    int weight;
    int condition_id;
    int size_id;
    // some form of date
} Sweater;

typedef struct {
    int id;
    int sweater_id;
    char content[STR_LENGTH];
    // some form of date;
} Note;

typedef struct {
    int id;
    int sweater_id;
    int piece_type_id;
    int original_weight;
    int current_weight;
    int continuous;
    int scraped;
    // some form of date;
} Piece;

typedef struct {
    int id;
    char piece_type[KEY_LENGTH];
} PieceType;

typedef struct {
    int id;
    char brand[KEY_LENGTH];
} Brand;

typedef struct {
    int id;
    char color[KEY_LENGTH];
} Color;

typedef struct {
    int id;
    char neckline[KEY_LENGTH];
} Neckline;

typedef struct {
    int id;
    char sleeves[KEY_LENGTH];
} Sleeves;

typedef struct {
    int id;
    char type[KEY_LENGTH];
} Type;

typedef struct {
    int id;
    char condition[KEY_LENGTH];
} Condition;

typedef struct {
    int id;
    char size[KEY_LENGTH];
} Size;

// ----------------------------------------------------------------------------
// Start Miscellaneous Functions
void print_sweater(Sweater *s) {
    printf("%d ", s->brand_id);
    printf("%d ", s->color_id);
    printf("%d ", s->neckline_id);
    printf("%d ", s->type_id);
    printf("with %d sleeves ", s->sleeves_id);
    printf("in %d condition ", s->condition_id);
    printf("size %d.", s->size_id);
}

char *trim_whitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

void normalize_key(char *out, char *in) {
    int index = 0;
    in = trim_whitespace(in);
    
    for(int i = 0; i < strlen(in); i++) {
        if (in[i] == '.' || in[i] == ',') {
            continue;
        } else if (in[i] >= 'a' && in[i] <= 'z') {
            out[index++] = in[i] - 32;
        } else {
            out[index++] = in[i];
        }
    }
    out[index] = '\0';
}

void remove_message_delimeter(char *buffer) {
    char *end = strstr(buffer, "\r\n\r\n");
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

void recv_all(const int client_id, char *buffer, int buffer_size) {
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

size_t send_message(const int client_fd, const char *message) {
    return send_all(client_fd, message, strlen(message));
}
// End Miscellaneous Functions

// ----------------------------------------------------------------------------
// Start Tokenizing Tables

void tokenize_sweater(Sweater *sweater) {

}

void tokenize_note(Note *note) {

}

void tokenize_piece(Piece *piece) {

}

void tokenize_piece_type(PieceType *piece_type) {

}

void tokenize_brand(Brand *brand) {

}

void tokenize_color(Color *color) {

}

void tokenize_neckline(Neckline *neckline) {

}

void tokenize_sleeves(Sleeves *sleeve) {

}

void tokenize_type(Type *type) {

}

void tokenize_condition(Condition *condition) {

}

void tokenize_size(Size *size) {

}
// End Tokenizing Tables

// ----------------------------------------------------------------------------
// Start Parsing Tokens
Tables table_from_string(const char *token) {
    for (int i = 0; i < NUM_TABLES; i++) {
        if (strcmp(token, tables[i]) == 0) {
            return (Tables)i;
        }
    }
    return TABLE_NULL; // fallback / error
}

void parse_search_sweater(size_t client_fd, char **tokens) {

}

void parse_search_note(size_t client_fd, char **tokens) {

}

void parse_search_piece(size_t client_fd, char **tokens) {

}

void parse_search_piece_type(size_t client_fd, char **tokens) {

}

void parse_search_brand(size_t client_fd, char **tokens) {

}

void parse_search_color(size_t client_fd, char **tokens) {

}

void parse_search_neckline(size_t client_fd, char **tokens) {

}

void parse_search_sleeves(size_t client_fd, char **tokens) {

}

void parse_search_type(size_t client_fd, char **tokens) {

}

void parse_search_condition(size_t client_fd, char **tokens) {

}

void parse_search_size(size_t client_fd, char **tokens) {

}

void parse_add_sweater(char **tokens, Sweater *sweater) {
    sweater->brand_id = atoi(tokens[1]);
    sweater->color_id = atoi(tokens[3]);
    sweater->neckline_id = atoi(tokens[5]);
    sweater->sleeves_id = atoi(tokens[7]);
    sweater->type_id = atoi(tokens[9]);
    sweater->weight = atoi(tokens[11]);
    sweater->condition_id = atoi(tokens[13]);
    sweater->size_id = atoi(tokens[15]);
    print_sweater(sweater);
}

void parse_add_note(char **tokens, Note *note) {
    note->sweater_id = atoi(tokens[1]);
    strcpy(note->content, tokens[3]);
}

void parse_add_piece(char **tokens, Piece *piece) {
    piece->sweater_id = atoi(tokens[1]);
    piece->piece_type_id = atoi(tokens[3]);
    piece->original_weight = atoi(tokens[5]);
    piece->current_weight = atoi(tokens[7]);
    piece->continuous = atoi(tokens[9]); 
    piece->scraped = atoi(tokens[11]);
}

void parse_add_piece_type(char **tokens, PieceType *piece_type) {
    strcpy(piece_type->piece_type, tokens[1]);
}

void parse_add_brand(char **tokens, Brand *brand) {
    strcpy(brand->brand, tokens[1]);
}

void parse_add_color(char **tokens, Color *color) {
    strcpy(color->color, tokens[1]);
}

void parse_add_neckline(char **tokens, Neckline *neckline) {
    strcpy(neckline->neckline, tokens[1]);
}

void parse_add_sleeves(char **tokens, Sleeves *sleeves) {
    strcpy(sleeves->sleeves, tokens[1]);
}

void parse_add_type(char **tokens, Type *type) {
    strcpy(type->type, tokens[1]);
}

void parse_add_condition(char **tokens, Condition *condition) {
    strcpy(condition->condition, tokens[1]);
}

void parse_add_size(char **tokens, Size *size) {
    strcpy(size->size, tokens[0]);
}

void free_tokens(char **tokens) {
    if (tokens) {
        for (int i = 0; *(tokens + i); i++) {
            free(*(tokens + i));
        }
        free(tokens);
    }
}

char **str_split(char *str, char *delim) {
    char **result = malloc(2 * STR_LENGTH * sizeof(char*));
    int i = 0;

    char *token = strtok(str, delim);
    while (token && i < KEY_LENGTH) {
        result[i++] = strdup(token);
        token = strtok(NULL, delim);
    }

    result[i] = NULL;
    return result;
}
// End Parsing Tokens

//-----------------------------------------------------------------------------
// Start SQLite Functions

int db_select_sweater(Sweater *sweater) {
    const char *sql = 
        " ";

     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_select_note(Note *note) {
    const char *sql = 
        " ";

     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_select_piece(Piece *piece) {
    const char *sql = 
        " ";

     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_select_piece_type(PieceType *piece_type) {
    const char *sql = 
        " ";

     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_select_brand(Brand *brand) {
    const char *sql = 
        " ";

     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_select_color(Color *color) {
    const char *sql = 
        " ";

     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_select_neckline(Neckline *neckline) {
    const char *sql = 
        " ";

     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_select_sleeves(Sleeves *sleeves) {
    const char *sql = 
        " ";

     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_select_type(Type *type) {
    const char *sql = 
        " ";

     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_select_condition(Condition *condition) {
    const char *sql = 
        " ";

     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_select_size(Size *size) {
    const char *sql = 
        " ";

     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_insert_sweater(Sweater *sweater) {
    const char *sql = 
        "   INSERT INTO sweater( "
        "   cashmere_code, "
        "   brand_id, "
        "   color_id, "
        "   neckline_id, "
        "   sleeves_id, "
        "   type_id, "
        "   weight, "
        "   condition_id, "
        "   size_id) "
        "   VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";

     sqlite3_stmt *stmt;
     print_sweater(sweater);
     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     sqlite3_bind_text(stmt, 1, "CASH-000", -1, SQLITE_TRANSIENT);
     sqlite3_bind_int(stmt, 2, sweater->brand_id);
     sqlite3_bind_int(stmt, 3, sweater->color_id);
     sqlite3_bind_int(stmt, 4, sweater->neckline_id);
     sqlite3_bind_int(stmt, 5, sweater->sleeves_id);
     sqlite3_bind_int(stmt, 6, sweater->type_id);
     sqlite3_bind_int(stmt, 7, sweater->weight);
     sqlite3_bind_int(stmt, 8, sweater->condition_id);
     sqlite3_bind_int(stmt, 9, sweater->size_id);
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_insert_note(Note *note) {
     const char *sql = "INSERT INTO note(sweater_id, content) VALUES (?, ?);";
     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     sqlite3_bind_int(stmt, 1, note->sweater_id);
     printf("%s\n", note->content);
     sqlite3_bind_text(stmt, 2, note->content, -1, SQLITE_TRANSIENT);
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);
}

int db_insert_piece(Piece *piece) {
     const char *sql = 
         "  INSERT INTO piece( "
         "  sweater_id, "
         "  piece_type_id, "
         "  original_weight, "
         "  current_weight, "
         "  continuous, "
         "  scraped) "
         "  VALUES (?, ?, ?, ?, ?, ?);";
     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     sqlite3_bind_int(stmt, 1, piece->sweater_id);
     sqlite3_bind_int(stmt, 2, piece->piece_type_id);
     sqlite3_bind_int(stmt, 3, piece->original_weight);
     sqlite3_bind_int(stmt, 4, piece->current_weight);
     sqlite3_bind_int(stmt, 5, piece->continuous);
     sqlite3_bind_int(stmt, 6, piece->scraped);
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);
}

int db_insert_piece_type(PieceType *piece_type) {
     const char *sql = "INSERT INTO piece_type(piece_type) VALUES (?);";
     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     sqlite3_bind_text(stmt, 1, piece_type->piece_type, -1, SQLITE_TRANSIENT);
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);
}

int db_insert_brand(Brand *brand) {
     const char *sql = "INSERT INTO brand(brand) VALUES (?);";
     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     sqlite3_bind_text(stmt, 1, brand->brand, -1, SQLITE_TRANSIENT);
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);
}

int db_insert_color(Color *color) {
     const char *sql = "INSERT INTO color(color) VALUES (?);";
     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     sqlite3_bind_text(stmt, 1, color->color, -1, SQLITE_TRANSIENT);
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);
}

int db_insert_neckline(Neckline *neckline) {
     const char *sql = "INSERT INTO neckline(neckline) VALUES (?);";
     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     sqlite3_bind_text(stmt, 1, neckline->neckline, -1, SQLITE_TRANSIENT);
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);
}

int db_insert_sleeves(Sleeves *sleeves) {
     const char *sql = "INSERT INTO sleeves(sleeves) VALUES (?);";
     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     sqlite3_bind_text(stmt, 1, sleeves->sleeves, -1, SQLITE_TRANSIENT);
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_insert_type(Type *type) {
     const char *sql = "INSERT INTO type(type) VALUES (?);";
     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     sqlite3_bind_text(stmt, 1, type->type, -1, SQLITE_TRANSIENT);
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_insert_condition(Condition *condition) {
     const char *sql = "INSERT INTO condition(condition) VALUES (?);";
     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     sqlite3_bind_text(stmt, 1, condition->condition, -1, SQLITE_TRANSIENT);
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);   
}

int db_insert_size(Size *size) {
     const char *sql = "INSERT INTO size(size) VALUES (?);";
     sqlite3_stmt *stmt;

     sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
     sqlite3_bind_text(stmt, 1, size->size, -1, SQLITE_TRANSIENT);
     sqlite3_step(stmt);
     sqlite3_finalize(stmt);

     return (int)sqlite3_last_insert_rowid(db);
}

// End SQLite Functions

// ----------------------------------------------------------------------------
// Start Search Item

void search_sweater(size_t client_fd, char **tokens) {

}

void search_note(size_t client_fd, char **tokens) {

}

void search_piece(size_t client_fd, char **tokens) {

}

void search_piece_type(size_t client_fd, char **tokens) {

}

void search_brand(size_t client_fd, char **tokens) {

}

void search_color(size_t client_fd, char **tokens) {

}

void search_neckline(size_t client_fd, char **tokens) {

}

void search_sleeves(size_t client_fd, char **tokens) {

}

void search_type(size_t client_fd, char **tokens) {

}

void search_condition(size_t client_fd, char **tokens) {

}

void search_size(size_t client_fd, char **tokens) {

}

void search_item(size_t client_fd, char **tokens) {
}
// End Search Item
void info_item(size_t client_fd, char **tokens) {
}

// ----------------------------------------------------------------------------
// Start Add Item
void add_sweater(size_t client_fd, Sweater *sweater) {
    sweater->id = db_insert_sweater(sweater);
    char message[STR_LENGTH] = {0};
    sprintf(message, "SWEATER:ID:%d\r\n\r\n", sweater->id);
    printf("%s\n", message);
    send_all(client_fd, message, strlen(message));
}

void add_note(size_t client_fd, Note *note) {
    note->id = db_insert_note(note);
    char message[STR_LENGTH] = {0};
    sprintf(message, "Note:ID:%d\r\n\r\n", note->id);
    printf("%s\n", message);
    send_all(client_fd, message, strlen(message));
}

void add_piece(size_t client_fd, Piece *piece) {
    piece->id = db_insert_piece(piece);
    char message[STR_LENGTH] = {0};
    sprintf(message, "PIECE:ID:%d\r\n\r\n", piece->id);
    printf("%s\n", message);
    send_all(client_fd, message, strlen(message));
}

void add_piece_type(size_t client_fd, PieceType *piece_type) {
    piece_type->id = db_insert_piece_type(piece_type);
    char message[STR_LENGTH] = {0};
    sprintf(message, "PIECE TYPE:ID:%d\r\n\r\n", piece_type->id);
    printf("%s\n", message);
    send_all(client_fd, message, strlen(message));
}

void add_brand(size_t client_fd, Brand *brand) {
    brand->id = db_insert_brand(brand);
    char message[STR_LENGTH] = {0};
    sprintf(message, "BRAND:ID:%d\r\n\r\n", brand->id);
    printf("%s\n", message);
    send_all(client_fd, message, strlen(message));
}

void add_color(size_t client_fd, Color *color) {
    color->id = db_insert_color(color);
    char message[STR_LENGTH] = {0};
    sprintf(message, "COLOR:ID:%d\r\n\r\n", color->id);
    printf("%s\n", message);
    send_all(client_fd, message, strlen(message));
}

void add_neckline(size_t client_fd, Neckline *neckline) {
    neckline->id = db_insert_neckline(neckline);
    char message[STR_LENGTH] = {0};
    sprintf(message, "NECKLINE:ID:%d\r\n\r\n", neckline->id);
    printf("%s\n", message);
    send_all(client_fd, message, strlen(message));
}

void add_sleeves(size_t client_fd, Sleeves *sleeves) {
    sleeves->id = db_insert_sleeves(sleeves);
    char message[STR_LENGTH] = {0};
    sprintf(message, "SLEEVES:ID:%d\r\n\r\n", sleeves->id);
    printf("%s\n", message);
    send_all(client_fd, message, strlen(message));
}

void add_type(size_t client_fd, Type *type) {
    type->id = db_insert_type(type);
    char message[STR_LENGTH] = {0};
    sprintf(message, "TYPE:ID:%d\r\n\r\n", type->id);
    printf("%s\n", message);
    send_all(client_fd, message, strlen(message));
}

void add_condition(size_t client_fd, Condition *condition) {
    condition->id = db_insert_condition(condition);
    char message[STR_LENGTH] = {0};
    sprintf(message, "CONDITION:ID:%d\r\n\r\n", condition->id);
    printf("%s\n", message);
    send_all(client_fd, message, strlen(message));
}

void add_size(size_t client_fd, Size *size) {
    size->id = db_insert_size(size);
    char message[STR_LENGTH] = {0};
    sprintf(message, "SIZE:ID:%d\r\n\r\n", size->id);
    printf("%s\n", message);
    send_all(client_fd, message, strlen(message));
}

#define TABLE_IDX 1

void add_item(size_t client_fd, char **tokens) {
    Tables table = table_from_string(tokens[TABLE_IDX]);
    switch (table) {
        case TABLE_SWEATER:
            Sweater sweater = {0};
            parse_add_sweater(&tokens[2], &sweater);
            add_sweater(client_fd, &sweater);
            break;
        case TABLE_NOTE:
            Note note = {0};
            parse_add_note(&tokens[2], &note);
            add_note(client_fd, &note);
            break;
        case TABLE_PIECE:
            Piece piece = {0};
            parse_add_piece(&tokens[2], &piece);
            add_piece(client_fd, &piece);
            break;
        case TABLE_PIECE_TYPE:
            PieceType piece_type = {0};
            parse_add_piece_type(&tokens[2], &piece_type);
            add_piece_type(client_fd, &piece_type);
            break;
        case TABLE_BRAND:
            Brand brand = {0};
            parse_add_brand(&tokens[2], &brand);
            add_brand(client_fd, &brand);
            break;
        case TABLE_COLOR:
            Color color = {0};
            parse_add_color(&tokens[2], &color);
            add_color(client_fd, &color);
            break;
        case TABLE_NECKLINE:
            Neckline neckline = {0};
            parse_add_neckline(&tokens[2], &neckline);
            add_neckline(client_fd, &neckline);
            break;
        case TABLE_SLEEVES:
            Sleeves sleeves = {0};
            parse_add_sleeves(&tokens[2], &sleeves);
            add_sleeves(client_fd, &sleeves);
            break;
        case TABLE_TYPE:
            Type type = {0};
            parse_add_type(&tokens[2], &type);
            add_type(client_fd, &type);
            break;
        case TABLE_CONDITION:
            Condition condition = {0};
            parse_add_condition(&tokens[2], &condition);
            add_condition(client_fd, &condition);
            break;
        case TABLE_SIZE:
            Size size = {0};
            parse_add_size(&tokens[2], &size);
            add_size(client_fd, &size);
            break;
        default:
            printf("OHH NO LUKAS WHAT HAVE YOU DOOOOONE ~ 0xCA75 04/16/2026");
    }
    
    
    send_message(client_fd, "Added item into database.");
}
// End Add Item

void edit_item(size_t client_fd, char **tokens) {
}

void remove_item(size_t client_fd, char **tokens) {
}

void hello_from_server(int client_fd) {
    printf("Connection Accepted.\n");
    send_message(client_fd, "Hello from the Cashmere Database server!\r\n\r\n");
}

// ----------------------------------------------------------------------------
// Sart Print Functions
/*
void print_sweater(Sweater *s) {
    printf("%s ", search_brand(s.brand_id));
    printf("%s ", search_color(s->color_id));
    printf("%s ", search_neckline(s->neckline_id));
    printf("%s ", search_type(s->type_id));
    printf("with %s sleeves ", search_sleeves(s->sleeves_id));
    printf("in %s condition ", search_condition(s->condition_id));
    printf("size %s.", search_size(s->size_id));
}
*/
// End Print Functions

#define BUFFER_LENGTH 8192

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_LENGTH] = {0};
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
    
    db_init("cashmere.db");

    // 4. Accept connections in a loop
    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
       
        hello_from_server(client_fd);
        memset(buffer, 0, sizeof(buffer));
        recv_all(client_fd, buffer, sizeof(buffer));
        printf("%s\n", buffer);
       
        while (1) {
            memset(buffer, 0, sizeof(buffer)); 
            recv_all(client_fd, buffer, sizeof(buffer));
            remove_message_delimeter(buffer);
            // TODO: want to add a way to have multiple connections
            /* TODO: Merge out of main function into a handle_command helper*/
            printf("%s\n", buffer);
            char tmp[BUFFER_LENGTH];
            strcpy(tmp, buffer);
            char **tokens = str_split(buffer, ":");
            // TODO: add logging so i know what commands are being used with what tokens
            // TODO: token count + tokens safety
            // TODO: we should know how many tokens are required for a search or an add just like a C function parameters.
            if (tokens) {
                printf("Tokens: \n");
                int i;
                for (i = 0; tokens[i] != NULL ; i++) {
                    printf("%s\n", tokens[i]);
                }
                if (strcmp(tokens[0], "SEARCH ITEM") == 0) {
                    search_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "INFO ITEM") == 0) {
                    info_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "ADD ITEM") == 0) {
                    add_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "EDIT ITEM") == 0) {
                    edit_item(client_fd, tokens);
                }
                else if (strcmp(tokens[0], "REMOVE ITEM") == 0) {
                    remove_item(client_fd, tokens);
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
    db_close();

    close(server_fd);
    return 0;
}
