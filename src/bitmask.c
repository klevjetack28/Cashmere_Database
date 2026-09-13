#include "bitmask.h"

static bool bitmask_bit_is_valid(unsigned int bit)
{
    return bit < BITMASK_WIDTH;
}

bool bitmask_is_set(Bitmask mask, unsigned int bit)
{
    if (!bitmask_bit_is_valid(bit)) {
        return false;
    }

    return (mask & BITMASK_BIT(bit)) != 0;
}

bool bitmask_set(Bitmask *mask, unsigned int bit)
{
    if (mask == NULL || !bitmask_bit_is_valid(bit)) {
        return false;
    }

    *mask |= BITMASK_BIT(bit);

    return true;
}

bool bitmask_clear(Bitmask *mask, unsigned int bit)
{
    if (mask == NULL || !bitmask_bit_is_valid(bit)) {
        return false;
    }

    *mask &= ~BITMASK_BIT(bit);

    return true;
}

bool bitmask_toggle(Bitmask *mask, unsigned int bit)
{
    if (mask == NULL || !bitmask_bit_is_valid(bit)) {
        return false;
    }

    *mask ^= BITMASK_BIT(bit);

    return true;
}

bool bitmask_try_set(Bitmask *mask, unsigned int bit)
{
    if (mask == NULL || !bitmask_bit_is_valid(bit)) {
        return false;
    }

    if (bitmask_is_set(*mask, bit)) {
        return false;
    }

    bitmask_set(mask, bit);

    return true;
}

bool bitmask_clear_all(Bitmask *mask)
{
    if (mask == NULL) {
        return false;
    }

    *mask = 0;

    return true;
}

unsigned int bitmask_count(Bitmask mask)
{
    unsigned int count = 0;

    while(mask != 0) {
        mask &= mask - 1;
        count++;
    }

    return count;
}

bool bitmask_has_all(Bitmask mask, Bitmask required)
{
    return (mask & required) == required;
}

bool bitmask_has_any(Bitmask mask, Bitmask choices)
{
    return (mask & choices) != 0;
}

bool bitmask_has_only(Bitmask mask, Bitmask allowed)
{
    return (mask & ~allowed) == 0;
}
