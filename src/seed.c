#include "seed.h"

static const Table LOOKUP_TABLES[] = {
    TABLE_PIECE_TYPE,
    TABLE_BRAND,
    TABLE_COLOR,
    TABLE_NECKLINE,
    TABLE_SLEEVES,
    TABLE_TYPE,
    TABLE_CONDITION,
    TABLE_SIZE,
};

static const int NUM_LOOKUPS = sizeof(LOOKUP_TABLES) / sizeof(LOOKUP_TABLES[0]);

static void seed_create_lookup_item(Table table, char *value) {
    switch(table) {
        case TABLE_PIECE_TYPE:
            PieceType piece_type = payload_decode_piece_type(value);
            db_create_piece_type(&piece_type);
            break;
        case TABLE_BRAND:
            Brand brand = payload_decode_brand(value);
            db_create_brand(&brand);
            break;
        case TABLE_COLOR:
            Color color = payload_decode_color(value);
            db_create_color(&color);
            break;
        case TABLE_NECKLINE:
            Neckline neckline = payload_decode_neckline(value);
            db_create_neckline(&neckline);
            break;
        case TABLE_SLEEVES:
            Sleeves sleeves = payload_decode_sleeves(value);
            db_create_sleeves(&sleeves);
            break;
        case TABLE_TYPE:
            Type type = payload_decode_type(value);
            db_create_type(&type);
            break;
        case TABLE_CONDITION:
            Condition condition = payload_decode_condition(value);
            db_create_condition(&condition);
            break;
        case TABLE_SIZE:
            Size size = payload_decode_size(value);
            db_create_size(&size);
            break;
        default:
    }
}

static const Table SWEATER_TABLES[] = {
    TABLE_SWEATER,
    TABLE_NOTE,
    TABLE_PIECE
};

static const int NUM_SWEATERS = sizeof(SWEATER_TABLES) / sizeof(SWEATER_TABLES[0]);

static void seed_create_sweater_item(Table table, char *value) {
    switch(table) {
        case TABLE_SWEATER:
            Sweater sweater = payload_decode_sweater(value);
            db_create_sweater(&sweater);
            break;
        case TABLE_NOTE:
            Note note = payload_decode_note(value);
            db_create_note(&note);
            break;
        case TABLE_PIECE:
            Piece piece =  payload_decode_piece(value);
            db_create_piece(&piece);
            break;
        default:
    }
}

int seed_load_all(void) {
    seed_load_lookups();
    seed_load_sweater();
}

int seed_load_lookups(void) {
    for (int i = 0; i < NUM_LOOKUPS; i++) {
        Table table = LOOKUP_TABLES[i];
        char filename[STR_LENGTH];
        snprintf(filename, STR_LENGTH, "../data/seeds/%s.txt", TABLE_NAMES[table]);
        char *file = read_entire_file(filename);
        char **items = str_split(file, "\n");
        int num_items = ptr_array_length(items);
        for (int j = 0; j < num_items; j++) {
            seed_create_lookup_item(table, items[j]);
        }
    }
}

int seed_load_sweater(void) {
    for (int i = 0; i < NUM_SWEATERS; i++) {
        Table table = SWEATER_TABLES[i];
        char filename[STR_LENGTH];
        snprintf(filename, STR_LENGTH, "../data/seeds/%s.txt", TABLE_NAMES[table]);
        char *file = read_entire_file(filename);
        char **items = str_split(file, "\n");
        int num_items = ptr_array_length(items);
        for (int j = 0; j < num_items; j++) {
            seed_create_sweater_item(table, items[j]);
        }
    }
}
