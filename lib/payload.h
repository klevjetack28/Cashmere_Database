#ifndef PAYLOAD_H
#define PAYLOAD_H

#include "db_tables.h"
#include "packet.h"
#include "0xca75.h"
#include "query.h"

char *payload_encode_sweater_filter(SweaterFilter *sweater_filter);
SweaterFilter payload_decode_sweater_filter(char *payload);

char *payload_encode_sweater_search(SweaterSearch *sweater_search);
SweaterSearch payload_decode_sweater_search(char *payload);
char *payload_encode_sweater_rows(Sweater *sweater, int count);
int payload_decode_sweater_rows(Sweater **sweater, char *payload);
char *payload_encode_sweater(Sweater *sweater);
Sweater payload_decode_sweater(char *payload);

char *payload_encode_note_search(NoteSearch *note_search);
NoteSearch payload_decode_note_search(char *payload);
char *payload_encode_note_rows(Note *note, int count);
int payload_decode_note_rows(Note **note, char *payload);
char *payload_encode_note(Note *note);
Note payload_decode_note(char *payload);

char *payload_encode_piece_search(PieceSearch *piece_search);
PieceSearch payload_decode_piece_search(char *payload);
char *payload_encode_piece_rows(Piece *piece, int count);
int payload_decode_piece_rows(Piece **piece, char *payload);
char *payload_encode_piece(Piece *piece);
Piece payload_decode_piece(char *payload);

char *payload_encode_piece_type_rows(PieceType *piece_type, int count);
int payload_decode_piece_type_rows(PieceType **piece_type, char *payload);
char *payload_encode_piece_type(PieceType *piece_type);
PieceType payload_decode_piece_type(char *payload);

char *payload_encode_brand_rows(Brand *brand, int count);
int payload_decode_brand_rows(Brand **brand, char *payload);
char *payload_encode_brand(Brand *brand);
Brand payload_decode_brand(char *payload);

char *payload_encode_color_family_rows(ColorFamily *color_family, int count);
int payload_decode_color_family_rows(ColorFamily **color_family, char *payload);
char *payload_encode_color_family(ColorFamily *color_family);
ColorFamily payload_decode_color_family(char *payload);

char *payload_encode_color_rows(Color *color, int count);
int payload_decode_color_rows(Color **color, char *payload);
char *payload_encode_color(Color *color);
Color payload_decode_color(char *payload);

char *payload_encode_neckline_rows(Neckline *neckline, int count);
int payload_decode_neckline_rows(Neckline **neckline, char *payload);
char *payload_encode_neckline(Neckline *neckline);
Neckline payload_decode_neckline(char *payload);

char *payload_encode_sleeves_rows(Sleeves *sleeves, int count);
int payload_decode_sleeves_rows(Sleeves **sleeves, char *payload);
char *payload_encode_sleeves(Sleeves *sleeves);
Sleeves payload_decode_sleeves(char *payload);

char *payload_encode_type_rows(Type *type, int count);
int payload_decode_type_rows(Type **type, char *payload);
char *payload_encode_type(Type *type);
Type payload_decode_type(char *payload);

char *payload_encode_condition_rows(Condition *condition, int count);
int payload_decode_condition_rows(Condition **condition, char *payload);
char *payload_encode_condition(Condition *condition);
Condition payload_decode_condition(char *payload);

char *payload_encode_size_rows(Size *size, int count);
int payload_decode_size_rows(Size **size, char *payload);
char *payload_encode_size(Size *size);
Size payload_decode_size(char *payload);

char *payload_encode_id(int id);
int payload_decode_id(char *payload);

char *payload_encode_pagination(Pagination *pagination);
char *payload_decode_pagination(Pagination *pagination);


#endif // PAYLOAD_H
