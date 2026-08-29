#ifndef DB_FILTERS_H
#define DB_FILTERS_H

#include <string.h>

#include "constants.h"

typedef struct {
    int offset;
    int limit;
} Pagination;

typedef struct {
    int brand_ids[MAX_TOKENS];
    int brand_count;

    int color_family_ids[MAX_TOKENS];
    int color_family_count;

    int neckline_ids[MAX_TOKENS];
    int neckline_count;

    int sleeves_ids[MAX_TOKENS];
    int sleeves_count;

    int type_ids[MAX_TOKENS];
    int type_count;

    int condition_ids[MAX_TOKENS];
    int condition_count;

    int size_ids[MAX_TOKENS];
    int size_count;

    int min_weight;
    int max_weight;
} SweaterFilter;

typedef struct {
    SweaterFilter sweater_filter;
    Pagination pagination;
} SweaterSearch;

typedef struct {
    int piece_type_ids[MAX_TOKENS];
    int piece_type_count;

    int sweater_ids[MAX_TOKENS];
    int sweater_count;

    int min_original_weight;
    int max_original_weight;

    int min_current_weight;
    int max_current_weight;

    SweaterFilter sweater_filter;

    Pagination pagination;
} PieceSearch;

typedef struct {
    int sweater_ids[MAX_TOKENS];
    int sweater_count;

    char content[STR_LENGTH];

    SweaterFilter sweater_filter;

    Pagination pagination;
} NoteSearch;

#endif // DB_FILTERS_H
