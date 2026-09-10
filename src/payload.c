#include "payload.h"

int payload_encode_sweater_filter(char *payload, int payload_size, SweaterFilter *sweater_filter) {
    /*SweaterSearch sweater_search;
 
    char brand_ids[STR_LENGTH] = {0};
    snprintf(brand_ids, STR_LENGTH, "SWEATER_IDS=%d", sweater_filter->brand_ids[0]);
    for (int i = 1; i < sweater_filter->brand_count; i++) {
        char tmp[STR_LENGTH] = {0};
        snprintf(tmp, STR_LENGTH, ",%d", i, sweater_filter->brand_ids[i]);
        strcat(brand_ids, tmp);
    }
   
    char color_family_ids[STR_LENGTH] = {0};
    snprintf(color_family_ids, STR_LENGTH, "SWEATER_IDS=%d", sweater_filter->color_family_ids[0]);
    for (int i = 1; i < sweater_filter->color_family_count; i++) {
        char tmp[STR_LENGTH] = {0};
        snprintf(tmp, STR_LENGTH, ",%d", i, sweater_filter->color_family_ids[i]);
        strcat(color_family_ids, tmp);
    }

    char neckline_ids[STR_LENGTH] = {0};
    snprintf(neckline_ids, STR_LENGTH, "SWEATER_IDS=%d", sweater_filter->neckline_ids[0]);
    for (int i = 1; i < sweater_filter->neckline_count; i++) {
        char tmp[STR_LENGTH] = {0};
        snprintf(tmp, STR_LENGTH, ",%d", i, sweater_filter->neckline_ids[i]);
        strcat(neckline_ids, tmp);
    }

    char sleeves_ids[STR_LENGTH] = {0};
    snprintf(sleeves_ids, STR_LENGTH, "SWEATER_IDS=%d", sweater_filter->sleeves_ids[0]);
    for (int i = 1; i < sweater_filter->sleeves_count; i++) {
        char tmp[STR_LENGTH] = {0};
        snprintf(tmp, STR_LENGTH, ",%d", i, sweater_filter->sleeves_ids[i]);
        strcat(sleeves_ids, tmp);
    }

    char type_ids[STR_LENGTH] = {0};
    snprintf(type_ids, STR_LENGTH, "TYPE_IDS=%d", sweater_filter->type_ids[0]);
    for (int i = 1; i < sweater_filter->type_count; i++) {
        char tmp[STR_LENGTH] = {0};
        snprintf(tmp, STR_LENGTH, ",%d", i, sweater_filter->type_ids[i]);
        strcat(type_ids, tmp);
    }

    char condition_ids[STR_LENGTH] = {0};
    snprintf(condition_ids, STR_LENGTH, "CONDITION_IDS=%d", sweater_filter->condition_ids[0]);
    for (int i = 1; i < sweater_filter->condition_count; i++) {
        char tmp[STR_LENGTH] = {0};
        snprintf(tmp, STR_LENGTH, ",%d", i, sweater_filter->condition_ids[i]);
        strcat(condition_ids, tmp);
    }

    char size_ids[STR_LENGTH] = {0};
    snprintf(size_ids, STR_LENGTH, "SIZE_IDS=%d", sweater_filter->size_ids[0]);
    for (int i = 1; i < sweater_filter->size_count; i++) {
        char tmp[STR_LENGTH] = {0};
        snprintf(tmp, STR_LENGTH, ",%d", i, sweater_filter->size_ids[i]);
        strcat(size_ids, tmp);
    }

    snprintf(payload, payload_size, "MIN_WEIGHT=%d MAX_WEIGHT=%d, SECTION=BRAND_IDS %s, SECTION=COLOR_FAMILY_IDS %s, SECTION=NECKLINE_IDS %s, SECTION=SLEEVES_IDS %s, SECTION=TYPE_IDS %s, SECTION=CONDITION_IDS %s, SECTION=SIZE_IDS %s", sweater_filter->min_weight, sweater_filter->max_weight, brand_ids, color_family_ids, neckline_ids, sleeves_ids, type_ids, condition_ids, size_ids);
    return strlen(payload);*/
}

SweaterFilter payload_decode_sweater_filter(char *payload) {
    /*SweaterFilter sweater_filter = {0};

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {   
        char *token[TOKEN_PAIR];
        str_split(tokens[i], "=", token, TOKEN_PAIR);
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "BRAND_IDS") == 0) {
            char *ids[MAX_TOKENS];
            int num_ids = str_split(value, ",", ids, MAX_TOKENS);
            // this is where i would have the condition for if str_split return -1
            for (int j = 0; j < num_ids; j++) {
                sweater_filter.brand_ids[j] = atoi(value);
            }
            sweater_filter.brand_count = num_ids;
        } else if (strcmp(field, "COLOR_FAMILY_IDS") == 0) {
            char *ids[MAX_TOKENS];
            int num_ids = str_split(value, ",", ids, MAX_TOKENS);

            for (int j = 0; j < num_ids; j++) {
                sweater_filter.color_family_ids[j] = atoi(value);
            }
            sweater_filter.color_family_count = num_ids;
        } else if (strcmp(field, "NECKLINE_IDS") == 0) {
            char *ids[MAX_TOKENS];
            int num_ids = str_split(value, ",", ids, MAX_TOKENS);

            for (int j = 0; j < num_ids; j++) {
                sweater_filter.neckline_ids[j] = atoi(value);
            }
            sweater_filter.neckline_count = num_ids;
        } else if (strcmp(field, "SLEEVES_IDS") == 0) {
            char *ids[MAX_TOKENS];
            int num_ids = str_split(value, ",", ids, MAX_TOKENS);

            for (int j = 0; j < num_ids; j++) {
                sweater_filter.sleeves_ids[j] = atoi(value);
            }
            sweater_filter.sleeves_count = num_ids;
        } else if (strcmp(field, "TYPE_IDS") == 0) {
            char *ids[MAX_TOKENS];
            int num_ids = str_split(value, ",", ids, MAX_TOKENS);

            for (int j = 0; j < num_ids; j++) {
                sweater_filter.type_ids[j] = atoi(value);
            }
            sweater_filter.type_count = num_ids;
        } else if (strcmp(field, "CONDITION_IDS") == 0) {
            char *ids[MAX_TOKENS];
            int num_ids = str_split(value, ",", ids, MAX_TOKENS);

            for (int j = 0; j < num_ids; j++) {
                sweater_filter.condition_ids[j] = atoi(value);
            }
            sweater_filter.condition_count = num_ids;
        } else if (strcmp(field, "SIZE_IDS") == 0) {
            char *ids[MAX_TOKENS];
            int num_ids = str_split(value, ",", ids, MAX_TOKENS);

            for (int j = 0; j < num_ids; j++) {
                sweater_filter.size_ids[j] = atoi(value);
            }
            sweater_filter.size_count = num_ids;
        } else if (strcmp(field, "MIN_WEIGHT") == 0) {
            sweater_filter.min_weight = atoi(value);
        } else if (strcmp(field, "MAX_WEIGHT") == 0) {
            sweater_filter.max_weight = atoi(value);
        } else {
    
        }
    }

    return sweater_filter;*/
}

int payload_encode_sweater_search(char *payload, int payload_size, SweaterSearch *sweater_search) {
    /*char sweater_filter[STR_LENGTH] = {0};
    payload_encode_sweater_filter(sweater_filter, STR_LENGTH, &sweater_search->sweater_filter);

    char pagination[STR_LENGTH] = {0};
    payload_encode_pagination(pagination, STR_LENGTH, &sweater_search->pagination);

    snprintf(payload, payload_size, "SECTION=SWEATER_FILTER %s, SECTION=PAGINATION %s", sweater_filter, pagination);
    return strlen(payload);*/
}

SweaterSearch payload_decode_sweater_search(char *payload) {
    /*SweaterSearch sweater_search;
    
    char *sections[MAX_TOKENS];
	int num_sections = str_split(payload, ", ", sections, MAX_TOKENS);
    for (int i = 0; i < num_sections; i++) {
        char *tokens[MAX_TOKENS];
	    int num_tokens = str_split(sections[i], " ", tokens, MAX_TOKENS);
        
        char *section[TOKEN_PAIR];
        str_split(tokens[i], "=", section, TOKEN_PAIR);
        char *field = section[0];
        char *value = section[1];

        if (strcmp(field, "SWEATER_FILTER") == 0) {
            sweater_search.sweater_filter = payload_decode_sweater_filter(sections[i]);
        } else if (strcmp(field, "PAGINATION") == 0) {
            sweater_search.pagination = payload_decode_pagination(sections[i]);
        } else {

        }
    }

    return sweater_search;*/
}

int payload_encode_sweater_rows(char *payload, Sweater *sweater_rows, int row_count) {
    /*for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_sweater(tmp, sizeof(tmp), &sweater_rows[i]);
        strcat(payload, tmp);
    }

    return strlen(payload);*/
}

int payload_decode_sweater_rows(char *payload, Sweater *sweater_rows) {
    /*char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);

    for (int i = 0; i < num_tokens; i++) {
        sweater_rows[i] = payload_decode_sweater(tokens[i + 1]);
    }

    return num_tokens;*/
}

int payload_encode_sweater(char *payload, int payload_size, Sweater *sweater) {
    /*snprintf(payload, payload_size, 
            "ID=%d BRAND_ID=%d COLOR_ID=%d NECKLINE_ID=%d SLEEVES_ID=%d TYPE_ID=%d CONDITION_ID=%d SIZE_ID=%d WEIGHT=%d", 
            sweater->id, 
            sweater->brand_id, 
            sweater->color_id, 
            sweater->neckline_id, 
            sweater->sleeves_id, 
            sweater->type_id, 
            sweater->condition_id, 
            sweater->size_id, 
            sweater->weight
            );

    return strlen(payload);*/
}

Sweater payload_decode_sweater(char *payload) {
    /*Sweater sweater;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {   
        char *token[TOKEN_PAIR];
        str_split(tokens[i], "=", token, TOKEN_PAIR);
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            sweater.id = atoi(value);
        } else if (strcmp(field, "BRAND_ID") == 0) {
            sweater.brand_id = atoi(value);
        } else if (strcmp(field, "COLOR_ID") == 0) {
            sweater.color_id = atoi(value);
        } else if (strcmp(field, "NECKLINE_ID") == 0) {
            sweater.neckline_id = atoi(value);
        } else if (strcmp(field, "SLEEVES_ID") == 0) {
            sweater.sleeves_id = atoi(value);
        } else if (strcmp(field, "TYPE_ID") == 0) {
            sweater.type_id = atoi(value);
        } else if (strcmp(field, "CONDITION_ID") == 0) {
            sweater.condition_id = atoi(value);
        } else if (strcmp(field, "SIZE_ID") == 0) {
            sweater.size_id = atoi(value);
        } else if (strcmp(field, "WEIGHT") == 0) {
            sweater.weight = atoi(value);
        } else {
    
        }
    }

    return sweater;*/
}

int payload_encode_note_search(char *payload, int payload_size, NoteSearch *note_search) {
    /*char sweater_filter[STR_LENGTH] = {0};
    payload_encode_sweater_filter(sweater_filter, STR_LENGTH, &note_search->sweater_filter);

    char pagination[STR_LENGTH] = {0};
    payload_encode_pagination(pagination, STR_LENGTH, &note_search->pagination);

    char sweater_ids[STR_LENGTH] = {0};
    snprintf(sweater_ids, STR_LENGTH, "SWEATER_IDS=%d", note_search->sweater_ids[0]);
    for (int i = 1; i < note_search->sweater_count; i++) {
        char tmp[STR_LENGTH] = {0};
        snprintf(tmp, STR_LENGTH, ",%d", i, note_search->sweater_ids[i]);
        strcat(sweater_ids, tmp);
    }
    
    snprintf(payload, payload_size, "CONTENT=%s, SECTION=SWEATER_IDS %s, SECTION=SWEATER_FILTER %s, SECTION=PAGINATION %s", note_search->content, sweater_ids, sweater_filter, pagination);
    return strlen(payload);*/
}

NoteSearch payload_decode_note_search(char *payload) {
    /*NoteSearch note_search;
    
    char *sections[MAX_TOKENS];
	int num_sections = str_split(payload, ", ", sections, MAX_TOKENS);
    for (int i = 0; i < num_sections; i++) {
        char *tokens[MAX_TOKENS];
	    int num_tokens = str_split(sections[i], " ", tokens, MAX_TOKENS);
        
        char *section[TOKEN_PAIR];
        str_split(tokens[i], "=", section, TOKEN_PAIR);
        char *field = section[0];
        char *value = section[1];

        if (strcmp(field, "SWEATER_IDS") == 0) {
            char *ids[MAX_TOKENS];
            int num_ids = str_split(value, ",", ids, MAX_TOKENS);

            for (int j = 0; j < num_ids; j++) {
                note_search.sweater_ids[j] = atoi(ids[j]);
            }
        } else if (strcmp(field, "CONTENT") == 0) {
            strcpy(note_search.content, field);
        } else if (strcmp(field, "SWEATER_FILTER") == 0) {
            note_search.sweater_filter = payload_decode_sweater_filter(sections[i]);
        } else if (strcmp(field, "PAGINATION") == 0) {
            note_search.pagination = payload_decode_pagination(sections[i]);
        } else {

        }
    }

    return note_search;*/
}

int payload_encode_note_rows(char *payload, Note *note_rows, int row_count) {
    /*for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_note(tmp, sizeof(tmp), &note_rows[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);*/
}

int payload_decode_note_rows(char *payload, Note *note_rows) {
    /*char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    
    
    for (int i = 0; i < num_tokens; i++) {
        note_rows[i] = payload_decode_note(tokens[i]);
    }

    return num_tokens;*/
}

int payload_encode_note(char *payload, int payload_size, Note *note) {
    /*snprintf(payload, payload_size, 
            "ID=%d SWEATER_ID=%d CONTENT=%s", 
            note->id, 
            note->sweater_id, 
            note->content
            );

    return strlen(payload);*/
}

Note payload_decode_note(char *payload) {
    /*Note note;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char *token[TOKEN_PAIR];
        str_split(tokens[i], "=", token, TOKEN_PAIR);       
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            note.id = atoi(value);
        } else if (strcmp(field, "SWEATER_ID") == 0) {
            note.sweater_id = atoi(value);
        } else if (strcmp(field, "CONTENT") == 0) {
            strcpy(note.content, value);
        } else {

        }
    }

    return note;*/
}

int payload_encode_piece_search(char *payload, int payload_size, PieceSearch *piece_search) {
    /*char sweater_filter[STR_LENGTH] = {0};
    payload_encode_sweater_filter(sweater_filter, STR_LENGTH, &piece_search->sweater_filter);

    char pagination[STR_LENGTH] = {0};
//    payload_encode_pagination(pagination, STR_LENGTH, &piece_search->pagination);

    char sweater_ids[STR_LENGTH] = {0};
    snprintf(sweater_ids, STR_LENGTH, "SWEATER_IDS=%d", piece_search->sweater_ids[0]);
    for (int i = 1; i < piece_search->sweater_count; i++) {
        char tmp[STR_LENGTH] = {0};
        snprintf(tmp, STR_LENGTH, ",%d", i, piece_search->sweater_ids[i]);
        strcat(sweater_ids, tmp);
    }
    
    char piece_type_ids[STR_LENGTH] = {0};
    snprintf(piece_type_ids, STR_LENGTH, "PIECE_TYPE_IDS=%d", piece_search->piece_type_ids[0]);
    for (int i = 1; i < piece_search->piece_type_count; i++) {
        char tmp[STR_LENGTH] = {0};
        snprintf(tmp, STR_LENGTH, ",%d", i, piece_search->piece_type_ids[i]);
        strcat(sweater_ids, tmp);
    }
    
    snprintf(payload, payload_size, "MIN_ORIGINAL_WEIGHT=%d MAX_ORIGINAL_WEIGHT=%d MIN_CURRENT_WEIGHT=%d MAX_CURRENT_WEIGHT=%d, SECTION=SWEATER_IDS %s, SECTION=PIECE_TYPE_IDS %s, SECTION=SWEATER_FILTER %s, SECTION=PAGINATION %s", piece_search->min_original_weight, piece_search->max_original_weight, piece_search->min_current_weight, piece_search->max_current_weight, sweater_ids, piece_type_ids, sweater_filter, pagination);
    return strlen(payload);*/

}

PieceSearch payload_decode_piece_search(char *payload) {
    /*PieceSearch piece_search;
    
    char *sections[MAX_TOKENS];
	int num_sections = str_split(payload, ", ", sections, MAX_TOKENS);
    for (int i = 0; i < num_sections; i++) {
        char *tokens[MAX_TOKENS];
	    int num_tokens = str_split(sections[i], " ", tokens, MAX_TOKENS);
        
        char *section[TOKEN_PAIR];
        str_split(tokens[i], "=", section, TOKEN_PAIR);
        char *field = section[0];
        char *value = section[1];

        if (strcmp(field, "SWEATER_IDS") == 0) {
            char *ids[MAX_TOKENS];
            int num_ids = str_split(value, ",", ids, MAX_TOKENS);

            for (int j = 0; j < num_ids; j++) {
                piece_search.sweater_ids[j] = atoi(ids[j]);
            }
        } else if (strcmp(field, "PIECE_TYPE_IDS") == 0) {
            char *ids[MAX_TOKENS];
            int num_ids = str_split(value, ",", ids, MAX_TOKENS);

            for (int j = 0; j < num_ids; j++) {
                piece_search.piece_type_ids[j] = atoi(ids[j]);
            }
        } else if (strcmp(field, "MIN_ORIGINAL_WEIGHT") == 0) {
            piece_search.min_original_weight = atoi(value);
        } else if (strcmp(field, "MAX_ORIGINAL_WEIGHT") == 0) {
            piece_search.max_original_weight = atoi(value);
        } else if (strcmp(field, "MIN_CURRENT_WEIGHT") == 0) {
            piece_search.min_current_weight = atoi(value);
        } else if (strcmp(field, "MAX_CURRENT_WEIGHT") == 0) {
            piece_search.max_current_weight = atoi(value);
        } else if (strcmp(field, "SWEATER_FILTER") == 0) {
            piece_search.sweater_filter = payload_decode_sweater_filter(sections[i]);
        } else if (strcmp(field, "PAGINATION") == 0) {
 //           piece_search.pagination = payload_decode_pagination(sections[i]);
        } else {

        }
    }

    return piece_search;*/
}

int payload_encode_piece_rows(char *payload, Piece *piece_rows, int row_count) {
    /*for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_piece(tmp, sizeof(tmp), &piece_rows[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);*/
}

int payload_decode_piece_rows(char *payload, Piece *piece_rows) {
    /*char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    

    for (int i = 0; i < num_tokens; i++) {
        piece_rows[i] = payload_decode_piece(tokens[i]);
    }

    return num_tokens;*/
}

int payload_encode_piece(char *payload, int payload_size, Piece *piece) {
    /*snprintf(payload, payload_size, 
            "ID=%d SWEATER_ID=%d PIECE_TYPE_ID=%d ORIGINAL_WEIGHT=%d CURRENT_WEIGHT=%d CONTINUOUS=%d", 
            piece->id, 
            piece->sweater_id, 
            piece->piece_type_id, 
            piece->original_weight, 
            piece->current_weight, 
            piece->continuous 
            );

    return strlen(payload);*/
}

Piece payload_decode_piece(char *payload) {
    /*Piece piece;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char *token[TOKEN_PAIR];
        str_split(tokens[i], "=", token, TOKEN_PAIR);
        char *field = token[0];
        char *value = token[1];
        if (strcmp(field, "ID") == 0) {
            piece.id = atoi(value);
        } else if (strcmp(field, "SWEATER_ID") == 0) {
            piece.sweater_id = atoi(value);
        } else if (strcmp(field, "PIECE_TYPE_ID") == 0) {
            piece.piece_type_id = atoi(value);
        } else if (strcmp(field, "ORIGINAL_WEIGHT") == 0) {
            piece.original_weight = atoi(value);
        } else if (strcmp(field, "CURRENT_WEIGHT") == 0) {
            piece.current_weight = atoi(value);
        } else if (strcmp(field, "CONTINUOUS") == 0) {
            piece.continuous = atoi(value);
        } else {

        }
    }

    return piece;*/
}

PayloadStatus payload_encode_piece_type_rows(char payload_out[], int payload_capacity, int *payload_length_out, const PieceType piece_type_rows_in[], int piece_type_count) {
    if (payload_out == NULL || payload_length_out == NULL || payload_capacity <= 0 || piece_type_count < 0 || (piece_type_count > 0 && piece_type_rows_in == NULL)) {
        return PAYLOAD_STATUS_ERROR;
    }

    int tmp_length = 0;
    payload_out[0] = '\0';
    for (int i = 0; i < piece_type_count; i++) {
        char tmp[STR_LENGTH] = {0};
        int payload_length = 0;
        
        PayloadStatus status = payload_encode_piece_type(tmp, sizeof(tmp), &payload_length, &piece_type_rows_in[i]);
        if (status == PAYLOAD_STATUS_ERROR) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        int newline = (i > 0) ? 1 : 0;
        int required_length = tmp_length + payload_length + newline;
        if (required_length >= payload_capacity) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        if (newline) {
            strcat(payload_out, "\n");
        } 
        strcat(payload_out, tmp);
        tmp_length = required_length; 
    }
    *payload_length_out = tmp_length;
    payload_out[tmp_length] = '\0';
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_piece_type_rows(const char payload_in[], int payload_length, PieceType piece_type_rows_out[], int piece_type_capacity, int *piece_type_count_out) {
    if (payload_in == NULL || piece_type_rows_out == NULL ||
        piece_type_count_out == NULL || payload_length < 0 ||
        payload_length >= PAYLOAD_MAX_LENGTH || piece_type_capacity <= 0 ||
        piece_type_capacity > MAX_TOKENS) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (payload_length == 0) {
        *piece_type_count_out = 0;
        return PAYLOAD_STATUS_OK;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *rows[piece_type_capacity];
    int row_count = str_split(payload_copy, "\n", rows, piece_type_capacity);

    if (row_count == -1) {
        return PAYLOAD_STATUS_ERROR;
    }
   
    PieceType tmp_piece_types[piece_type_capacity];
    memset(tmp_piece_types, 0, sizeof(tmp_piece_types));

    for (int i = 0; i < row_count; i++) {
        PayloadStatus status = payload_decode_piece_type(
            rows[i],
            (int)strlen(rows[i]),
            &tmp_piece_types[i]
        );

        if (status != PAYLOAD_STATUS_OK) {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    memcpy(piece_type_rows_out, tmp_piece_types, row_count * sizeof(PieceType));
    *piece_type_count_out = row_count;

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_piece_type(char payload_out[], int payload_capacity, int *payload_length_out, const PieceType *piece_type_in) {
    if (payload_out == NULL || payload_length_out == NULL || piece_type_in == NULL || payload_capacity <= 0) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (piece_type_in->id < 0 || piece_type_in->piece_type[0] == '\0' || memchr(piece_type_in->piece_type, '\0', KEY_LENGTH) == NULL) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    int length = snprintf(payload_out, payload_capacity, 
            "ID=%d PIECE_TYPE=%s", 
            piece_type_in->id, 
            piece_type_in->piece_type
            );

    if (length < 0 || length >= payload_capacity) {
        return PAYLOAD_STATUS_ERROR;
    }

    *payload_length_out = length;
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_piece_type(const char payload_in[], int payload_length, PieceType *piece_type_out) {
    if (payload_in == NULL || piece_type_out == NULL || payload_length <= 0 || payload_length >= PAYLOAD_MAX_LENGTH) {
        return PAYLOAD_STATUS_ERROR;
    }

    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';
    
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload_copy, " ", tokens, MAX_TOKENS);

    if (num_tokens != PIECE_TYPE_FIELD_COUNT) {
        return PAYLOAD_STATUS_ERROR;
    }

    for (int i = 0; i < num_tokens; i++) {
        char *pair[TOKEN_PAIR];

        int pair_count = str_split(tokens[i], "=", pair, TOKEN_PAIR);
        if (pair_count != TOKEN_PAIR) {
            return PAYLOAD_STATUS_ERROR;
        }

        char *field = pair[0];
        char *value = pair[1];
        if (strcmp(field, "ID") == 0) {
            if (!str_to_int(value, &piece_type_out->id)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else if (strcmp(field, "PIECE_TYPE") == 0) {
             strncpy(piece_type_out->piece_type, value, KEY_LENGTH - 1);
             int length = strlen(piece_type_out->piece_type);
             piece_type_out->piece_type[length] = '\0';
        } else {

        }
    }

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_brand_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Brand brand_rows_in[], int brand_count) {
    if (payload_out == NULL || payload_length_out == NULL || payload_capacity <= 0 || brand_count < 0 || (brand_count > 0 && brand_rows_in == NULL)) {
        return PAYLOAD_STATUS_ERROR;
    }

    int tmp_length = 0;
    payload_out[0] = '\0';
    for (int i = 0; i < brand_count; i++) {
        char tmp[STR_LENGTH] = {0};
        int payload_length = 0;
        
        PayloadStatus status = payload_encode_brand(tmp, sizeof(tmp), &payload_length, &brand_rows_in[i]);
        if (status == PAYLOAD_STATUS_ERROR) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        int newline = (i > 0) ? 1 : 0;
        int required_length = tmp_length + payload_length + newline;
        if (required_length >= payload_capacity) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        if (newline) {
            strcat(payload_out, "\n");
        } 
        strcat(payload_out, tmp);
        tmp_length = required_length; 
    }
    *payload_length_out = tmp_length;
    payload_out[tmp_length] = '\0';
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_brand_rows(const char payload_in[], int payload_length, Brand brand_rows_out[], int brand_capacity, int *brand_count_out) {
    if (payload_in == NULL || brand_rows_out == NULL ||
        brand_count_out == NULL || payload_length < 0 ||
        payload_length >= PAYLOAD_MAX_LENGTH || brand_capacity <= 0 ||
        brand_capacity > MAX_TOKENS) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (payload_length == 0) {
        *brand_count_out = 0;
        return PAYLOAD_STATUS_OK;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *rows[brand_capacity];
    int row_count = str_split(payload_copy, "\n", rows, brand_capacity);

    if (row_count == -1) {
        return PAYLOAD_STATUS_ERROR;
    }
   
    Brand tmp_brands[brand_capacity];
    memset(tmp_brands, 0, sizeof(tmp_brands));

    for (int i = 0; i < row_count; i++) {
        PayloadStatus status = payload_decode_brand(
            rows[i],
            (int)strlen(rows[i]),
            &tmp_brands[i]
        );

        if (status != PAYLOAD_STATUS_OK) {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    memcpy(brand_rows_out, tmp_brands, row_count * sizeof(Brand));
    *brand_count_out = row_count;

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_brand(char payload_out[], int payload_capacity, int *payload_length_out, const Brand *brand_in) {
    if (payload_out == NULL || payload_length_out == NULL || brand_in == NULL || payload_capacity <= 0) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (brand_in->id < 0 || brand_in->brand[0] == '\0' || memchr(brand_in->brand, '\0', KEY_LENGTH) == NULL) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    int length = snprintf(payload_out, payload_capacity, 
            "ID=%d BRAND=%s", 
            brand_in->id, 
            brand_in->brand
            );

    if (length < 0 || length >= payload_capacity) {
        return PAYLOAD_STATUS_ERROR;
    }

    *payload_length_out = length;
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_brand(const char payload_in[], int payload_length, Brand *brand_out) {
    if (payload_in == NULL || brand_out == NULL || payload_length <= 0 || payload_length >= PAYLOAD_MAX_LENGTH) {
        return PAYLOAD_STATUS_ERROR;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload_copy, " ", tokens, MAX_TOKENS);

    if (num_tokens != BRAND_FIELD_COUNT) {
        return PAYLOAD_STATUS_ERROR;
    }

    for (int i = 0; i < num_tokens; i++) {
        char *pair[TOKEN_PAIR];

        int pair_count = str_split(tokens[i], "=", pair, TOKEN_PAIR);
        if (pair_count != TOKEN_PAIR) {
            return PAYLOAD_STATUS_ERROR;
        }

        char *field = pair[0];
        char *value = pair[1];
        if (strcmp(field, "ID") == 0) {
            if (!str_to_int(value, &brand_out->id)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else if (strcmp(field, "BRAND") == 0) {
             strncpy(brand_out->brand, value, KEY_LENGTH - 1);
             int length = strlen(brand_out->brand);
             brand_out->brand[length] = '\0';
        } else {

        }
    }

    return PAYLOAD_STATUS_OK;
}
// COLOR FAMILY SECTION START
PayloadStatus payload_encode_color_family_rows(char payload_out[], int payload_capacity, int *payload_length_out, const ColorFamily color_family_rows_in[], int color_family_count) {
    if (payload_out == NULL || payload_length_out == NULL || payload_capacity <= 0 || color_family_count < 0 || (color_family_count > 0 && color_family_rows_in == NULL)) {
        return PAYLOAD_STATUS_ERROR;
    }

    int tmp_length = 0;
    payload_out[0] = '\0';
    for (int i = 0; i < color_family_count; i++) {
        char tmp[STR_LENGTH] = {0};
        int payload_length = 0;
        
        PayloadStatus status = payload_encode_color_family(tmp, sizeof(tmp), &payload_length, &color_family_rows_in[i]);
        if (status == PAYLOAD_STATUS_ERROR) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        int newline = (i > 0) ? 1 : 0;
        int required_length = tmp_length + payload_length + newline;
        if (required_length >= payload_capacity) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        if (newline) {
            strcat(payload_out, "\n");
        } 
        strcat(payload_out, tmp);
        tmp_length = required_length; 
    }
    *payload_length_out = tmp_length;
    payload_out[tmp_length] = '\0';
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_color_family_rows(const char payload_in[], int payload_length, ColorFamily color_family_rows_out[], int color_family_capacity, int *color_family_count_out) {
    if (payload_in == NULL || color_family_rows_out == NULL ||
        color_family_count_out == NULL || payload_length < 0 ||
        payload_length >= PAYLOAD_MAX_LENGTH || color_family_capacity <= 0 ||
        color_family_capacity > MAX_TOKENS) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (payload_length == 0) {
        *color_family_count_out = 0;
        return PAYLOAD_STATUS_OK;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *rows[color_family_capacity];
    int row_count = str_split(payload_copy, "\n", rows, color_family_capacity);

    if (row_count == -1) {
        return PAYLOAD_STATUS_ERROR;
    }
   
    ColorFamily tmp_color_familys[color_family_capacity];
    memset(tmp_color_familys, 0, sizeof(tmp_color_familys));

    for (int i = 0; i < row_count; i++) {
        PayloadStatus status = payload_decode_color_family(
            rows[i],
            (int)strlen(rows[i]),
            &tmp_color_familys[i]
        );

        if (status != PAYLOAD_STATUS_OK) {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    memcpy(color_family_rows_out, tmp_color_familys, row_count * sizeof(ColorFamily));
    *color_family_count_out = row_count;

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_color_family(char payload_out[], int payload_capacity, int *payload_length_out, const ColorFamily *color_family_in) {
    if (payload_out == NULL || payload_length_out == NULL || color_family_in == NULL || payload_capacity <= 0) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (color_family_in->id < 0 || color_family_in->color_family[0] == '\0' || memchr(color_family_in->color_family, '\0', KEY_LENGTH) == NULL) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    int length = snprintf(payload_out, payload_capacity, 
            "ID=%d COLOR_FAMILY=%s", 
            color_family_in->id, 
            color_family_in->color_family
            );

    if (length < 0 || length >= payload_capacity) {
        return PAYLOAD_STATUS_ERROR;
    }

    *payload_length_out = length;
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_color_family(const char payload_in[], int payload_length, ColorFamily *color_family_out) {
    if (payload_in == NULL || color_family_out == NULL || payload_length <= 0 || payload_length >= PAYLOAD_MAX_LENGTH) {
        return PAYLOAD_STATUS_ERROR;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload_copy, " ", tokens, MAX_TOKENS);

    if (num_tokens != COLOR_FAMILY_FIELD_COUNT) {
        return PAYLOAD_STATUS_ERROR;
    }

    for (int i = 0; i < num_tokens; i++) {
        char *pair[TOKEN_PAIR];

        int pair_count = str_split(tokens[i], "=", pair, TOKEN_PAIR);
        if (pair_count != TOKEN_PAIR) {
            return PAYLOAD_STATUS_ERROR;
        }

        char *field = pair[0];
        char *value = pair[1];
        if (strcmp(field, "ID") == 0) {
            if (!str_to_int(value, &color_family_out->id)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else if (strcmp(field, "COLOR_FAMILY") == 0) {
             strncpy(color_family_out->color_family, value, KEY_LENGTH - 1);
             int length = strlen(color_family_out->color_family);
             color_family_out->color_family[length] = '\0';
        } else {

        }
    }

    return PAYLOAD_STATUS_OK;
}
// COLOR FAMILY SECTION END

PayloadStatus payload_encode_color_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Color color_rows_in[], int color_count) {
    if (payload_out == NULL || payload_length_out == NULL || payload_capacity <= 0 || color_count < 0 || (color_count > 0 && color_rows_in == NULL)) {
        return PAYLOAD_STATUS_ERROR;
    }

    int tmp_length = 0;
    payload_out[0] = '\0';
    for (int i = 0; i < color_count; i++) {
        char tmp[STR_LENGTH] = {0};
        int payload_length = 0;
        
        PayloadStatus status = payload_encode_color(tmp, sizeof(tmp), &payload_length, &color_rows_in[i]);
        if (status == PAYLOAD_STATUS_ERROR) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        int newline = (i > 0) ? 1 : 0;
        int required_length = tmp_length + payload_length + newline;
        if (required_length >= payload_capacity) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        if (newline) {
            strcat(payload_out, "\n");
        } 
        strcat(payload_out, tmp);
        tmp_length = required_length; 
    }
    *payload_length_out = tmp_length;
    payload_out[tmp_length] = '\0';
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_color_rows(const char payload_in[], int payload_length, Color color_rows_out[], int color_capacity, int *color_count_out) {
    if (payload_in == NULL || color_rows_out == NULL ||
        color_count_out == NULL || payload_length < 0 ||
        payload_length >= PAYLOAD_MAX_LENGTH || color_capacity <= 0 ||
        color_capacity > MAX_TOKENS) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (payload_length == 0) {
        *color_count_out = 0;
        return PAYLOAD_STATUS_OK;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *rows[color_capacity];
    int row_count = str_split(payload_copy, "\n", rows, color_capacity);

    if (row_count == -1) {
        return PAYLOAD_STATUS_ERROR;
    }
   
    Color tmp_colors[color_capacity];
    memset(tmp_colors, 0, sizeof(tmp_colors));

    for (int i = 0; i < row_count; i++) {
        PayloadStatus status = payload_decode_color(
            rows[i],
            (int)strlen(rows[i]),
            &tmp_colors[i]
        );

        if (status != PAYLOAD_STATUS_OK) {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    memcpy(color_rows_out, tmp_colors, row_count * sizeof(Color));
    *color_count_out = row_count;

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_color(char payload_out[], int payload_capacity, int *payload_length_out, const Color *color_in) {
    if (payload_out == NULL || payload_length_out == NULL || color_in == NULL || payload_capacity <= 0) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (color_in->id < 0 || color_in->color[0] == '\0' || memchr(color_in->color, '\0', KEY_LENGTH) == NULL) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    int length = snprintf(payload_out, payload_capacity, 
            "ID=%d COLOR=%s", 
            color_in->id, 
            color_in->color
            );

    if (length < 0 || length >= payload_capacity) {
        return PAYLOAD_STATUS_ERROR;
    }

    *payload_length_out = length;
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_color(const char payload_in[], int payload_length, Color *color_out) {
    if (payload_in == NULL || color_out == NULL || payload_length <= 0 || payload_length >= PAYLOAD_MAX_LENGTH) {
        return PAYLOAD_STATUS_ERROR;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload_copy, " ", tokens, MAX_TOKENS);

    if (num_tokens != COLOR_FIELD_COUNT) {
        return PAYLOAD_STATUS_ERROR;
    }

    for (int i = 0; i < num_tokens; i++) {
        char *pair[TOKEN_PAIR];

        int pair_count = str_split(tokens[i], "=", pair, TOKEN_PAIR);
        if (pair_count != TOKEN_PAIR) {
            return PAYLOAD_STATUS_ERROR;
        }

        char *field = pair[0];
        char *value = pair[1];
        if (strcmp(field, "ID") == 0) {
            if (!str_to_int(value, &color_out->id)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else if (strcmp(field, "COLOR") == 0) {
             strncpy(color_out->color, value, KEY_LENGTH - 1);
             int length = strlen(color_out->color);
             color_out->color[length] = '\0';
        } else {

        }
    }

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_neckline_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Neckline neckline_rows_in[], int neckline_count) {
    if (payload_out == NULL || payload_length_out == NULL || payload_capacity <= 0 || neckline_count < 0 || (neckline_count > 0 && neckline_rows_in == NULL)) {
        return PAYLOAD_STATUS_ERROR;
    }

    int tmp_length = 0;
    payload_out[0] = '\0';
    for (int i = 0; i < neckline_count; i++) {
        char tmp[STR_LENGTH] = {0};
        int payload_length = 0;
        
        PayloadStatus status = payload_encode_neckline(tmp, sizeof(tmp), &payload_length, &neckline_rows_in[i]);
        if (status == PAYLOAD_STATUS_ERROR) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        int newline = (i > 0) ? 1 : 0;
        int required_length = tmp_length + payload_length + newline;
        if (required_length >= payload_capacity) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        if (newline) {
            strcat(payload_out, "\n");
        } 
        strcat(payload_out, tmp);
        tmp_length = required_length; 
    }
    *payload_length_out = tmp_length;
    payload_out[tmp_length] = '\0';
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_neckline_rows(const char payload_in[], int payload_length, Neckline neckline_rows_out[], int neckline_capacity, int *neckline_count_out) {
    if (payload_in == NULL || neckline_rows_out == NULL ||
        neckline_count_out == NULL || payload_length < 0 ||
        payload_length >= PAYLOAD_MAX_LENGTH || neckline_capacity <= 0 ||
        neckline_capacity > MAX_TOKENS) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (payload_length == 0) {
        *neckline_count_out = 0;
        return PAYLOAD_STATUS_OK;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *rows[neckline_capacity];
    int row_count = str_split(payload_copy, "\n", rows, neckline_capacity);

    if (row_count == -1) {
        return PAYLOAD_STATUS_ERROR;
    }
   
    Neckline tmp_necklines[neckline_capacity];
    memset(tmp_necklines, 0, sizeof(tmp_necklines));

    for (int i = 0; i < row_count; i++) {
        PayloadStatus status = payload_decode_neckline(
            rows[i],
            (int)strlen(rows[i]),
            &tmp_necklines[i]
        );

        if (status != PAYLOAD_STATUS_OK) {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    memcpy(neckline_rows_out, tmp_necklines, row_count * sizeof(Neckline));
    *neckline_count_out = row_count;

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_neckline(char payload_out[], int payload_capacity, int *payload_length_out, const Neckline *neckline_in) {
    if (payload_out == NULL || payload_length_out == NULL || neckline_in == NULL || payload_capacity <= 0) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (neckline_in->id < 0 || neckline_in->neckline[0] == '\0' || memchr(neckline_in->neckline, '\0', KEY_LENGTH) == NULL) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    int length = snprintf(payload_out, payload_capacity, 
            "ID=%d NECKLINE=%s", 
            neckline_in->id, 
            neckline_in->neckline
            );

    if (length < 0 || length >= payload_capacity) {
        return PAYLOAD_STATUS_ERROR;
    }

    *payload_length_out = length;
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_neckline(const char payload_in[], int payload_length, Neckline *neckline_out) {
    if (payload_in == NULL || neckline_out == NULL || payload_length <= 0 || payload_length >= PAYLOAD_MAX_LENGTH) {
        return PAYLOAD_STATUS_ERROR;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload_copy, " ", tokens, MAX_TOKENS);

    if (num_tokens != NECKLINE_FIELD_COUNT) {
        return PAYLOAD_STATUS_ERROR;
    }

    for (int i = 0; i < num_tokens; i++) {
        char *pair[TOKEN_PAIR];

        int pair_count = str_split(tokens[i], "=", pair, TOKEN_PAIR);
        if (pair_count != TOKEN_PAIR) {
            return PAYLOAD_STATUS_ERROR;
        }

        char *field = pair[0];
        char *value = pair[1];
        if (strcmp(field, "ID") == 0) {
            if (!str_to_int(value, &neckline_out->id)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else if (strcmp(field, "NECKLINE") == 0) {
             strncpy(neckline_out->neckline, value, KEY_LENGTH - 1);
             int length = strlen(neckline_out->neckline);
             neckline_out->neckline[length] = '\0';
        } else {

        }
    }

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_sleeves_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Sleeves sleeves_rows_in[], int sleeves_count) {
    if (payload_out == NULL || payload_length_out == NULL || payload_capacity <= 0 || sleeves_count < 0 || (sleeves_count > 0 && sleeves_rows_in == NULL)) {
        return PAYLOAD_STATUS_ERROR;
    }

    int tmp_length = 0;
    payload_out[0] = '\0';
    for (int i = 0; i < sleeves_count; i++) {
        char tmp[STR_LENGTH] = {0};
        int payload_length = 0;
        
        PayloadStatus status = payload_encode_sleeves(tmp, sizeof(tmp), &payload_length, &sleeves_rows_in[i]);
        if (status == PAYLOAD_STATUS_ERROR) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        int newline = (i > 0) ? 1 : 0;
        int required_length = tmp_length + payload_length + newline;
        if (required_length >= payload_capacity) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        if (newline) {
            strcat(payload_out, "\n");
        } 
        strcat(payload_out, tmp);
        tmp_length = required_length; 
    }
    *payload_length_out = tmp_length;
    payload_out[tmp_length] = '\0';
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_sleeves_rows(const char payload_in[], int payload_length, Sleeves sleeves_rows_out[], int sleeves_capacity, int *sleeves_count_out) {
    if (payload_in == NULL || sleeves_rows_out == NULL ||
        sleeves_count_out == NULL || payload_length < 0 ||
        payload_length >= PAYLOAD_MAX_LENGTH || sleeves_capacity <= 0 ||
        sleeves_capacity > MAX_TOKENS) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (payload_length == 0) {
        *sleeves_count_out = 0;
        return PAYLOAD_STATUS_OK;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *rows[sleeves_capacity];
    int row_count = str_split(payload_copy, "\n", rows, sleeves_capacity);

    if (row_count == -1) {
        return PAYLOAD_STATUS_ERROR;
    }
   
    Sleeves tmp_sleeves[sleeves_capacity];
    memset(tmp_sleeves, 0, sizeof(tmp_sleeves));

    for (int i = 0; i < row_count; i++) {
        PayloadStatus status = payload_decode_sleeves(
            rows[i],
            (int)strlen(rows[i]),
            &tmp_sleeves[i]
        );

        if (status != PAYLOAD_STATUS_OK) {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    memcpy(sleeves_rows_out, tmp_sleeves, row_count * sizeof(Sleeves));
    *sleeves_count_out = row_count;

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_sleeves(char payload_out[], int payload_capacity, int *payload_length_out, const Sleeves *sleeves_in) {
    if (payload_out == NULL || payload_length_out == NULL || sleeves_in == NULL || payload_capacity <= 0) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (sleeves_in->id < 0 || sleeves_in->sleeves[0] == '\0' || memchr(sleeves_in->sleeves, '\0', KEY_LENGTH) == NULL) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    int length = snprintf(payload_out, payload_capacity, 
            "ID=%d SLEEVES=%s", 
            sleeves_in->id, 
            sleeves_in->sleeves
            );

    if (length < 0 || length >= payload_capacity) {
        return PAYLOAD_STATUS_ERROR;
    }

    *payload_length_out = length;
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_sleeves(const char payload_in[], int payload_length, Sleeves *sleeves_out) {
    if (payload_in == NULL || sleeves_out == NULL || payload_length <= 0 || payload_length >= PAYLOAD_MAX_LENGTH) {
        return PAYLOAD_STATUS_ERROR;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload_copy, " ", tokens, MAX_TOKENS);

    if (num_tokens != SLEEVES_FIELD_COUNT) {
        return PAYLOAD_STATUS_ERROR;
    }

    for (int i = 0; i < num_tokens; i++) {
        char *pair[TOKEN_PAIR];

        int pair_count = str_split(tokens[i], "=", pair, TOKEN_PAIR);
        if (pair_count != TOKEN_PAIR) {
            return PAYLOAD_STATUS_ERROR;
        }

        char *field = pair[0];
        char *value = pair[1];
        if (strcmp(field, "ID") == 0) {
            if (!str_to_int(value, &sleeves_out->id)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else if (strcmp(field, "SLEEVES") == 0) {
             strncpy(sleeves_out->sleeves, value, KEY_LENGTH - 1);
             int length = strlen(sleeves_out->sleeves);
             sleeves_out->sleeves[length] = '\0';
        } else {

        }
    }

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_type_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Type type_rows_in[], int type_count) {
    if (payload_out == NULL || payload_length_out == NULL || payload_capacity <= 0 || type_count < 0 || (type_count > 0 && type_rows_in == NULL)) {
        return PAYLOAD_STATUS_ERROR;
    }

    int tmp_length = 0;
    payload_out[0] = '\0';
    for (int i = 0; i < type_count; i++) {
        char tmp[STR_LENGTH] = {0};
        int payload_length = 0;
        
        PayloadStatus status = payload_encode_type(tmp, sizeof(tmp), &payload_length, &type_rows_in[i]);
        if (status == PAYLOAD_STATUS_ERROR) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        int newline = (i > 0) ? 1 : 0;
        int required_length = tmp_length + payload_length + newline;
        if (required_length >= payload_capacity) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        if (newline) {
            strcat(payload_out, "\n");
        } 
        strcat(payload_out, tmp);
        tmp_length = required_length; 
    }
    *payload_length_out = tmp_length;
    payload_out[tmp_length] = '\0';
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_type_rows(const char payload_in[], int payload_length, Type type_rows_out[], int type_capacity, int *type_count_out) {
    if (payload_in == NULL || type_rows_out == NULL ||
        type_count_out == NULL || payload_length < 0 ||
        payload_length >= PAYLOAD_MAX_LENGTH || type_capacity <= 0 ||
        type_capacity > MAX_TOKENS) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (payload_length == 0) {
        *type_count_out = 0;
        return PAYLOAD_STATUS_OK;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *rows[type_capacity];
    int row_count = str_split(payload_copy, "\n", rows, type_capacity);

    if (row_count == -1) {
        return PAYLOAD_STATUS_ERROR;
    }
   
    Type tmp_types[type_capacity];
    memset(tmp_types, 0, sizeof(tmp_types));

    for (int i = 0; i < row_count; i++) {
        PayloadStatus status = payload_decode_type(
            rows[i],
            (int)strlen(rows[i]),
            &tmp_types[i]
        );

        if (status != PAYLOAD_STATUS_OK) {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    memcpy(type_rows_out, tmp_types, row_count * sizeof(Type));
    *type_count_out = row_count;

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_type(char payload_out[], int payload_capacity, int *payload_length_out, const Type *type_in) {
    if (payload_out == NULL || payload_length_out == NULL || type_in == NULL || payload_capacity <= 0) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (type_in->id < 0 || type_in->type[0] == '\0' || memchr(type_in->type, '\0', KEY_LENGTH) == NULL) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    int length = snprintf(payload_out, payload_capacity, 
            "ID=%d TYPE=%s", 
            type_in->id, 
            type_in->type
            );

    if (length < 0 || length >= payload_capacity) {
        return PAYLOAD_STATUS_ERROR;
    }

    *payload_length_out = length;
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_type(const char payload_in[], int payload_length, Type *type_out) {
    if (payload_in == NULL || type_out == NULL || payload_length <= 0 || payload_length >= PAYLOAD_MAX_LENGTH) {
        return PAYLOAD_STATUS_ERROR;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload_copy, " ", tokens, MAX_TOKENS);

    if (num_tokens != TYPE_FIELD_COUNT) {
        return PAYLOAD_STATUS_ERROR;
    }

    for (int i = 0; i < num_tokens; i++) {
        char *pair[TOKEN_PAIR];

        int pair_count = str_split(tokens[i], "=", pair, TOKEN_PAIR);
        if (pair_count != TOKEN_PAIR) {
            return PAYLOAD_STATUS_ERROR;
        }

        char *field = pair[0];
        char *value = pair[1];
        if (strcmp(field, "ID") == 0) {
            if (!str_to_int(value, &type_out->id)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else if (strcmp(field, "TYPE") == 0) {
             strncpy(type_out->type, value, KEY_LENGTH - 1);
             int length = strlen(type_out->type);
             type_out->type[length] = '\0';
        } else {

        }
    }

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_condition_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Condition condition_rows_in[], int condition_count) {
    if (payload_out == NULL || payload_length_out == NULL || payload_capacity <= 0 || condition_count < 0 || (condition_count > 0 && condition_rows_in == NULL)) {
        return PAYLOAD_STATUS_ERROR;
    }

    int tmp_length = 0;
    payload_out[0] = '\0';
    for (int i = 0; i < condition_count; i++) {
        char tmp[STR_LENGTH] = {0};
        int payload_length = 0;
        
        PayloadStatus status = payload_encode_condition(tmp, sizeof(tmp), &payload_length, &condition_rows_in[i]);
        if (status == PAYLOAD_STATUS_ERROR) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        int newline = (i > 0) ? 1 : 0;
        int required_length = tmp_length + payload_length + newline;
        if (required_length >= payload_capacity) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        if (newline) {
            strcat(payload_out, "\n");
        } 
        strcat(payload_out, tmp);
        tmp_length = required_length; 
    }
    *payload_length_out = tmp_length;
    payload_out[tmp_length] = '\0';
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_condition_rows(const char payload_in[], int payload_length, Condition condition_rows_out[], int condition_capacity, int *condition_count_out) {
    if (payload_in == NULL || condition_rows_out == NULL ||
        condition_count_out == NULL || payload_length < 0 ||
        payload_length >= PAYLOAD_MAX_LENGTH || condition_capacity <= 0 ||
        condition_capacity > MAX_TOKENS) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (payload_length == 0) {
        *condition_count_out = 0;
        return PAYLOAD_STATUS_OK;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *rows[condition_capacity];
    int row_count = str_split(payload_copy, "\n", rows, condition_capacity);

    if (row_count == -1) {
        return PAYLOAD_STATUS_ERROR;
    }
   
    Condition tmp_conditions[condition_capacity];
    memset(tmp_conditions, 0, sizeof(tmp_conditions));

    for (int i = 0; i < row_count; i++) {
        PayloadStatus status = payload_decode_condition(
            rows[i],
            (int)strlen(rows[i]),
            &tmp_conditions[i]
        );

        if (status != PAYLOAD_STATUS_OK) {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    memcpy(condition_rows_out, tmp_conditions, row_count * sizeof(Condition));
    *condition_count_out = row_count;

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_condition(char payload_out[], int payload_capacity, int *payload_length_out, const Condition *condition_in) {
    if (payload_out == NULL || payload_length_out == NULL || condition_in == NULL || payload_capacity <= 0) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (condition_in->id < 0 || condition_in->condition[0] == '\0' || memchr(condition_in->condition, '\0', KEY_LENGTH) == NULL) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    int length = snprintf(payload_out, payload_capacity, 
            "ID=%d CONDITION=%s", 
            condition_in->id, 
            condition_in->condition
            );

    if (length < 0 || length >= payload_capacity) {
        return PAYLOAD_STATUS_ERROR;
    }

    *payload_length_out = length;
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_condition(const char payload_in[], int payload_length, Condition *condition_out) {
    if (payload_in == NULL || condition_out == NULL || payload_length <= 0 || payload_length >= PAYLOAD_MAX_LENGTH) {
        return PAYLOAD_STATUS_ERROR;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload_copy, " ", tokens, MAX_TOKENS);

    if (num_tokens != CONDITION_FIELD_COUNT) {
        return PAYLOAD_STATUS_ERROR;
    }

    for (int i = 0; i < num_tokens; i++) {
        char *pair[TOKEN_PAIR];

        int pair_count = str_split(tokens[i], "=", pair, TOKEN_PAIR);
        if (pair_count != TOKEN_PAIR) {
            return PAYLOAD_STATUS_ERROR;
        }

        char *field = pair[0];
        char *value = pair[1];
        if (strcmp(field, "ID") == 0) {
            if (!str_to_int(value, &condition_out->id)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else if (strcmp(field, "CONDITION") == 0) {
             strncpy(condition_out->condition, value, KEY_LENGTH - 1);
             int length = strlen(condition_out->condition);
             condition_out->condition[length] = '\0';
        } else {

        }
    }

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_size_rows(char payload_out[], int payload_capacity, int *payload_length_out, const Size size_rows_in[], int size_count) {
    if (payload_out == NULL || payload_length_out == NULL || payload_capacity <= 0 || size_count < 0 || (size_count > 0 && size_rows_in == NULL)) {
        return PAYLOAD_STATUS_ERROR;
    }

    int tmp_length = 0;
    payload_out[0] = '\0';
    for (int i = 0; i < size_count; i++) {
        char tmp[STR_LENGTH] = {0};
        int payload_length = 0;
        
        PayloadStatus status = payload_encode_size(tmp, sizeof(tmp), &payload_length, &size_rows_in[i]);
        if (status == PAYLOAD_STATUS_ERROR) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        int newline = (i > 0) ? 1 : 0;
        int required_length = tmp_length + payload_length + newline;
        if (required_length >= payload_capacity) {
            payload_out[0] = '\0';
            return PAYLOAD_STATUS_ERROR;
        }
        
        if (newline) {
            strcat(payload_out, "\n");
        } 
        strcat(payload_out, tmp);
        tmp_length = required_length; 
    }
    *payload_length_out = tmp_length;
    payload_out[tmp_length] = '\0';
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_size_rows(const char payload_in[], int payload_length, Size size_rows_out[], int size_capacity, int *size_count_out) {
    if (payload_in == NULL || size_rows_out == NULL ||
        size_count_out == NULL || payload_length < 0 ||
        payload_length >= PAYLOAD_MAX_LENGTH || size_capacity <= 0 ||
        size_capacity > MAX_TOKENS) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (payload_length == 0) {
        *size_count_out = 0;
        return PAYLOAD_STATUS_OK;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *rows[size_capacity];
    int row_count = str_split(payload_copy, "\n", rows, size_capacity);

    if (row_count == -1) {
        return PAYLOAD_STATUS_ERROR;
    }
   
    Size tmp_sizes[size_capacity];
    memset(tmp_sizes, 0, sizeof(tmp_sizes));

    for (int i = 0; i < row_count; i++) {
        PayloadStatus status = payload_decode_size(
            rows[i],
            (int)strlen(rows[i]),
            &tmp_sizes[i]
        );

        if (status != PAYLOAD_STATUS_OK) {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    memcpy(size_rows_out, tmp_sizes, row_count * sizeof(Size));
    *size_count_out = row_count;

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_size(char payload_out[], int payload_capacity, int *payload_length_out, const Size *size_in) {
    if (payload_out == NULL || payload_length_out == NULL || size_in == NULL || payload_capacity <= 0) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (size_in->id < 0 || size_in->size[0] == '\0' || memchr(size_in->size, '\0', KEY_LENGTH) == NULL) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    int length = snprintf(payload_out, payload_capacity, 
            "ID=%d SIZE=%s", 
            size_in->id, 
            size_in->size
            );

    if (length < 0 || length >= payload_capacity) {
        return PAYLOAD_STATUS_ERROR;
    }

    *payload_length_out = length;
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_size(const char payload_in[], int payload_length, Size *size_out) {
    if (payload_in == NULL || size_out == NULL || payload_length <= 0 || payload_length >= PAYLOAD_MAX_LENGTH) {
        return PAYLOAD_STATUS_ERROR;
    }
    
    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload_copy, " ", tokens, MAX_TOKENS);

    if (num_tokens != SIZE_FIELD_COUNT) {
        return PAYLOAD_STATUS_ERROR;
    }

    for (int i = 0; i < num_tokens; i++) {
        char *pair[TOKEN_PAIR];

        int pair_count = str_split(tokens[i], "=", pair, TOKEN_PAIR);
        if (pair_count != TOKEN_PAIR) {
            return PAYLOAD_STATUS_ERROR;
        }

        char *field = pair[0];
        char *value = pair[1];
        if (strcmp(field, "ID") == 0) {
            if (!str_to_int(value, &size_out->id)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else if (strcmp(field, "SIZE") == 0) {
             strncpy(size_out->size, value, KEY_LENGTH - 1);
             int length = strlen(size_out->size);
             size_out->size[length] = '\0';
        } else {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_id(char *payload_out, int payload_capacity, int *payload_length_out, const int id) {
    if (payload_out == NULL || payload_length_out == NULL ||
        payload_capacity <= 0) {
        return PAYLOAD_STATUS_ERROR;
    }

    int length = snprintf(payload_out, payload_capacity, "ID=%d", id);

    if (length < 0 || length >= payload_capacity) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    *payload_length_out = length;
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_id(const char *payload_in, int payload_length, int *id_out) {
    if (payload_in == NULL || id_out == NULL ||
        payload_length <= 0 || payload_length >= PAYLOAD_MAX_LENGTH) {
        return PAYLOAD_STATUS_ERROR;
    }

    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';
    
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload_copy, " ", tokens, MAX_TOKENS); 
    
    if (num_tokens != ID_FIELD_COUNT) {
        return PAYLOAD_STATUS_ERROR;
    }

    for (int i = 0; i < num_tokens; i++) {
        char *token[TOKEN_PAIR];
        int pair_count = str_split(tokens[i], "=", token, TOKEN_PAIR);
        
        if (pair_count != TOKEN_PAIR) {
            return PAYLOAD_STATUS_ERROR;
        }
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            if (!str_to_int(value, id_out)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_encode_pagination(char *payload_out, int payload_capacity, int *payload_length_out, const Pagination *pagination_in) {
    if (payload_out == NULL || payload_length_out == NULL ||
        pagination_in == NULL || payload_capacity <= 0) {
        return PAYLOAD_STATUS_ERROR;
    }

    if (pagination_in->limit <= 0 || pagination_in->offset < 0) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    int length = snprintf(payload_out, payload_capacity, "LIMIT=%d OFFSET=%d", pagination_in->limit, pagination_in->offset);
    
    if (length < 0 || length >= payload_capacity) {
        payload_out[0] = '\0';
        return PAYLOAD_STATUS_ERROR;
    }

    *payload_length_out = length;
    return PAYLOAD_STATUS_OK;
}

PayloadStatus payload_decode_pagination(const char *payload_in, int payload_length, Pagination *pagination_out) {
    if (payload_in == NULL || pagination_out == NULL ||
        payload_length <= 0 || payload_length >= PAYLOAD_MAX_LENGTH) {
        return PAYLOAD_STATUS_ERROR;
    }

    char payload_copy[PAYLOAD_MAX_LENGTH];
    memcpy(payload_copy, payload_in, payload_length);
    payload_copy[payload_length] = '\0';

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload_copy, " ", tokens, MAX_TOKENS);
    
    if (num_tokens != PAGINATION_FIELD_COUNT) {
        return PAYLOAD_STATUS_ERROR;
    }

    for (int i = 0; i < num_tokens; i++) {
        char *token[TOKEN_PAIR];
        int pair_count = str_split(tokens[i], "=", token, TOKEN_PAIR);
        
        if (pair_count != TOKEN_PAIR) {
            return PAYLOAD_STATUS_ERROR;
        }

        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "OFFSET") == 0) {
            if (!str_to_int(value, &pagination_out->offset)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else if (strcmp(field, "LIMIT") == 0) {
            if (!str_to_int(value, &pagination_out->limit)) {
                return PAYLOAD_STATUS_ERROR;
            }
        } else {
            return PAYLOAD_STATUS_ERROR;
        }
    }

    return PAYLOAD_STATUS_OK;
}
