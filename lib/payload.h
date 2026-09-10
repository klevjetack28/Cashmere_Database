#ifndef PAYLOAD_H
#define PAYLOAD_H

#include "db_tables.h"
#include "packet.h"
#include "0xca75.h"
#include "db_filters.h"
#include "constants.h"

typedef enum {
    PAYLOAD_STATUS_OK = 0,
    PAYLOAD_STATUS_ERROR
} PayloadStatus;

int payload_encode_sweater_filter(char *payload, int payload_size, SweaterFilter *sweater_filter_in);
SweaterFilter payload_decode_sweater_filter(char *payload);

int payload_encode_sweater_search(char *payload, int payload_size, SweaterSearch *sweater_search);
SweaterSearch payload_decode_sweater_search(char *payload);
int payload_encode_sweater_rows(char *payload, Sweater *sweater_rows, int count);
int payload_decode_sweater_rows(char *payload, Sweater *sweater_rows);
int payload_encode_sweater(char *payload, int payload_size, Sweater *sweater);
Sweater payload_decode_sweater(char *payload);

int payload_encode_note_search(char *payload, int payload_size, NoteSearch *note_search);
NoteSearch payload_decode_note_search(char *payload);
int payload_encode_note_rows(char *payload, Note *note_rows, int count);
int payload_decode_note_rows(char *payload, Note *note_rows);
int payload_encode_note(char *payload, int payload_size, Note *note);
Note payload_decode_note(char *payload);

int payload_encode_piece_search(char *payload, int payload_size, PieceSearch *piece_search);
PieceSearch payload_decode_piece_search(char *payload);
int payload_encode_piece_rows(char *payload, Piece *piece_rows, int count);
int payload_decode_piece_rows(char *payload, Piece *piece_rows);
int payload_encode_piece(char *payload, int payload_size, Piece *piece);
Piece payload_decode_piece(char *payload);

PayloadStatus payload_encode_piece_type_rows(char payload_out[], int payload_capacity, int *payload_length_out, const PieceType piece_types_in[], int piece_type_count);
PayloadStatus payload_decode_piece_type_rows(const char payload_in[], int payload_length, PieceType piece_types_out[], int piece_type_capacity, int *piece_type_count_out);
PayloadStatus payload_encode_piece_type(char payload_out[], int payload_capacity, int *payload_length_out, const PieceType *piece_type_in);
PayloadStatus payload_decode_piece_type(const char payload_in[], int payload_length, PieceType *piece_type_out);

PayloadStatus payload_encode_brand_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Brand brands_in[], int brand_count);
PayloadStatus payload_decode_brand_rows(const char payload_in[], int payload_length, Brand brands_out[], int brand_capacity, int *brand_count_out);
PayloadStatus payload_encode_brand(char payload_out[], int payload_capacity, int *payload_length_out, const Brand *brand_in);
PayloadStatus payload_decode_brand(const char payload_in[], int payload_length, Brand *brand_out);

PayloadStatus payload_encode_color_family_rows(char payload_out[], int payload_capacity, int *payload_length_out, const ColorFamily color_familys_in[], int color_family_count);
PayloadStatus payload_decode_color_family_rows(const char payload_in[], int payload_length, ColorFamily color_familys_out[], int color_family_capacity, int *color_family_count_out);
PayloadStatus payload_encode_color_family(char payload_out[], int payload_capacity, int *payload_length_out, const ColorFamily *color_family_in);
PayloadStatus payload_decode_color_family(const char payload_in[], int payload_length, ColorFamily *color_family_out);

PayloadStatus payload_encode_color_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Color colors_in[], int color_count);
PayloadStatus payload_decode_color_rows(const char payload_in[], int payload_length, Color colors_out[], int color_capacity, int *color_count_out);
PayloadStatus payload_encode_color(char payload_out[], int payload_capacity, int *payload_length_out, const Color *color_in);
PayloadStatus payload_decode_color(const char payload_in[], int payload_length, Color *color_out);

PayloadStatus payload_encode_neckline_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Neckline necklines_in[], int neckline_count);
PayloadStatus payload_decode_neckline_rows(const char payload_in[], int payload_length, Neckline necklines_out[], int neckline_capacity, int *neckline_count_out);
PayloadStatus payload_encode_neckline(char payload_out[], int payload_capacity, int *payload_length_out, const Neckline *neckline_in);
PayloadStatus payload_decode_neckline(const char payload_in[], int payload_length, Neckline *neckline_out);

PayloadStatus payload_encode_sleeves_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Sleeves sleeves_in[], int sleeve_count);
PayloadStatus payload_decode_sleeves_rows(const char payload_in[], int payload_length, Sleeves sleeves_out[], int sleeve_capacity, int *sleeve_count_out);
PayloadStatus payload_encode_sleeves(char payload_out[], int payload_capacity, int *payload_length_out, const Sleeves *sleeves_in);
PayloadStatus payload_decode_sleeves(const char payload_in[], int payload_length, Sleeves *sleeves_out);

PayloadStatus payload_encode_type_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Type types_in[], int type_count);
PayloadStatus payload_decode_type_rows(const char payload_in[], int payload_length, Type types_out[], int type_capacity, int *type_count_out);
PayloadStatus payload_encode_type(char payload_out[], int payload_capacity, int *payload_length_out, const Type *type_in);
PayloadStatus payload_decode_type(const char payload_in[], int payload_length, Type *type_out);

PayloadStatus payload_encode_condition_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Condition conditions_in[], int condition_count);
PayloadStatus payload_decode_condition_rows(const char payload_in[], int payload_length, Condition conditions_out[], int condition_capacity, int *condition_count_out);
PayloadStatus payload_encode_condition(char payload_out[], int payload_capacity, int *payload_length_out, const Condition *condition_in);
PayloadStatus payload_decode_condition(const char payload_in[], int payload_length, Condition *condition_out);

PayloadStatus payload_encode_size_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Size sizes_in[], int size_count);
PayloadStatus payload_decode_size_rows(const char payload_in[], int payload_length, Size sizes_out[], int size_capacity, int *size_count_out);
PayloadStatus payload_encode_size(char payload_out[], int payload_capacity, int *payload_length_out, const Size *size_in);
PayloadStatus payload_decode_size(const char payload_in[], int payload_length, Size *size_out);

PayloadStatus payload_encode_id(char payload_out[], int payload_capacity, int *payload_length_out, int id);
PayloadStatus payload_decode_id(const char payload_in[], int payload_length, int *id);

PayloadStatus payload_encode_pagination(char payload_out[], int payload_capacity, int *payload_length_out, const Pagination *pagination_in);
PayloadStatus payload_decode_pagination(const char payload_in[], int payload_length, Pagination *pagination_out);

#endif // PAYLOAD_H
