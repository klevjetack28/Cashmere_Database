#ifndef PAYLOAD_H
#define PAYLOAD_H

#include "db_tables.h"
#include "packet.h"
#include "0xca75.h"
#include "query.h"

int payload_encode_sweater_filter(char *payload, int payload_size, SweaterFilter *sweater_filter);
SweaterFilter payload_decode_sweater_filter(char *payload);

int payload_encode_sweater_search(char *payload, int payload_size, SweaterSearch *sweater_search);
SweaterSearch payload_decode_sweater_search(char *payload);
int payload_encode_sweater_rows(char *payload, Sweater *sweater, int count);
int payload_decode_sweater_rows(char *payload, Sweater *sweater);
int payload_encode_sweater(char *payload, int payload_size, Sweater *sweater);
Sweater payload_decode_sweater(char *payload);

int payload_encode_note_search(char *payload, int payload_size, NoteSearch *note_search);
NoteSearch payload_decode_note_search(char *payload);
int payload_encode_note_rows(char *payload, Note *note, int count);
int payload_decode_note_rows(char *payload, Note *note);
int payload_encode_note(char *payload, int payload_size, Note *note);
Note payload_decode_note(char *payload);

int payload_encode_piece_search(char *payload, int payload_size, PieceSearch *piece_search);
PieceSearch payload_decode_piece_search(char *payload);
int payload_encode_piece_rows(char *payload, Piece *piece, int count);
int payload_decode_piece_rows(char *payload, Piece *piece);
int payload_encode_piece(char *payload, int payload_size, Piece *piece);
Piece payload_decode_piece(char *payload);

int payload_encode_piece_type_rows(char *payload, PieceType *piece_type, int count);
int payload_decode_piece_type_rows(char *payload, PieceType *piece_type);
int payload_encode_piece_type(char *payload, int payload_size, PieceType *piece_type);
PieceType payload_decode_piece_type(char *payload);

int payload_encode_brand_rows(char *payload, Brand *brand, int count);
int payload_decode_brand_rows(char *payload, Brand *brand);
int payload_encode_brand(char *payload, int payload_size, Brand *brand);
Brand payload_decode_brand(char *payload);

int payload_encode_color_family_rows(char *payload, ColorFamily *color_family, int count);
int payload_decode_color_family_rows(char *payload, ColorFamily *color_family);
int payload_encode_color_family(char *payload, int payload_size, ColorFamily *color_family);
ColorFamily payload_decode_color_family(char *payload);

int payload_encode_color_rows(char *payload, Color *color, int count);
int payload_decode_color_rows(char *payload, Color *color);
int payload_encode_color(char *payload, int payload_size, Color *color);
Color payload_decode_color(char *payload);

int payload_encode_neckline_rows(char *payload, Neckline *neckline, int count);
int payload_decode_neckline_rows(char *payload, Neckline *neckline);
int payload_encode_neckline(char *payload, int payload_size, Neckline *neckline);
Neckline payload_decode_neckline(char *payload);

int payload_encode_sleeves_rows(char *payload, Sleeves *sleeves, int count);
int payload_decode_sleeves_rows(char *payload, Sleeves *sleeves);
int payload_encode_sleeves(char *payload, int payload_size, Sleeves *sleeves);
Sleeves payload_decode_sleeves(char *payload);

int payload_encode_type_rows(char *payload, Type *type, int count);
int payload_decode_type_rows(char *payload, Type *type);
int payload_encode_type(char *payload, int payload_size, Type *type);
Type payload_decode_type(char *payload);

int payload_encode_condition_rows(char *payload, Condition *condition, int count);
int payload_decode_condition_rows(char *payload, Condition *condition);
int payload_encode_condition(char *payload, int payload_size, Condition *condition);
Condition payload_decode_condition(char *payload);

int payload_encode_size_rows(char *payload, Size *size, int count);
int payload_decode_size_rows(char *payload, Size *size);
int payload_encode_size(char *payload, int payload_size, Size *size);
Size payload_decode_size(char *payload);

int payload_encode_id(char *payload, int payload_size, int id);
int payload_decode_id(char *payload);

int payload_encode_pagination(char *payload, int payload_size, Pagination *pagination);
Pagination payload_decode_pagination(char *payload);

int payload_encode_count(char *payload, int payload_size, int count);
int payload_decode_count(char *payload);

#endif // PAYLOAD_H
