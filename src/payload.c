#include "payload.h"

char *payload_encode_sweater(Sweater *sweater) {
     char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d\nBRAND_ID=%dCOLOR_ID=%d\nNECKLINE_ID=%d\nSLEEVES_ID=%d\nTYPE_ID=%d\nCONDITION_ID=%d\nSIZE_ID=%d\nWEIGHT=%d", 
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

char *payload_encode_note(Note *note) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d\nSWEATER_ID=%d\nCONTENT=%s", 
            note->id, 
            note->sweater_id, 
            note->content
            );

    return payload;
}

char *payload_encode_piece(Piece *piece) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d\nSWEATER_ID=%d\nPIECE_TYPE_ID=%d\nORIGINAL_WEIGHT=%d\nCURRENT_WEIGHT=%d\nCONTINUOUS=%d\nSCRAPED=%d", 
            piece->id, 
            piece->sweater_id, 
            piece->piece_type_id, 
            piece->original_weight, 
            piece->current_weight, 
            piece->continuous, 
            piece->scraped
            );

    return payload;
}

char *payload_encode_piece_type(PieceType *piece_type) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d\nPIECE_TYPE=%s", 
            piece_type->id, 
            piece_type->piece_type
            );

    return payload;
}

char *payload_encode_brand(Brand *brand) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d\nBRAND=%s", 
            brand->id, 
            brand->brand
            );

    return payload;
}

char *payload_encode_color(Color *color) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d\nCOLOR=%s", 
            color->id, 
            color->color
            );

    return payload;
}

char *payload_encode_neckline(Neckline *neckline) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d\nNECKLINE=%s", 
            neckline->id, 
            neckline->neckline
            );

    return payload;
}

char *payload_encode_sleeves(Sleeves *sleeves) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d\nSLEEVES=%s", 
            sleeves->id, 
            sleeves->sleeves
            );

    return payload;
}

char *payload_encode_type(Type *type) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d\nTYPE=%s", 
            type->id, 
            type->type
            );

    return payload;
}

char *payload_encode_condition(Condition *condition) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d\nCONDITION=%s", 
            condition->id, 
            condition->condition
            );

    return payload;
}

char *payload_encode_size(Size *size) {
    char *payload = malloc(PAYLOAD_MAX_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, PAYLOAD_MAX_LENGTH, 
            "ID=%d\nSIZE=%s", 
            size->id, 
            size->size
            );

    return payload;
}

Sweater payload_decode_sweater(char *payload) {
    Sweater sweater;

    char **tokens = str_split(payload, "\n");
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

Note payload_decode_note(char *payload) {
    Note note;

    char **tokens = str_split(payload, "\n");
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

Piece payload_decode_piece(char *payload) {
    Piece piece;

    char **tokens = str_split(payload, "\n");
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
        } else if (strcmp(field, "SCRAPED") == 0) {
            piece.scraped = atoi(value);
        } else {

        }

    }

    return piece;
}

PieceType payload_decode_piece_type(char *payload) {
    PieceType piece_type;

    char **tokens = str_split(payload, "\n");
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

Brand payload_decode_brand(char *payload) {
    Brand brand;

    char **tokens = str_split(payload, "\n");
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

Color payload_decode_color(char *payload) {
    Color color;

    char **tokens = str_split(payload, "\n");
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

Neckline payload_decode_neckline(char *payload) {
    Neckline neckline;

    char **tokens = str_split(payload, "\n");
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

Sleeves payload_decode_sleeves(char *payload) {
    Sleeves sleeves;

    char **tokens = str_split(payload, "\n");
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

Type payload_decode_type(char *payload) {
    Type type;

    char **tokens = str_split(payload, "\n");
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

Condition payload_decode_condition(char *payload) {
    Condition condition;

    char **tokens = str_split(payload, "\n");
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

Size payload_decode_size(char *payload) {
    Size size;

    char **tokens = str_split(payload, "\n");
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
