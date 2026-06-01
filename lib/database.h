#ifndef DATABASE_H
#define DATABASE_H

int db_init(const char *path);
int db_close();
db_print_sweater(const Sweater *sweater);
db_print_note(const Note *note);
db_print_piece(const Piece *piece);
db_print_piece_type(const PieceType *piece_type);
db_print_brand(const Brand *brand);
db_print_color(const Color *color);
db_print_neckline(const Neckline *neckline);
db_print_sleeves(const Sleeves *sleeves);
db_print_type(const Type *type);
db_print_condition(const Condition *condition);
db_print_size(const Size *size);
void db_select_all_sweater(char *token_str);
void db_select_all_note(char *token_str);
void db_select_all_piece(char *token_str);
void db_select_all_piece_type(char *token_str);
void db_select_all_brand(char *token_str);
void db_select_all_color(char *token_str);
void db_select_all_neckline(char *token_str);
void db_select_all_sleeves(char *token_str);
void db_select_all_type(char *token_str);
void db_select_all_condition(char *token_str);
void db_select_all_size(char *token_str);
void db_select_sweater(char *token_str, Sweater *sweater);
void db_select_note(char *token_str, Note *note);
void db_select_piece(char *token_str, Piece *piece);
void db_select_piece_type(char *token_str, PieceType *piece_type);
void db_select_brand(char *token_str, Brand *brand);
void db_select_color(char *token_str, Color *color);
void db_select_neckline(char *token_str, Neckline *neckline);
void db_select_sleeves(char *token_str, Sleeves *sleeves);
void db_select_type(char *token_str, Type *type);
void db_select_condition(char *token_str, Condition *condition);
void db_select_size(char *token_str, Size *size);
int db_insert_sweater(Sweater *sweater);
int db_insert_note(Note *note);
int db_insert_piece(Piece *piece);
int db_insert_piece_type(PieceType *piece_type);
int db_insert_brand(Brand *brand);
int db_insert_color(Color *color);
int db_insert_neckline(Neckline *neckline);
int db_insert_sleeves(Sleeves *sleeves);
int db_insert_type(Type *type);
int db_insert_condition(Condition *condition);
int db_insert_size(Size *size);

#endif // DATABASE_H
