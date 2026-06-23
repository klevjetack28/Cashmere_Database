#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#include "db_tables.h"
#include "0xca75.h"
#include "query.h"

int db_init(const char *filename);
int db_close();

db_read_sweater_rows(Sweater **sweater_rows, int limit, int offset);
db_read_note_rows(Note **note_rows, int limit, int offset);
db_read_piece_rows(Piece ** piece_rows, int limit, int offset);
db_read_piece_type_rows(PieceType **piece_type_rows, int limit, int offset);
db_read_brand_rows(Brand **brand_rows, int limit int offset);
db_read_color_rows(Color **color_rows, int limit, int offset);
db_read_neckline_rows(Neckline **neckline_rows, int limit, int offset);
db_read_sleeves_rows(Sleeves **sleeves_rows, int limit, int offset);
db_read_type_rows(Type **type_rows, int limit, int offset);
db_read_condition_rows(Condition **condition_rows, int limit, int offset);
db_read_size_rows(Size **size_rows, int limit, int offset);

Sweater db_read_sweater_by_id(int id);
Note db_read_note_by_id(int id);
Piece db_read_piece_by_id(int id);
PieceType db_read_piece_type_by_id(int id);
Brand db_read_brand_by_id(int id);
Color db_read_color_by_id(int id);
Neckline db_read_neckline_by_id(int id);
Sleeves db_read_sleeves_by_id(int id);
Type db_read_type_by_id(int id);
Condition db_read_condition_by_id(int id);
Size db_read_size_by_id(int id);

int db_create_sweater(Sweater *sweater);
int db_create_note(Note *note);
int db_create_piece(Piece *piece);
int db_create_piece_type(PieceType *piece_type);
int db_create_brand(Brand *brand);
int db_create_color_family(ColorFamily *color_family);
int db_create_color(Color *color);
int db_create_neckline(Neckline *neckline);
int db_create_sleeves(Sleeves *sleeves);
int db_create_type(Type *type);
int db_create_condition(Condition *condition);
int db_create_size(Size *size);

int db_update_sweater(Sweater *sweater);
int db_update_note(Note *note);
int db_update_piece(Piece *piece);
int db_update_piece_type(PieceType *piece_type);
int db_update_brand(Brand *brand);
int db_update_color(Color *color);
int db_update_neckline(Neckline *neckline);
int db_update_sleeves(Sleeves *sleeves);
int db_update_type(Type *type);
int db_update_condition(Condition *condition);
int db_update_size(Size *size);

int db_delete_sweater_by_id(int id);
int db_delete_note_by_id(int id);
int db_delete_piece_by_id(int id);
int db_delete_piece_type_by_id(int id);
int db_delete_brand_by_id(int id);
int db_delete_color_by_id(int id);
int db_delete_neckline_by_id(int id);
int db_delete_sleeves_by_id(int id);
int db_delete_type_by_id(int id);
int db_delete_condition_by_id(int id);
int db_delete_size_by_id(int id);

#endif // DATABASE_H
