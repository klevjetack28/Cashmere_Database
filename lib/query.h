#ifndef QUERY_H
#define QUERY_H

#include "constants.h"

#define MAX_FILTER_IDS 16

typedef struct {
    int offset;
    int limit;
} Pagination;

typedef struct {
    int brand_ids[MAX_FILTER_IDS];
    int brand_count;

    int color_ids[MAX_FILTER_IDS];
    int color_count;

    int neckline_ids[MAX_FILTER_IDS];
    int neckline_count;

    int sleeves_ids[MAX_FILTER_IDS];
    int sleeves_count;

    int type_ids[MAX_FILTER_IDS];
    int type_count;

    int condition_ids[MAX_FILTER_IDS];
    int condition_count;

    int size_ids[MAX_FILTER_IDS];
    int size_count;

    int min_weight;
    int max_weight;
} SweaterFilter;

typedef struct {
    SweaterFilter sweater_filter;
    Pagination page;
} SweaterSearch;

typedef struct {
    int piece_type_ids[MAX_FILTER_IDS];
    int piece_type_count;

    int sweater_ids[MAX_FILTER_IDS];
    int sweater_count;

    int min_original_weight;
    int max_original_weight;

    int min_current_weight;
    int max_current_weight;

    SweaterFilter sweater_filter;

    Pagination page;
} PieceSearch;

typedef struct {
    int sweater_ids[MAX_FILTER_IDS];
    int sweater_count;

    char content[STR_LENGTH];

    SweaterFilter sweater_filter;

    Pagination page;
} NoteSearch;

#endif //QUERY_H
