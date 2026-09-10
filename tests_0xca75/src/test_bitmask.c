#include "test_bitmask.h"

static void test_bitmask_is_set(void)
{
    Bitmask mask = BITMASK_BIT(2);

    assert(bitmask_is_set(mask, 2));
    assert(!bitmask_is_set(mask, 1));
    assert(!bitmask_is_set(mask, BITMASK_WIDTH));
}

static void test_bitmask_set(void)
{
    Bitmask mask = 0;

    assert(bitmask_set(&mask, 3));
    assert(bitmask_is_set(mask, 3));
}

static void test_bitmask_set_invalid(void)
{
    Bitmask mask = 0;

    assert(!bitmask_set(&mask, BITMASK_WIDTH));
    assert(mask == 0);

    assert(!bitmask_set(NULL, 1));
}

void test_all_bitmask(void) {
    test_bitmask_is_set();

    test_bitmask_set();
    test_bitmask_set_invalid();

    test_bitmask_clear();
    test_bitmask_clear_invalid();

    test_bitmask_toggle();
    test_bitmask_toggle_invalid();

    test_bitmask_try_set();
    test_bitmask_try_set_invalid();

    test_bitmask_clear_all();
    test_bitmask_count();

    test_bitmask_has_all();
    test_bitmask_has_any();
    test_bitmask_has_only();   

}

