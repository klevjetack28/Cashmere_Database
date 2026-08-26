#ifndef DB_PRINT
#define DB_PRINT

#include "db_tables.h"

void print_sweater(const Sweater *sweater);
void print_note(const Note *note);
void print_piece(const Piece *piece);
void print_piece_type(const PieceType *piece_type);
void print_brand(const Brand *brand);
void print_color_family(const ColorFamily *color_family);
void print_color(const Color *color);
void print_neckline(const Neckline *neckline);
void print_sleeves(const Sleeves *sleeves);
void print_type(const Type *type);
void print_condition(const Condition *condition);
void print_size(const Size *size);

#endif // DB_PRINT
