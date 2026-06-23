#include "database.h"

sqlite3 *db = NULL;

int db_init(const char *filename) {
    if (sqlite3_open("cashmere.db", &db) != SQLITE_OK) {
        printf("sqlite3_open: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    char *sql = read_entire_file(filename);

    char *err = NULL;
    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        printf("sqlite3_exec: %s\n", err);
        sqlite3_free(err);
        return -1;
    }
    
    return 0;
}

int db_close() {
    if (db) sqlite3_close(db);
}



int db_read_sweater_rows(Sweater **sweater_rows, Pagination *pagination) {

    int count = 0;
}

int db_read_note_rows(Note **note_rows, Pagination *pagination) {

    int count = 0;
}

int db_read_piece_rows(Piece **piece_rows, Pagination *pagination) {

    int count = 0;
}

int db_read_piece_type_rows(PieceType **piece_type_rows, Pagination *pagination) {
     const char *sql = 
        "SELECT * LIMIT ? OFFSET ? FROM PieceType";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, pagination.limit);
    sqlite3_bind_int(stmt, 2, pagination.offset);

    int count = 0;
    PieceType *piece_type_rows;
    for (int i = 0; i < pagination.limit; i++) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            memset(&piece_type_rows[i], 0, sizeof(piece_type_rows[0]));
            piece_type_rows[i].id = sqlite3_column_int(stmt, 0);
            strcpy(piece_type_rows[i].piece_type, sqlite3_column_text(stmt, 1));
        }
        count++;
    }

    sqlite3_finalize(stmt);
    return count;
}

int db_read_brand_rows(Brand **brand_rows, Pagination *pagination) {
    const char *sql = 
        "SELECT * LIMIT ? OFFSET ? FROM Brand";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, pagination.limit);
    sqlite3_bind_int(stmt, 2, pagination.offset);
   
    int count = 0;
    Brand *brand_rows;
    for (int i = 0; i < pagination.limit; i++) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            memset(&brand_rows[i], 0, sizeof(brand_rows[0]));
            brand_rows[i].id = sqlite3_column_int(stmt, 0);
            strcpy(brand_rows[i].brand, sqlite3_column_text(stmt, 1));
        }
        count++;
    }

    sqlite3_finalize(stmt);
    return count;
}

int db_read_color_family(ColorFamily **color_family_rows, Pagination *pagintion) {
    const char *sql = 
        "SELECT * LIMIT ? OFFSET ? FROM ColorFamily";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, pagination.limit);
    sqlite3_bind_int(stmt, 2, pagination.offset);

    int count = 0;
    ColorFamily *color_family_rows;
    for (int i = 0; i < pagination.limit; i++) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            memset(&color_family_rows[i], 0, sizeof(color_family_rows[0]));
            color_family_rows[i].id = sqlite3_column_int(stmt, 0);
            strcpy(color_fmaily_rows[i].color_family, sqlite3_column_text(stmt, 1));
        }
        count++;
    }
    
    sqlite3_finalize(stmt);
    return count;
}

int db_read_color_rows(Color **color_rows, Pagination *pagination) {
    const char *sql = 
        "SELECT * LIMIT ? OFFSET ? FROM Color";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, pagination.limit);
    sqlite3_bind_int(stmt, 2, pagination.offset);

    int count = 0;
    Color *color_rows;
    for (int i = 0; i < pagination.limit; i++) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            memset(&color_rows[i], 0, sizeof(color_rows[0]));
            color_rows[i].id = sqlite3_column_int(stmt, 0);
            strcpy(color_rows[i].color, sqlite3_column_text(stmt, 1));
        }
        count++;
    }
    
    sqlite3_finalize(stmt);
    return count;
}

int db_read_neckline_rows(Neckline **neckline_rows, Pagination *pagination) {
    const char *sql = 
        "SELECT * LIMIT ? OFFSET ? FROM Neckline";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, pagination.limit);
    sqlite3_bind_int(stmt, 2, pagination.offset);

    int count = 0;
    Neckline *neckline_rows;
    for (int i = 0; i < pagination.limit; i++) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            memset(&neckline_rows[i], 0, sizeof(neckline_rows[0]));
            neckline_rows[i].id = sqlite3_column_int(stmt, 0);
            strcpy(neckline_rows[i].neckline, sqlite3_column_text(stmt, 1));
        }
        count++;
    }

    sqlite3_finalize(stmt);
    return count;
}

int db_read_sleeves_rows(Sleeves **sleeves_rows, Pagination *pagination) {
    const char *sql = 
        "SELECT * LIMIT ? OFFSET ? FROM Sleeves";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, pagination.limit);
    sqlite3_bind_int(stmt, 2, pagination.offset);
   
    int count = 0;
    Sleeves *sleeves_rows;
    for (int i = 0; i < pagination.limit; i++) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            memset(&sleeves_rows[i], 0, sizeof(sleeves_rows[0]));
            sleeves_rows[i].id = sqlite3_column_int(stmt, 0);
            strcpy(sleeves_rows[i].sleeves, sqlite3_column_text(stmt, 1));
        }
        count++;
    }
    
    sqlite3_finalize(stmt);
    return count;
}

int db_read_type_rows(Type **type_rows, Pagination *pagination) {
    const char *sql = 
        "SELECT * LIMIT ? OFFSET ? FROM Type";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, pagination.limit);
    sqlite3_bind_int(stmt, 2, pagination.offset);

    int count = 0;
    Type *type_rows;
    for (int i = 0; i < pagination.limit; i++) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            memset(&type_rows[i], 0, sizeof(type_rows[0]));
            type_rows[i].id = sqlite3_column_int(stmt, 0);
            strcpy(type_rows[i].type, sqlite3_column_text(stmt, 1));
        }
        count++;
    }

    sqlite3_finalize(stmt);
    return count;
}

int db_read_condition_rows(Condition **condition_rows, Pagination *pagination) {
    const char *sql = 
        "SELECT * LIMIT ? OFFSET ? FROM Condition";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, pagination.limit);
    sqlite3_bind_int(stmt, 2, pagination.offset);

    int count = 0;
    Condition *condition_rows;
    for (int i = 0; i < pagination.limit; i++) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            memset(&condition_rows[i], 0, sizeof(condition_rows[0]));
            condition_rows[i].id = sqlite3_column_int(stmt, 0);
            strcpy(condition_rows[i].condition, sqlite3_column_text(stmt, 1));
        }
        count++;
    }

    sqlite3_finalize(stmt);
    return count;
}

int db_read_size_rows(Size **size_rows, Pagination *pagination) {
    const char *sql = 
        "SELECT * LIMIT ? OFFSET ? FROM Size";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, pagination.limit);
    sqlite3_bind_int(stmt, 2, pagination.offset);
    
    int count = 0;
    Size *size_rows;
    for (int i = 0; i < pagination.limit; i++) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            memset(&size_rows[i], 0, size_rowsof(size_rows[0]));
            size_rows[i].id = sqlite3_column_int(stmt, 0);
            strcpy(size_rows[i].size, sqlite3_column_text(stmt, 1));
        }
        count++; 
    }

    sqlite3_finalize(stmt);
    return count;
}

Sweater db_read_sweater_by_id(int id) {
    const char *sql = 
        "SELECT id, brand_id, color_id, neckline_id, sleeves_id, type_id, condition_id, size_id, weight FROM sweater WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    Sweater sweater;
    sweater.id = sqlite3_column_int(stmt, 0);
    sweater.brand_id = sqlite3_column_int(stmt, 1);
    sweater.color_id = sqlite3_column_int(stmt, 2);
    sweater.neckline_id = sqlite3_column_int(stmt, 3);
    sweater.sleeves_id = sqlite3_column_int(stmt, 4);
    sweater.type_id = sqlite3_column_int(stmt, 5);
    sweater.condition_id = sqlite3_column_int(stmt, 6);
    sweater.size_id = sqlite3_column_int(stmt, 7);
    sweater.weight = sqlite3_column_int(stmt, 8);

    sqlite3_finalize(stmt);
    return sweater;
}

Note db_read_note_by_id(int id) {
    const char *sql = 
        "SELECT id, sweater_id, content FROM Note WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    Note note;
    note.id = sqlite3_column_int(stmt, 0);
    note.sweater_id = sqlite3_column_int(stmt, 1);
    strcpy(note.content, sqlite3_column_text(stmt, 2));
    sqlite3_finalize(stmt);

    return note;
}

Piece db_read_piece_by_id(int id) {
    const char *sql = 
        "SELECT id, sweater_id, piece_type_id, original_weight, current_weight, continuous FROM Piece WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    Piece piece;
    piece.id = sqlite3_column_int(stmt, 0);
    piece.sweater_id = sqlite3_column_int(stmt, 1);
    piece.piece_type_id = sqlite_column_int(stmt, 2);
    piece.original_weight = sqlite_column_int(stmt, 3);
    piece.current_weight = sqlite_column_int(stmt, 4);
    piece.continuous = sqlite_column_int(stmt, 5);
    sqlite3_finalize(stmt);

    return piece;
}

PieceType db_read_piece_type_by_id(int id) {
    const char *sql = 
        "SELECT id, piece_type FROM PieceType WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    PieceType piece_type;
    piece_type.id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(piece_type.piece_type, tmp);
    sqlite3_finalize(stmt);

    return piece_type;
}

Brand db_read_brand_by_id(int id) {
    const char *sql = 
        "SELECT id, brand FROM Brand WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    Brand brand;
    brand.id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(brand.brand, tmp);
    sqlite3_finalize(stmt);

    return brand;
}

ColorFamily db_read_color_family_by_id(int id) {
    const char *sql = 
        "SELECT id, color_family FROM ColorFamily WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    ColorFamily color_family;
    color_family.id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(color_family.color_family, tmp);
    sqlite3_finalize(stmt);

    return color_family;

}

Color db_read_color_by_id(int id) {
    const char *sql = 
        "SELECT id, color FROM Color WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    Color color;
    color.id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(color.color, tmp);
    sqlite3_finalize(stmt);

    return color;
}

Neckline db_read_neckline_by_id(int id) {
    const char *sql = 
        "SELECT id, neckline FROM Neckline WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    Neckline neckline;
    neckline.id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(neckline.neckline, tmp);
    sqlite3_finalize(stmt);

    return neckline;
}

Sleeves db_read_sleeves_by_id(int id) {
    const char *sql = 
        "SELECT id, sleeves FROM Sleeves WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    Sleeves sleeves;
    sleeves.id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(sleeves.sleeves, tmp);
    sqlite3_finalize(stmt);

    return sleeves;
}

Type db_read_type_by_id(int id) {
    const char *sql = 
        "SELECT id, type FROM Type WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    Type type;
    type.id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(type.type, tmp);
    sqlite3_finalize(stmt);

    return type;
}

Condition db_read_condition_by_id(int id) {
    const char *sql = 
        "SELECT id, condition FROM Condition WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    Condition condition;
    condition.id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(condition.condition, tmp);
    sqlite3_finalize(stmt);

    return condition;
}

Size db_read_size_by_id(int id) {
    const char *sql = 
        "SELECT id, size FROM Size WHERE id = ?";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);

    Size size;
    size.id = sqlite3_column_int(stmt, 0);
    const char *tmp = sqlite3_column_text(stmt, 1);
    strcpy(size.size, tmp);
    sqlite3_finalize(stmt);

    return size;
}

int db_create_sweater(Sweater *sweater) {
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

int db_create_note(Note *note) {
    const char *sql = "INSERT INTO note(sweater_id, content) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, note->sweater_id);
    sqlite3_bind_text(stmt, 2, note->content, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);
}

int db_create_piece(Piece *piece) {
    const char *sql = 
        "  INSERT INTO piece( "
        "  sweater_id, "
        "  piece_type_id, "
        "  original_weight, "
        "  current_weight, "
        "  continuous) "
        "  VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, piece->sweater_id);
    sqlite3_bind_int(stmt, 2, piece->piece_type_id);
    sqlite3_bind_int(stmt, 3, piece->original_weight);
    sqlite3_bind_int(stmt, 4, piece->current_weight);
    sqlite3_bind_int(stmt, 5, piece->continuous);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);
}

int db_create_piece_type(PieceType *piece_type) {
    const char *sql = "INSERT INTO piece_type(piece_type) VALUES (?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, piece_type->piece_type, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);
}

int db_create_brand(Brand *brand) {
    const char *sql = "INSERT INTO brand(brand) VALUES (?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, brand->brand, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    int id = (int)sqlite3_last_insert_rowid(db);
    return id;
}

int db_create_color_family(ColorFamily *color_family) {
    const char *sql = "INSERT INTO color_family(color_family) VALUES (?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, color_family->color_family, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);
}

int db_create_color(Color *color) {
    const char *sql = "INSERT INTO color(color_family_id, color) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, color->color_family_id);
    sqlite3_bind_text(stmt, 2, color->color, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);
}

int db_create_neckline(Neckline *neckline) {
    const char *sql = "INSERT INTO neckline(neckline) VALUES (?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, neckline->neckline, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);
}

int db_create_sleeves(Sleeves *sleeves) {
    const char *sql = "INSERT INTO sleeves(sleeves) VALUES (?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, sleeves->sleeves, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);   
}

int db_create_type(Type *type) {
    const char *sql = "INSERT INTO type(type) VALUES (?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, type->type, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);   
}

int db_create_condition(Condition *condition) {
    const char *sql = "INSERT INTO condition(condition) VALUES (?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, condition->condition, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);   
}

int db_create_size(Size *size) {
    const char *sql = "INSERT INTO size(size) VALUES (?);";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, size->size, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);
}

int db_update_sweater(Sweater *sweater) {

}

int db_update_note(Note *note) {

}

int db_update_piece(Piece *piece) {

}

int db_update_piece_type(PieceType *piece_type) {

}

int db_update_brand(Brand *brand) {

}

int db_update_color_family(COlorFamily *color_family) {

}

int db_update_color(Color *color) {

}

int db_update_neckline(Neckline *neckline) {

}

int db_update_sleeves(Sleeves *sleeves) {

}

int db_update_type(Type *type) {

}

int db_update_condition(Condition *condition) {

}

int db_update_size(Size *size) {

}

int db_delete_sweater_by_id(int id) {

}

int db_delete_note_by_id(int id) {

}

int db_delete_piece_by_id(int id) {

}

int db_delete_piece_type_by_id(int id) {

}

int db_delete_brand_by_id(int id) {

}

int db_delete_color_family_by_id(int id) {

}

int db_delete_color_by_id(int id) {

}

int db_delete_neckline_by_id(int id) {

}

int db_delete_sleeves_by_id(int id) {

}

int db_delete_type_by_id(int id) {

}

int db_delete_condition_by_id(int id) {

}

int db_delete_size_by_id(int id) {

}


