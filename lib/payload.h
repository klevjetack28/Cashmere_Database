#ifndef PAYLOAD_H
#define PAYLOAD_H

#include "db_tables.h"
#include "packet.h"
#include "0xca75.h"

char *payload_encode_sweater(Sweater *sweater);
char *payload_encode_note(Note *note);
char *payload_encode_piece(Piece *piece);
char *payload_encode_piece_type(PieceType *piece_type);
char *payload_encode_brand(Brand *brand);
char *payload_encode_color_family(ColorFamily *color_family);
char *payload_encode_color(Color *color);
char *payload_encode_neckline(Neckline *neckline);
char *payload_encode_sleeves(Sleeves *sleeves);
char *payload_encode_type(Type *type);
char *payload_encode_condition(Condition *condition);
char *payload_encode_size(Size *size);

Sweater payload_decode_sweater(char *payload);
Note payload_decode_note(char *payload);
Piece payload_decode_piece(char *payload);
PieceType payload_decode_piece_type(char *payload);
Brand payload_decode_brand(char *payload);
ColorFamily payload_decode_color_family(char *payload);
Color payload_decode_color(char *payload);
Neckline payload_decode_neckline(char *payload);
Sleeves payload_decode_sleeves(char *payload);
Type payload_decode_type(char *payload);
Condition payload_decode_condition(char *payload);
Size payload_decode_size(char *payload);

#endif // PAYLOAD_H
