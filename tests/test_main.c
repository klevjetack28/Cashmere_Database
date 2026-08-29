#include "test_db_core.h"
#include "test_db_tables.h"
#include "test_payload.h"
#include "test_packet.h"
#include "test_seed.h"
#include "test_misc.h"
#include "test_network.h"

int main(void) {
    test_all_misc();
    test_all_db_tables();
    test_all_packet();
    test_all_payload();
    test_all_db_core();
    test_all_seed();
    test_all_network();
    return 0;
}
