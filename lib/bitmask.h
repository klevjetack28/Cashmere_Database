#ifndef BITMASK_H
#define BITMASK_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define BITMASK_WIDTH 32U
#define BITMASK_BIT(bit) (UINT32_C(1) << (bit))

typedef uint32_t Bitmask;

/* Individual bit operations. */
bool bitmask_is_set(Bitmask mask, unsigned int bit);
bool bitmask_set(Bitmask *mask, unsigned int bit);
bool bitmask_clear(Bitmask *mask, unsigned int bit);
bool bitmask_toggle(Bitmask *mask, unsigned int bit);

/* Sets a bit only if it is not already set. */
bool bitmask_try_set(Bitmask *mask, unsigned int bit);

/* Whole-mask operations. */
bool bitmask_clear_all(Bitmask *mask);
unsigned int bitmask_count(Bitmask mask);

/* Group comparisons. */
bool bitmask_has_all(Bitmask mask, Bitmask required);
bool bitmask_has_any(Bitmask mask, Bitmask choices);
bool bitmask_has_only(Bitmask mask, Bitmask allowed);

#endif // BITMASK_H
