#include "test_db_tables.h"

void test_all_db_tables(void) {
    // Exact valid input
    assert(table_from_string("NULL") == TABLE_NULL);
    assert(table_from_string("SWEATER") == TABLE_SWEATER);
    assert(table_from_string("NOTE") == TABLE_NOTE);
    assert(table_from_string("PIECE") == TABLE_PIECE);
    assert(table_from_string("PIECE_TYPE") == TABLE_PIECE_TYPE);
    assert(table_from_string("BRAND") == TABLE_BRAND);
    assert(table_from_string("COLOR_FAMILY") == TABLE_COLOR_FAMILY);
    assert(table_from_string("COLOR") == TABLE_COLOR);
    assert(table_from_string("NECKLINE") == TABLE_NECKLINE);
    assert(table_from_string("SLEEVES") == TABLE_SLEEVES);
    assert(table_from_string("TYPE") == TABLE_TYPE);
    assert(table_from_string("CONDITION") == TABLE_CONDITION);
    assert(table_from_string("SIZE") == TABLE_SIZE);
    
    // Invalid name
    assert(table_from_string("INVALID") == TABLE_NULL);
    
    // Wrong case
    assert(table_from_string("sweater") == TABLE_NULL);

    // Empty string
    assert(table_from_string("") == TABLE_NULL);

    // Extra whitespace
    assert(table_from_string(" SWEATER") == TABLE_NULL);
    assert(table_from_string("SWEATER ") == TABLE_NULL);

    // Partial name
    assert(table_from_string("SWEAT") == TABLE_NULL);

    printf("db_tables: PASS\n");
}
