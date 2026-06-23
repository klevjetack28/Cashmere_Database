#include "payload.h"

int payload_encode_sweater_filter(char *payload, int payload_size, SweaterFilter *sweater_filter) {

}

SweaterFilter payload_decode_sweater_filter(char *payload) {

}

int payload_encode_sweater_search(char *payload, SweaterSearch *sweater_search) {


}

SweaterSearch payload_decode_sweater_search(char *payload) {

}

int payload_encode_sweater_rows(char *payload, int payload_size, Sweater *sweater, int row_count) {
    payload_encode_row_count(payload, payload_size, count);
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_sweater(tmp, sizeof(tmp), sweater[i]);
        strcat(payload, tmp);
    }

    return strlen(payload);
}

int payload_decode_sweater_rows(char *payload, Sweater *sweater_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);

    for (int i = 0; i < num_tokens; i++) {
        sweater_rows[i] = payload_decode_sweater(tokens[i + 1]);
    }

    return num_tokens;
}

int payload_encode_sweater(char *payload, int payload_size, Sweater *sweater) {
    snprintf(payload, payload_size, 
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

    return strlen(payload);   
}

Sweater payload_decode_sweater(char *payload) {
    Sweater sweater;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {   
        char **token = str_split(tokens[i], "=");
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

    return sweater;
}

int payload_encode_note_search(char *payload, int payload_size, NoteSearch *note_search) {
    char sweater_filter[STR_LENGTH] = {0};
    payload_encode_sweater_filter(sweater_filter, STR_LENGTH, note_search->sweater_filter);
    
    char pagination[STR_LENGTH] = {0};
    payload_encode_pagination(pagination, STR_LENGTH, note_search->pagination);

    char sweater_ids[STR_LENGTH] = {0};
    snprintf(sweater_ids, STR_LENGTH, "SWEATER_COUNT=%d", note_search->sweater_count);
    for (int i = 0; i < note_search->sweater_count; i++) {
        char tmp[STR_LENGTH] = {0};
        snprintf(tmp, STR_LENGTH, " SWEATER_ID_%d=%d", i, note_search->sweater_ids[i]);
        strcat(sweater_ids, tmp)
    }
    
    snprintf(payload, payload_size, "SECTION=NOTE_SEARCH%s%s%s", sweater_ids, sweater_filter, pagination);
    return strlen(payload);
}

NoteSearch payload_decode_note_search(char *payload) {
    NoteSearch note_search;

    return note_search;
}

int payload_encode_note_rows(char *payload, Note *note, int row_count) {
    payload_encode_row_count(payload, payload_size, count);
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_note(tmp, sizeof(tmp), note[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);
}

int payload_decode_note_rows(char *payload, Note *note_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    
    
    for (int i = 0; i < num_tokens; i++) {
        note_rows[i] = payload_decode_note(tokens[i]);
    }

    return num_tokens;

}

int payload_encode_note(char *payload, int payload_size, Note *note) {
    snprintf(payload, payload_size, 
            "ID=%d SWEATER_ID=%d CONTENT=%s", 
            note->id, 
            note->sweater_id, 
            note->content
            );

    return strlen(payload);
}

Note payload_decode_note(char *payload) {
    Note note;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
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

    return note;
}

int payload_encode_piece_search(char *payload, int payload_size, PieceSearch *piece_search) {

}

PieceSearch payload_decode_piece_search(char *payload) {

}

int payload_encode_piece_rows(char *payload, Piece *piece, int row_count) {
    payload_encode_row_count(payload, payload_size, count);
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_piece(tmp, sizeof(tmp), piece[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);
}

int payload_decode_piece_rows(char *payload, Piece *piece_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    

    for (int i = 0; i < num_tokens; i++) {
        piece_rows[i] = payload_decode_piece(tokens[i]);
    }

    return num_tokens;

}

int payload_encode_piece(char *payload, int payload_size, Piece *piece) {
    snprintf(payload, payload_size, 
            "ID=%d SWEATER_ID=%d PIECE_TYPE_ID=%d ORIGINAL_WEIGHT=%d CURRENT_WEIGHT=%d CONTINUOUS=%d", 
            piece->id, 
            piece->sweater_id, 
            piece->piece_type_id, 
            piece->original_weight, 
            piece->current_weight, 
            piece->continuous 
            );

    return strlen(payload);
}

Piece payload_decode_piece(char *payload) {
    Piece piece;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
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

    return piece;
}

int payload_encode_piece_type_rows(char *payload, PieceType *piece_type, int row_count) {
    payload_encode_row_count(payload, payload_size, count);
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_piece_type(tmp, sizeof(tmp), piece_type[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);
}

int payload_decode_piece_type_rows(char *payload, PieceType *piece_type_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    

    for (int i = 0; i < num_tokens; i++) {
        piece_type_rows[i] = payload_decode_piece_type(tokens[i]);
    }

    return num_tokens;
}

int payload_encode_piece_type(char *payload, int payload_size, PieceType *piece_type) {
    snprintf(payload, payload_size, 
            "ID=%d PIECE_TYPE=%s", 
            piece_type->id, 
            piece_type->piece_type
            );

    return strlen(payload);
}

PieceType payload_decode_piece_type(char *payload) {
    PieceType piece_type;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            piece_type.id = atoi(value);   
        } else if (strcmp(field, "PIECE_TYPE") == 0) {
            strcpy(piece_type.piece_type, value);
        } else {

        }
    }

    return piece_type;
}

int payload_encode_brand_rows(char *payload, Brand *brand, int row_count) {
    payload_encode_row_count(payload, payload_size, count);
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_brand(tmp, sizeof(tmp), brand[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);
}

int payload_decode_brand_rows(char *payload, Brand *brand_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    

    for (int i = 0; i < num_tokens; i++) {
        brand_rows[i] = payload_decode_brand(tokens[i]);
    }

    return num_tokens;
}

int payload_encode_brand(char *payload, int payload_size, Brand *brand) {
    snprintf(payload, payload_size, 
            "ID=%d BRAND=%s", 
            brand->id, 
            brand->brand
            );

    return strlen(payload);
}

Brand payload_decode_brand(char *payload) {
    Brand brand;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
             brand.id = atoi(value);           
        } else if (strcmp(field, "BRAND") == 0) {
             strcpy(brand.brand, value);
        } else {

        }
    }

    return brand;
}

int payload_encode_color_family_rows(char *payload, ColorFamily *color_family, int row_count) {
    payload_encode_row_count(payload, payload_size, count);
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_color_family(tmp, sizeof(tmp), color_family[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);
}

int payload_decode_color_family_rows(char *payload, ColorFamily *color_family_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    
    
    for (int i = 0; i < num_tokens; i++) {
        color_family_rows[i] = payload_decode_color_family(tokens[i + 1]);
    }

    return num_tokens;
}

int payload_encode_color_family(char *payload, int payload_size, ColorFamily *color_family) {
    snprintf(payload, payload_size, 
            "ID=%d COLOR_FAMILY=%s", 
            color_family->id, 
            color_family->color_family
            );

    return strlen(payload);
}

ColorFamily payload_decode_color_family(char *payload) {
    ColorFamily color_family;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            color_family.id = atoi(value);
        } else if (strcmp(field, "COLOR_FAMILY") == 0) {
            strcpy(color_family.color_family, value);
        } else {

        }
    }

    return color_family;
}

int payload_encode_color_rows(char *payload, Color *color, int row_count) {
    payload_encode_row_count(payload, payload_size, count);
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_color(tmp, sizeof(tmp), color[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);
}

int payload_decode_color_rows(char *payload, Color *color_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    

    for (int i = 0; i < num_tokens; i++) {
        color_rows[i] = payload_decode_color(tokens[i]);
    }

    return num_tokens;
}

int payload_encode_color(char *payload, int payload_size, Color *color) {
    snprintf(payload, payload_size, 
            "ID=%d COLOR=%s", 
            color->id, 
            color->color
            );

    return strlen(payload);
}

Color payload_decode_color(char *payload) {
    Color color;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            color.id = atoi(value);
        } else if (strcmp(field, "COLOR") == 0) {
            strcpy(color.color, value);
        } else {

        }
    }

    return color;
}

int payload_encode_neckline_rows(char *payload, Neckline *neckline, int row_count) {
    payload_encode_row_count(payload, payload_size, count);
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_neckline(tmp, sizeof(tmp), neckline[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);

}

int payload_decode_neckline_rows(char *payload, Neckline *neckline_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    
    
    for (int i = 0; i < num_tokens; i++) {
        neckline_rows[i] = payload_decode_neckline(tokens[i]);
    }

    return num_tokens;
}

int payload_encode_neckline(char *payload, int payload_size, Neckline *neckline) {
    snprintf(payload, payload_size, 
            "ID=%d NECKLINE=%s", 
            neckline->id, 
            neckline->neckline
            );

    return strlen(payload);
}

Neckline payload_decode_neckline(char *payload) {
    Neckline neckline;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            neckline.id = atoi(value);
        } else if (strcmp(field, "NECKLINE") == 0) {
            strcpy(neckline.neckline, value);
        } else {

        }
    }

    return neckline;
}

int payload_encode_sleeves_rows(char *payload, Sleeves *sleeves, int row_count) {
    payload_encode_row_count(payload, payload_size, count);
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_sleeves(tmp, sizeof(tmp), sleeves[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);
}

int payload_decode_sleeves_rows(char *payload, Sleeves *sleeves_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    

    for (int i = 0; i < num_tokens; i++) {
        sleeves_rows[i] = payload_decode_sleeves_rows(tokens[i]);
    }

    return num_tokens;
}

int payload_encode_sleeves(char *payload, int payload_size, Sleeves *sleeves) {
    snprintf(payload, payload_size, 
            "ID=%d SLEEVES=%s", 
            sleeves->id, 
            sleeves->sleeves
            );

    return strlen(payload);
}

Sleeves payload_decode_sleeves(char *payload) {
    Sleeves sleeves;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            sleeves.id = atoi(value);
        } else if (strcmp(field, "SLEEVES") == 0) {
            strcpy(sleeves.sleeves, value);
        } else {

        }
    }

    return sleeves;
}

int payload_encode_type_rows(char *payload, Type *type, int row_count) {
    
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_type(tmp, sizeof(tmp), type[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);
}

int payload_decode_type_rows(char *payload, Type *type_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    

    for (int i = 0; i < num_tokens; i++) {
        type_rows = payload_decode_type(tokens[i]);
    }

    return num_tokens;
}

int payload_encode_type(char *payload, int payload_size, Type *type) {
    snprintf(payload, payload_size, 
            "ID=%d TYPE=%s", 
            type->id, 
            type->type
            );

    return strlen(payload);
}

Type payload_decode_type(char *payload) {
    Type type;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            type.id = atoi(value);
        } else if (strcmp(field, "TYPE") == 0) {
            strcpy(type.type, value);
        } else {

        }
    }

    return type;
}

int payload_encode_condition_rows(char *payload, Condition *condition, int row_count) {
    
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_condition(tmp, sizeof(tmp), condition[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);
}

int payload_decode_condition_rows(char *payload, Condition *condition_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    
    
    for (int i = 0; i < num_tokens; i++) {
        condition_rows[i] = payload_decode_condition(tokens[i]);
    }

    return num_tokens;
}

int payload_encode_condition(char *payload, int payload_size, Condition *condition) {
    snprintf(payload, payload_size, 
            "ID=%d CONDITION=%s", 
            condition->id, 
            condition->condition
            );

    return strlen(payload);
}

Condition payload_decode_condition(char *payload) {
    Condition condition;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            condition.id = atoi(value);
        } else if (strcmp(field, "CONDITION") == 0) {
            strcpy(condition.condition, value);
        } else {

        }
    }

    return condition;
}

int payload_encode_size_rows(char *payload, Size *size, int row_count) {
    
    for (int i = 0; i < row_count; i++) {
        char tmp[STR_LENGTH] = {0};
        strcat(payload, "\n");
        payload_encode_size(tmp, sizeof(tmp), size[i + 1]);
        strcat(payload, tmp);
    }

    return strlen(payload);
}

int payload_decode_size_rows(char *payload, Size *size_rows) {
    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, "\n", tokens, MAX_TOKENS);
    
    
    for (int i = 0; i < num_tokens; i++) {
        size_rows = payload_decode_size(tokens[i]);
    }

    return num_tokens;
}

int payload_encode_size(char *payload, int payload_size, Size *size) {
    snprintf(payload, payload_size, 
            "ID=%d SIZE=%s", 
            size->id, 
            size->size
            );

    return strlen(payload);
}

Size payload_decode_size(char *payload) {
    Size size;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            size.id = atoi(value);
        } else if (strcmp(field, "SIZE") == 0) {
            strcpy(size.size, value);
        } else {
            // Handle errors
        }
    }

    return size;
}

int payload_encode_id(char *payload, int payload_size, int id) {
    snprintf(payload, payload_size, "ID=%d", id);
    return strlen(payload);
}

int payload_decode_id(char *payload) {
    int id;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS); 
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            id = atoi(value);
        } else {
            // Handle errors
        }
    }

    return id;
}

int payload_encode_pagination(char *payload, int payload_size, Pagination *pagination) {
    snprintf(payload, payload_size, "SECTION=PAGINATION LIMIT=%d OFFSET=%d", pagination.limit, pagination.offset);
    return strlen(payload);
}

Pagination payload_decode_pagination(char *payload) {
    Pagination pagination;

    char *tokens[MAX_TOKENS];
	int num_tokens = str_split(payload, " ", tokens, MAX_TOKENS);
    for (int i = 0; i < num_tokens; i++) {
        char **token = str_split(tokens[i], "=");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "OFFSET") == 0) {
            pagination.offset = atoi(value);
        } else if (strcmp(field, "LIMIT") == 0) {
            pagination.limit = atoi(value);
        } else {
            // Handle errors
        }
    }

    return pagination;
}
