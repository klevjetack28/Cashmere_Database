#include "db_tables.h"

const char *TABLE_NAMES[NUM_TABLES] = {
    "NULL",
    "SWEATER",
    "NOTE",
    "PIECE",
    "PIECE_TYPE",
    "BRAND",
    "COLOR",
    "NECKLINE",
    "SLEEVES",
    "TYPE",
    "CONDITION",
    "SIZE",
};

Table table_from_string(const char *token_str) {
    for (int i = 0; i < NUM_TABLES; i++) {
        if (strcmp(token_str, TABLE_NAMES[i]) == 0) {
            return (Table)i;
        }
    }
    return TABLE_NULL;
}
