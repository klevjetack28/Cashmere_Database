#include "payload.h"

char *payload_encode_sweater(Sweater *sweater) {
     char *payload = malloc(MAX_PAYLOAD_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, MAX_PAYLOAD_LENGTH, 
            "ID=%d\nBRAND_ID=%dCOLOR_ID=%d\nNECKLINE_ID=%d\nSLEEVES_ID=%d\nTYPE_ID=%d\nCONDITION_ID=%d\nSIZE_ID=%d\nWEIGHT=%d", 
            sweater.id, 
            sweater.brand_id, 
            sweater.color_id, 
            sweater.neckline_id, 
            sweater.sleeves_id, 
            sweater.type_id, 
            sweater.condition_id, 
            sweater.size_id, 
            sweater.weight
            );

    return payload;   
}

char *payload_encode_note(Note *note) {
    char *payload = malloc(MAX_PAYLOAD_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, MAX_PAYLOAD_LENGTH, 
            "ID=%d\nSWEATER_ID=%d\nCONTENT=%s", 
            note.id, 
            note.sweater_id, 
            note.content
            );

    return payload;
}

char *payload_encode_piece(Piece *piece) {
    char *payload = malloc(MAX_PAYLOAD_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, MAX_PAYLOAD_LENGTH, 
            "ID=%d\nSWEATER_ID=%d\nPIECE_TYPE_ID=%d\nORIGINAL_WEIGHT=%d\nCURRENT_WEIGHT=%d\nCONTINUOUS=%d\nSCRAPED=%d", 
            piece.id, 
            piece.sweater_id, 
            piece.piece_type_id, 
            piece.original_weight, 
            piece.current_weight, 
            piece.continuous, 
            piece.scraped
            );

    return payload;
}

char *payload_encode_piece_type(PieceType *piece_type) {
    char *payload = malloc(MAX_PAYLOAD_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, MAX_PAYLOAD_LENGTH, 
            "ID=%d\nPIECE_TYPE=%s", 
            piece_type.id, 
            piece_type.piece_type
            );

    return payload;
}

char *payload_encode_brand(Brand *brand) {
    char *payload = malloc(MAX_PAYLOAD_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, MAX_PAYLOAD_LENGTH, 
            "ID=%d\nBRAND=%s", 
            brand.id, 
            brand.brand
            );

    return payload;
}

char *payload_encode_color(Color *color) {
    char *payload = malloc(MAX_PAYLOAD_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, MAX_PAYLOAD_LENGTH, 
            "ID=%d\nCOLOR=%s", 
            color.id, 
            color.color
            );

    return payload;
}

char *payload_encode_neckline(Neckline *neckline) {
    char *payload = malloc(MAX_PAYLOAD_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, MAX_PAYLOAD_LENGTH, 
            "ID=%d\nNECKLINE=%s", 
            neckline.id, 
            neckline.neckline
            );

    return payload;
}

char *payload_encode_sleeves(Sleeves *sleeves) {
    char *payload = malloc(MAX_PAYLOAD_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, MAX_PAYLOAD_LENGTH, 
            "ID=%d\nSLEEVES=%s", 
            sleeves.id, 
            sleeves.sleeves
            );

    return payload;
}

char *payload_encode_type(Type *type) {
    char *payload = malloc(MAX_PAYLOAD_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, MAX_PAYLOAD_LENGTH, 
            "ID=%d\nTYPE=%s", 
            type.id, 
            type.type
            );

    return payload;
}

char *payload_encode_condition(Condition *condition) {
    char *payload = malloc(MAX_PAYLOAD_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, MAX_PAYLOAD_LENGTH, 
            "ID=%d\nCONDITION=%s", 
            condition.id, 
            condition.condition
            );

    return payload;
}

char *payload_encode_size(Size *size) {
    char *payload = malloc(MAX_PAYLOAD_LENGTH);

    if (payload == NULL) {
        return NULL;
    }

    snprintf(payload, MAX_PAYLOAD_LENGTH, 
            "ID=%d\nSIZE=%s", 
            size.id, 
            size.size
            );

    return payload;
}

Sweater payload_decode_sweater(char *payload) {
    Sweater sweater = malloc(sizeof(Sweater));

    if (sweater == NULL) {
        return NULL;
    }

    char **tokens = str_split(payload);
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
        char **token = str_split(tokens[i]);
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            
        }
    }

    return sweater;
}

Note payload_decode_note(char *payload) {
    Note note = malloc(sizeof(Note));

    if (note == NULL) {
        return NULL;
    }

    char **tokens = str_split(payload);
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
        char **token = str_split(tokens[i]);
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            
        }
    }

    return note;
}

Piece payload_decode_piece(char *payload) {
    Piece piece = malloc(sizeof(Piece));

    if (piece == NULL) {
        return NULL;
    }

    char **tokens = str_split(payload);
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
        char **token = str_split(tokens[i]);
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            
        }
    }

    return piece;
}

PieceType payload_decode_piece_type(char *payload) {
    PieceType piece_type = malloc(sizeof(PieceType));

    if (piece_type == NULL) {
        return NULL;
    }

    char **tokens = str_split(payload);
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
        char **token = str_split(tokens[i], '=');
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            
        } else if (strcmp(field, "PIECE_TYPE") == 0) {
    
        }
    }

    return piece_type;
}

Brand payload_decode_brand(char *payload) {
    Brand brand = malloc(sizeof(Brand));

    if (brand == NULL) {
        return NULL;
    }

    char **tokens = str_split(payload);
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
        char **token = str_split(tokens[i], '=');
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            
        } else if (strcmp(field, "BRAND") == 0) {
    
        }

    }

    return brand;
}

Color payload_decode_color(char *payload) {
    Color color = malloc(sizeof(Color));

    if (color == NULL) {
        return NULL;
    }

    char **tokens = str_split(payload);
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
        char **token = str_split(tokens[i], '=');
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            
        } else if (strcmp(field, "COLOR") == 0) {
    
        }

    }

    return color;
}

Neckline payload_decode_neckline(char *payload) {
    Neckline neckline = malloc(sizeof(Neckline));

    if (neckline == NULL) {
        return NULL;
    }

    char **tokens = str_split(payload);
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
        char **token = str_split(tokens[i], '=');
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            
        } else if (strcmp(field, "NECKLINE") == 0) {
    
        }

    }

    return neckline;
}

Sleeves payload_decode_sleeves(char *payload) {
    Sleeves sleeves = malloc(sizeof(Sleeves));

    if (sleeves == NULL) {
        return NULL;
    }

    char **tokens = str_split(payload);
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
        char **token = str_split(tokens[i], '=');
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            
        } else if (strcmp(field, "SLEEVES") == 0) {
    
        }

    }

    return sleeves;
}

Type payload_decode_type(char *payload) {
    Type type = malloc(sizeof(Type));

    if (type == NULL) {
        return NULL;
    }

    char **tokens = str_split(payload);
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
        char **token = str_split(tokens[i], '=');
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            
        } else if (strcmp(field, "TYPE") == 0) {
    
        }

    }

    return type;
}

Condition payload_decode_condition(char *payload) {
    Condition condition = malloc(sizeof(Condition));

    if (condition == NULL) {
        return NULL;
    }

    char **tokens = str_split(payload);
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
        char **token = str_split(tokens[i], '=');
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            
        } else if (strcmp(field, "CONDITION") == 0) {
    
        }

    }

    return condition;
}

Size payload_decode_size(char *payload) {
    Size size = malloc(sizeof(Size));

    if (size == NULL) {
        return NULL;
    }

    char **tokens = str_split(payload);
    size_t length = ptr_array_length(tokens);
    for (int i = 0; i < length; i++) {
        char **token = str_split(tokens[i], '=');
        char *field = token[0];
        char *value = token[1];

        if (strcmp(field, "ID") == 0) {
            
        } else if (strcmp(field, "SIZE") == 0) {
    
        }

    }

    return size;
}
