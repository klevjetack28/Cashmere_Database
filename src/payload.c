#include "payload.h"

char *payload_encode_sweater_filter(SweaterFilter *sweater_filter) {

}

SweaterFilter payload_decode_sweater_filter(char *payload) {

}

char *payload_encode_sweater_search(SweaterSearch *sweater_search) {

}

SweaterSearch payload_decode_sweater_search(char *payload) {

}

char *payload_encode_sweater_rows(Sweater *sweater, int count) {

}

int payload_decode_sweater_rows(char *payload, Sweater **sweater_rows) {

}

char *payload_encode_sweater(Sweater *sweater) {
     char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
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

    return payload;   
}

Sweater payload_decode_sweater(char *payload) {
    Sweater sweater;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_note_search(NoteSearch *note_search) {

}

NoteSearch payload_decode_note_search(char *payload) {

}

char *payload_encode_note_rows(Note *note, int count) {

}

int payload_decode_note_rows(char *payload, Note **note_rows) {

}

char *payload_encode_note(Note *note) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d SWEATER_ID=%d CONTENT=%s", 
            note->id, 
            note->sweater_id, 
            note->content
            );

    return payload;
}

Note payload_decode_note(char *payload) {
    Note note;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_piece_search(PieceSearch *piece_search) {

}

PieceSearch payload_decode_piece_search(char *payload) {

}

char *payload_encode_piece_rows(Piece *piece, int count) {

}

int payload_decode_piece_rows(char *payload, Piece **piece_rows) {

}

char *payload_encode_piece(Piece *piece) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d SWEATER_ID=%d PIECE_TYPE_ID=%d ORIGINAL_WEIGHT=%d CURRENT_WEIGHT=%d CONTINUOUS=%d", 
            piece->id, 
            piece->sweater_id, 
            piece->piece_type_id, 
            piece->original_weight, 
            piece->current_weight, 
            piece->continuous 
            );

    return payload;
}

Piece payload_decode_piece(char *payload) {
    Piece piece;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_piece_type_rows(PieceType *piece_type, int count) {

    // TODO
    // Need to replace size for all lookup tables
    // Need to add encode and decode for piece, note, and sweater tables.
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        char tmp[STR_LENGTH];
        snprintf(tmp, STR_LENGTH, 
            "ID=%d SIZE=%s\n", 
            size[i]->id, 
            size[i]->size
            );
        strcat(payload, tmp);
    }

    return payload;

}

int payload_decode_piece_type_rows(char *payload, PieceType **piece_type_rows) {
    char **tokens = str_split(payload, "\n");
    int length = atoi(str_split(tokens[0], " ")[1]);
    for (int i = 0; i < length; count++) {
        char **token = str_split(tokens[i], " ");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            piece_type_rows[i].id = atoi(value);
        } else if (strcmp(field, "PIECE_TYPE") == 0) {
            strcpy(piece_type_rows[i].piece_type, value);
        } else {
        
        }
    }

    return length;
}

char *payload_encode_piece_type(PieceType *piece_type) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d PIECE_TYPE=%s", 
            piece_type->id, 
            piece_type->piece_type
            );

    return payload;
}

PieceType payload_decode_piece_type(char *payload) {
    PieceType piece_type;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_brand_rows(Brand *brand, int count) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        char tmp[STR_LENGTH];
        snprintf(tmp, STR_LENGTH, 
            "ID=%d SIZE=%s\n", 
            size[i]->id, 
            size[i]->size
            );
        strcat(payload, tmp);
    }

    return payload;

}

int payload_decode_brand_rows(char *payload, Brand **brand_rows) {
    char **tokens = str_split(payload, "\n");
    int length = atoi(str_split(tokens[0], " ")[1]);
    for (int i = 0; i < length; count++) {
        char **token = str_split(tokens[i], " ");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            brand_rows[i].id = atoi(value);
        } else if (strcmp(field, "BRAND") == 0) {
            strcpy(brand_rows[i].brand, value);
        } else {
        
        }
    }

    return length;
}

char *payload_encode_brand(Brand *brand) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d BRAND=%s", 
            brand->id, 
            brand->brand
            );

    return payload;
}

Brand payload_decode_brand(char *payload) {
    Brand brand;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_color_family_rows(ColorFamily *color_family, int count) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        char tmp[STR_LENGTH];
        snprintf(tmp, STR_LENGTH, 
            "ID=%d SIZE=%s\n", 
            size[i]->id, 
            size[i]->size
            );
        strcat(payload, tmp);
    }

    return payload;

}

int payload_decode_color_family_rows(char *payload, ColorFamily **color_family_rows) {
    char **tokens = str_split(payload, "\n");
    int length = atoi(str_split(tokens[0], " ")[1]);
    for (int i = 0; i < length; count++) {
        char **token = str_split(tokens[i], " ");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            color_family_rows[i].id = atoi(value);
        } else if (strcmp(field, "COLOR_FAMILY") == 0) {
            strcpy(color_family_rows[i].color_family, value);
        } else {
        
        }
    }

    return length;
}

char *payload_encode_color_family(ColorFamily *color_family) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d COLOR_FAMILY=%s", 
            color_family->id, 
            color_family->color_family
            );

    return payload;
}

ColorFamily payload_decode_color_family(char *payload) {
    ColorFamily color_family;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_color_rows(Color *color, int count) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        char tmp[STR_LENGTH];
        snprintf(tmp, STR_LENGTH, 
            "ID=%d SIZE=%s\n", 
            size[i]->id, 
            size[i]->size
            );
        strcat(payload, tmp);
    }

    return payload;

}

int payload_decode_color_rows(char *payload, Color **color_rows) {
    char **tokens = str_split(payload, "\n");
    int length = atoi(str_split(tokens[0], " ")[1]);
    for (int i = 0; i < length; count++) {
        char **token = str_split(tokens[i], " ");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            color_rows[i].id = atoi(value);
        } else if (strcmp(field, "COLOR") == 0) {
            strcpy(color_rows[i].color, value);
        } else {
        
        }
    }

    return length;
}

char *payload_encode_color(Color *color) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d COLOR=%s", 
            color->id, 
            color->color
            );

    return payload;
}

Color payload_decode_color(char *payload) {
    Color color;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_neckline_rows(Neckline *neckline, int count) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        char tmp[STR_LENGTH];
        snprintf(tmp, STR_LENGTH, 
            "ID=%d SIZE=%s\n", 
            size[i]->id, 
            size[i]->size
            );
        strcat(payload, tmp);
    }

    return payload;

}

int payload_decode_neckline_rows(char *payload, Neckline **neckline_rows) {
    char **tokens = str_split(payload, "\n");
    int length = atoi(str_split(tokens[0], " ")[1]);
    for (int i = 0; i < length; count++) {
        char **token = str_split(tokens[i], " ");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            neckline_rows[i].id = atoi(value);
        } else if (strcmp(field, "NECKLINE") == 0) {
            strcpy(neckline_rows[i].neckline, value);
        } else {
        
        }
    }

    return length;
}

char *payload_encode_neckline(Neckline *neckline) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d NECKLINE=%s", 
            neckline->id, 
            neckline->neckline
            );

    return payload;
}

Neckline payload_decode_neckline(char *payload) {
    Neckline neckline;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_sleeves_rows(Sleeves *sleeves, int count) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        char tmp[STR_LENGTH];
        snprintf(tmp, STR_LENGTH, 
            "ID=%d SIZE=%s\n", 
            size[i]->id, 
            size[i]->size
            );
        strcat(payload, tmp);
    }

    return payload;

}

int payload_decode_sleeves_rows(char *payload, Sleeves **sleeves_rows) {
    char **tokens = str_split(payload, "\n");
    int length = atoi(str_split(tokens[0], " ")[1]);
    for (int i = 0; i < length; count++) {
        char **token = str_split(tokens[i], " ");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            sleeves_rows[i].id = atoi(value);
        } else if (strcmp(field, "SLEEVES") == 0) {
            strcpy(sleeves_rows[i].sleeves, value);
        } else {
        
        }
    }

    return length;
}

char *payload_encode_sleeves(Sleeves *sleeves) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d SLEEVES=%s", 
            sleeves->id, 
            sleeves->sleeves
            );

    return payload;
}

Sleeves payload_decode_sleeves(char *payload) {
    Sleeves sleeves;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_type_rows(Type *type, int count) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        char tmp[STR_LENGTH];
        snprintf(tmp, STR_LENGTH, 
            "ID=%d SIZE=%s\n", 
            size[i]->id, 
            size[i]->size
            );
        strcat(payload, tmp);
    }

    return payload;

}

int payload_decode_type_rows(char *payload, Type **type_rows) {
    char **tokens = str_split(payload, "\n");
    int length = atoi(str_split(tokens[0], " ")[1]);
    for (int i = 0; i < length; count++) {
        char **token = str_split(tokens[i], " ");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            type_rows[i].id = atoi(value);
        } else if (strcmp(field, "TYPE") == 0) {
            strcpy(type_rows[i].type, value);
        } else {
        
        }
    }

    return length;
}

char *payload_encode_type(Type *type) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d TYPE=%s", 
            type->id, 
            type->type
            );

    return payload;
}

Type payload_decode_type(char *payload) {
    Type type;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_condition_rows(Condition *condition, int count) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        char tmp[STR_LENGTH];
        snprintf(tmp, STR_LENGTH, 
            "ID=%d SIZE=%s\n", 
            size[i]->id, 
            size[i]->size
            );
        strcat(payload, tmp);
    }

    return payload;

}

int payload_decode_condition_rows(char *payload, Condition **condition_rows) {
    char **tokens = str_split(payload, "\n");
    int length = atoi(str_split(tokens[0], " ")[1]);
    for (int i = 0; i < length; count++) {
        char **token = str_split(tokens[i], " ");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            condition_rows[i]->id = atoi(value);
        } else if (strcmp(field, "CONDITION") == 0) {
            strcpy(condition_rows[i]->condition, value);
        } else {
        
        }
    }

    return length;
}

char *payload_encode_condition(Condition *condition) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d CONDITION=%s", 
            condition->id, 
            condition->condition
            );

    return payload;
}

Condition payload_decode_condition(char *payload) {
    Condition condition;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_size_rows(Size *size, int count) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        char tmp[STR_LENGTH];
        snprintf(tmp, STR_LENGTH, 
            "ID=%d SIZE=%s\n", 
            size[i]->id, 
            size[i]->size
            );
        strcat(payload, tmp);
    }

    return payload;
}

int payload_decode_size_rows(char *payload, Size **size_rows) {
    char **tokens = str_split(payload, "\n");
    int length = atoi(str_split(tokens[0], " ")[1]);
    for (int i = 0; i < length; count++) {
        char **token = str_split(tokens[i], " ");
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            size_rows[i].id = atoi(value);
        } else if (strcmp(field, "SIZE") == 0) {
            strcpy(size_rows[i].size, value);
        } else {
        
        }
    }

    return length;
}

char *payload_encode_size(Size *size) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d SIZE=%s", 
            size->id, 
            size->size
            );

    return payload;
}

Size payload_decode_size(char *payload) {
    Size size;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_id(int id) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, "ID=%d", id);
    return payload;
}

int payload_decode_id(char *payload) {
    int id;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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

char *payload_encode_pagination(Pagination *pagination) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, "LIMIT=%d OFFSET=%d", pagination.limit, pagination.offset);
    return payload;
}

Pagination payload_decode_pagination(char *payload) {
    Pagination pagination;

    char **tokens = str_split(payload, " ");
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
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
