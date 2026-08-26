#include "db_tables.h"

void print_sweater(const Sweater *sweater) {
    printf(
        "ID: %d\n"
        "Cashmere Code: %s\n"
        "Brand ID: %d\n"
        "Color ID: %d\n"
        "Neckline ID: %d\n"
        "Sleeves ID: %d\n"
        "Type ID: %d\n"
        "Condition ID: %d\n"
        "Size ID: %d\n"
        "Weight: %d\n",
        sweater->id,
        sweater->cashmere_code,
        sweater->brand_id,
        sweater->color_id,
        sweater->neckline_id,
        sweater->sleeves_id,
        sweater->type_id,
        sweater->condition_id,
        sweater->size_id,
        sweater->weight
    );
}

void print_note(const Note *note) {
    printf(
        "ID: %d\n"
        "Sweater ID: %d\n"
        "Content: %s\n",
        note->id,
        note->sweater_id,
        note->content
    );
}

void print_piece(const Piece *piece) {
    printf(
        "ID: %d\n"
        "Sweater ID: %d\n"
        "Piece Type ID: %d\n"
        "Original Weight: %d\n"
        "Current Weight: %d\n"
        "Continuous: %d\n",
        piece->id,
        piece->sweater_id,
        piece->piece_type_id,
        piece->original_weight,
        piece->current_weight,
        piece->continuous
    );
}

void print_piece_type(const PieceType *piece_type) {
    printf("ID: %d\nPiece Type: %s\n",
           piece_type->id, piece_type->piece_type);
}

void print_brand(const Brand *brand) {
    printf("ID: %d\nBrand: %s\n", brand->id, brand->brand);
}

void print_color_family(const ColorFamily *color_family) {
    printf("ID: %d\nColor Family: %s\n",
           color_family->id, color_family->color_family);
}

void print_color(const Color *color) {
    printf(
        "ID: %d\n"
        "Color Family ID: %d\n"
        "Color: %s\n",
        color->id,
        color->color_family_id,
        color->color
    );
}

void print_neckline(const Neckline *neckline) {
    printf("ID: %d\nNeckline: %s\n",
           neckline->id, neckline->neckline);
}

void print_sleeves(const Sleeves *sleeves) {
    printf("ID: %d\nSleeves: %s\n",
           sleeves->id, sleeves->sleeves);
}

void print_type(const Type *type) {
    printf("ID: %d\nType: %s\n", type->id, type->type);
}

void print_condition(const Condition *condition) {
    printf("ID: %d\nCondition: %s\n",
           condition->id, condition->condition);
}

void print_size(const Size *size) {
    printf("ID: %d\nSize: %s\n", size->id, size->size);
}
