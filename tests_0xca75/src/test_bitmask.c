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

static void test_bitmask_clear(void)
{
    Bitmask mask = BITMASK_BIT(1) | BITMASK_BIT(4);

    assert(bitmask_clear(&mask, 1));
    assert(!bitmask_is_set(mask, 1));
    assert(bitmask_is_set(mask, 4));
}

static void test_bitmask_clear_invalid(void)
{
    Bitmask mask = BITMASK_BIT(1);

    assert(!bitmask_clear(&mask, BITMASK_WIDTH));
    assert(mask == BITMASK_BIT(1));

    assert(!bitmask_clear(NULL, 1));
}

static void test_bitmask_toggle(void)
{
    Bitmask mask = 0;

    assert(bitmask_toggle(&mask, 5));
    assert(bitmask_is_set(mask, 5));

    assert(bitmask_toggle(&mask, 5));
    assert(!bitmask_is_set(mask, 5));
}

static void test_bitmask_toggle_invalid(void)
{
    Bitmask mask = 0;

    assert(!bitmask_toggle(&mask, BITMASK_WIDTH));
    assert(mask == 0);

    assert(!bitmask_toggle(NULL, 1));
}

static void test_bitmask_try_set(void)
{
    Bitmask mask = 0;

    assert(bitmask_try_set(&mask, 2));
    assert(bitmask_is_set(mask, 2));

    assert(!bitmask_try_set(&mask, 2));
    assert(bitmask_is_set(mask, 2));
}

static void test_bitmask_try_set_invalid(void)
{
    Bitmask mask = 0;

    assert(!bitmask_try_set(&mask, BITMASK_WIDTH));
    assert(mask == 0);

    assert(!bitmask_try_set(NULL, 1));
}

static void test_bitmask_clear_all(void)
{
    Bitmask mask =
        BITMASK_BIT(1) |
        BITMASK_BIT(4) |
        BITMASK_BIT(7);

    assert(bitmask_clear_all(&mask));
    assert(mask == 0);

    assert(!bitmask_clear_all(NULL));
}

static void test_bitmask_count(void)
{
    Bitmask mask =
        BITMASK_BIT(1) |
        BITMASK_BIT(4) |
        BITMASK_BIT(7);

    assert(bitmask_count(mask) == 3);
    assert(bitmask_count(0) == 0);
    assert(bitmask_count(UINT32_MAX) == BITMASK_WIDTH);
}

static void test_bitmask_has_all(void)
{
    Bitmask required =
        BITMASK_BIT(2) |
        BITMASK_BIT(4) |
        BITMASK_BIT(5);

    assert(bitmask_has_all(
        BITMASK_BIT(2) |
        BITMASK_BIT(3) |
        BITMASK_BIT(4) |
        BITMASK_BIT(5),
        required));

    assert(!bitmask_has_all(
        BITMASK_BIT(4) |
        BITMASK_BIT(5),
        required));
}

static void test_bitmask_has_any(void)
{
    Bitmask choices =
        BITMASK_BIT(2) |
        BITMASK_BIT(4) |
        BITMASK_BIT(5);

    assert(bitmask_has_any(BITMASK_BIT(4), choices));
    assert(!bitmask_has_any(BITMASK_BIT(7), choices));
}

static void test_bitmask_has_only(void)
{
    Bitmask allowed =
        BITMASK_BIT(1) |
        BITMASK_BIT(3) |
        BITMASK_BIT(5);

    assert(bitmask_has_only(
        BITMASK_BIT(1) | BITMASK_BIT(5),
        allowed));

    assert(!bitmask_has_only(
        BITMASK_BIT(1) | BITMASK_BIT(7),
        allowed));
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

    printf("bitmask: PASS\n");
}

