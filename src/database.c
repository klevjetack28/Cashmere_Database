#include "database.h"

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

void db_print_sweater(const Sweater *sweater){

}

void db_print_note(const Note *note){

}

void db_print_piece(const Piece *piece){

}

void db_print_piece_type(const PieceType *piece_type){

}

void db_print_brand(const Brand *brand){

}

void db_print_color(const Color *color){

}

void db_print_neckline(const Neckline *neckline){

}

void db_print_sleeves(const Sleeves *sleeves){

}

void db_print_type(const Type *type){

}

void db_print_condition(const Condition *condition){

}

void db_print_size(const Size *size){

}

void db_select_all_sweater(char *token_str) {

}

void db_select_all_note(char *token_str) {

}

void db_select_all_piece(char *token_str) {

}

void db_select_all_piece_type(char *token_str) {
     const char *sql = 
        "SELECT * FROM PieceType";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    
    PieceType piece_type;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        memset(&piece_type, 0, sizeof(piece_type));
        piece_type.id = sqlite3_column_int(stmt, 0);
        strcpy(piece_type.piece_type, sqlite3_column_text(stmt, 1));
        // I can always add token 1 start and end as a delimeter for item retrival
        tokenize_piece_type(token_str, &piece_type);        
    }
    sqlite3_finalize(stmt);
}

void db_select_all_brand(char *token_str) {
     const char *sql = 
        "SELECT * FROM Brand";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    
    Brand brand;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        memset(&brand, 0, sizeof(brand));
        brand.id = sqlite3_column_int(stmt, 0);
        strcpy(brand.brand, sqlite3_column_text(stmt, 1));
        // I can always add token 1 start and end as a delimeter for item retrival
        tokenize_brand(token_str, &brand);        
    }
    sqlite3_finalize(stmt);
    printf("%s\n", token_str);
}

void db_select_all_color(char *token_str) {
     const char *sql = 
        "SELECT * FROM Color";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    
    Color color;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        memset(&color, 0, sizeof(color));
        color.id = sqlite3_column_int(stmt, 0);
        strcpy(color.color, sqlite3_column_text(stmt, 1));
        // I can always add token 1 start and end as a delimeter for item retrival
        tokenize_color(token_str, &color);        
    }
    sqlite3_finalize(stmt);
}

void db_select_all_neckline(char *token_str) {
     const char *sql = 
        "SELECT * FROM Neckline";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    
    Neckline neckline;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        memset(&neckline, 0, sizeof(neckline));
        neckline.id = sqlite3_column_int(stmt, 0);
        strcpy(neckline.neckline, sqlite3_column_text(stmt, 1));
        // I can always add token 1 start and end as a delimeter for item retrival
        tokenize_neckline(token_str, &neckline);        
    }
    sqlite3_finalize(stmt);
}

void db_select_all_sleeves(char *token_str) {
     const char *sql = 
        "SELECT * FROM Sleeves";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    
    Sleeves sleeves;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        memset(&sleeves, 0, sizeof(sleeves));
        sleeves.id = sqlite3_column_int(stmt, 0);
        strcpy(sleeves.sleeves, sqlite3_column_text(stmt, 1));
        // I can always add token 1 start and end as a delimeter for item retrival
        tokenize_sleeves(token_str, &sleeves);        
    }
    sqlite3_finalize(stmt);
}

void db_select_all_type(char *token_str) {
     const char *sql = 
        "SELECT * FROM Type";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    
    Type type;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        memset(&type, 0, sizeof(type));
        type.id = sqlite3_column_int(stmt, 0);
        strcpy(type.type, sqlite3_column_text(stmt, 1));
        // I can always add token 1 start and end as a delimeter for item retrival
        tokenize_type(token_str, &type);        
    }
    sqlite3_finalize(stmt);
}

void db_select_all_condition(char *token_str) {
     const char *sql = 
        "SELECT * FROM Condition";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    
    Condition condition;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        memset(&condition, 0, sizeof(condition));
        condition.id = sqlite3_column_int(stmt, 0);
        strcpy(condition.condition, sqlite3_column_text(stmt, 1));
        // I can always add token 1 start and end as a delimeter for item retrival
        tokenize_condition(token_str, &condition);        
    }
    sqlite3_finalize(stmt);
}

void db_select_all_size(char *token_str) {
     const char *sql = 
        "SELECT * FROM Size";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    
    Size size;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        memset(&size, 0, sizeof(size));
        size.id = sqlite3_column_int(stmt, 0);
        strcpy(size.size, sqlite3_column_text(stmt, 1));
        // I can always add token 1 start and end as a delimeter for item retrival
        tokenize_size(token_str, &size);        
    }
    sqlite3_finalize(stmt);
}

void db_select_sweater(char *token_str, Sweater *sweater) {
    const char *sql = 
        "SELECT id, sweater FROM sweater WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, sweater->id);
    sqlite3_step(stmt);

    sweater->id = sqlite3_column_int(stmt, 0);
    //strcpy(sweater->sweater, sqlite3_column_text(stmt, 1));
    tokenize_sweater(token_str, sweater);
    
    sqlite3_finalize(stmt);
}

void db_select_note(char *token_str, Note *note) {
    const char *sql = 
        "SELECT id, note FROM Note WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, note->id);
    sqlite3_step(stmt);

    note->id = sqlite3_column_int(stmt, 0);
    //strcpy(note->note, sqlite3_column_text(stmt, 1));
    tokenize_note(token_str, note);
    
    sqlite3_finalize(stmt);
}

void db_select_piece(char *token_str, Piece *piece) {
    const char *sql = 
        "SELECT id, piece FROM Piece WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, piece->id);
    sqlite3_step(stmt);

    piece->id = sqlite3_column_int(stmt, 0);
    //strcpy(piece->piece, sqlite3_column_text(stmt, 1));
    tokenize_piece(token_str, piece);
    
    sqlite3_finalize(stmt);
}

void db_select_piece_type(char *token_str, PieceType *piece_type) {
    const char *sql = 
        "SELECT id, piece_type FROM PieceType WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, piece_type->id);
    sqlite3_step(stmt);

    piece_type->id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(piece_type->piece_type, tmp);
    tokenize_piece_type(token_str, piece_type);
    sqlite3_finalize(stmt);
}

void db_select_brand(char *token_str, Brand *brand) {
    const char *sql = 
        "SELECT id, brand FROM Brand WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, brand->id);
    printf("%d\n", brand->id);
    sqlite3_step(stmt);

    brand->id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    printf("%s\n", tmp);
    strcpy(brand->brand, tmp);
    tokenize_brand(token_str, brand);
    sqlite3_finalize(stmt);
}

void db_select_color(char *token_str, Color *color) {
    const char *sql = 
        "SELECT id, color FROM Color WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, color->id);
    sqlite3_step(stmt);

    color->id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(color->color, tmp);
    tokenize_color(token_str, color);
    sqlite3_finalize(stmt);
}

void db_select_neckline(char *token_str, Neckline *neckline) {
    const char *sql = 
        "SELECT id, neckline FROM Neckline WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, neckline->id);
    sqlite3_step(stmt);

    neckline->id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(neckline->neckline, tmp);
    tokenize_neckline(token_str, neckline);
    sqlite3_finalize(stmt);
}

void db_select_sleeves(char *token_str, Sleeves *sleeves) {
    const char *sql = 
        "SELECT id, sleeves FROM Sleeves WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, sleeves->id);
    sqlite3_step(stmt);

    sleeves->id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(sleeves->sleeves, tmp);
    tokenize_sleeves(token_str, sleeves);
    sqlite3_finalize(stmt);
}

void db_select_type(char *token_str, Type *type) {
    const char *sql = 
        "SELECT id, type FROM Type WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, type->id);
    sqlite3_step(stmt);

    type->id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(type->type, tmp);
    tokenize_type(token_str, type);
    sqlite3_finalize(stmt);
}

void db_select_condition(char *token_str, Condition *condition) {
    const char *sql = 
        "SELECT id, condition FROM Condition WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, condition->id);
    sqlite3_step(stmt);

    condition->id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(condition->condition, tmp);
    tokenize_condition(token_str, condition);
    sqlite3_finalize(stmt);
}

void db_select_size(char *token_str, Size *size) {
    const char *sql = 
        "SELECT id, size FROM Size WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, size->id);
    sqlite3_step(stmt);

    size->id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(size->size, tmp);
    tokenize_size(token_str, size);
    sqlite3_finalize(stmt);
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

