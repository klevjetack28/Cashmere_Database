#ifndef SEED_H
#define SEED_H

#include "db_tables.h"
#include "database.h"
#include "misc.h"
#include "constants.h"
#include "0xca75.h"
#include "payload.h"

int seed_load_all(void);
int seed_load_lookups(void);
int seed_load_sweater(void);

#endif // SEED_H
