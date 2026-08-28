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

int db_read_sweater(Sweater *sweater_rows[], Pagination *pagination);
int db_read_note(Note *note_rows[], Pagination *pagination);
int db_read_piece(Piece * piece_rows[], Pagination *pagination);
int db_read_piece_type(PieceType *piece_type_rows[], Pagination *pagination);
int db_read_brand(Brand *brand_rows[], Pagination *pagination);
int db_read_color_faimily(ColorFamily *color_family_rows[], Pagination *pagination);
int db_read_color(Color *color_rows[], Pagination *pagination);
int db_read_neckline(Neckline *neckline_rows[], Pagination *pagination);
int db_read_sleeves(Sleeves *sleeves_rows[], Pagination *pagination);
int db_read_type(Type *type_rows[], Pagination *pagination);
int db_read_condition(Condition *condition_rows[], Pagination *pagination);
int db_read_size(Size *size_rows[], Pagination *pagination);

Sweater db_info_sweater(int id);
Note db_info_note(int id);
Piece db_info_piece(int id);
PieceType db_info_piece_type(int id);
Brand db_info_brand(int id);
ColorFamily db_info_color_family(int id);
Color db_info_color(int id);
Neckline db_info_neckline(int id);
Sleeves db_info_sleeves(int id);
Type db_info_type(int id);
Condition db_info_condition(int id);
Size db_info_size(int id);

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
int db_update_color_family(ColorFamily *color_family);
int db_update_color(Color *color);
int db_update_neckline(Neckline *neckline);
int db_update_sleeves(Sleeves *sleeves);
int db_update_type(Type *type);
int db_update_condition(Condition *condition);
int db_update_size(Size *size);

int db_delete_sweater(int id);
int db_delete_note(int id);
int db_delete_piece(int id);
int db_delete_piece_type(int id);
int db_delete_brand(int id);
int db_delete_color_family(int id);
int db_delete_color(int id);
int db_delete_neckline(int id);
int db_delete_sleeves(int id);
int db_delete_type(int id);
int db_delete_condition(int id);
int db_delete_size(int id);

#endif // DATABASE_H
