#include "test_misc.h"

static void test_str_split_normal(void) {
    char input[] = "ID=4 BRAND=J_Crew";
    char *tokens[10];

    int count = str_split(input, " ", tokens, 10);

    assert(count == 2);
    assert(strcmp(tokens[0], "ID=4") == 0);
    assert(strcmp(tokens[1], "BRAND=J_Crew") == 0);
}

static void test_str_split_no_delimiter(void) {
    char input[] = "J_Crew";
    char *tokens[10];

    int count = str_split(input, " ", tokens, 10);

    assert(count == 1);
    assert(strcmp(tokens[0], "J_Crew") == 0);
}

static void test_str_split_multiple_tokens(void) {
    char input[] = "1,2,3,4";
    char *tokens[10];

    int count = str_split(input, ",", tokens, 10);

    assert(count == 4);
    assert(strcmp(tokens[0], "1") == 0);
    assert(strcmp(tokens[1], "2") == 0);
    assert(strcmp(tokens[2], "3") == 0);
    assert(strcmp(tokens[3], "4") == 0);
}

static void test_str_split_exactly_max_tokens(void) {
    char input[] = "1,2";
    char *tokens[2];

    int count = str_split(input, ",", tokens, 2);

    assert(count == 2);
    assert(strcmp(tokens[0], "1") == 0);
    assert(strcmp(tokens[1], "2") == 0);
}

static void test_str_split_exceeds_max_tokens(void) {
    char input[] = "1,2,3";
    char *tokens[2];

    int count = str_split(input, ",", tokens, 2);

    assert(count == -1);
}

static void test_str_split_empty_string(void) {
    char input[] = "";
    char *tokens[10];

    int count = str_split(input, " ", tokens, 10);

    assert(count == 0);
}

static void test_str_split_key_value_pairs(void) {
    char input[] = "ID=4 BRAND=J_Crew";
    char *tokens[10];

    int token_count = str_split(input, " ", tokens, 10);

    assert(token_count == 2);

    char *id_pair[2];
    int id_count = str_split(tokens[0], "=", id_pair, 2);

    assert(id_count == 2);
    assert(strcmp(id_pair[0], "ID") == 0);
    assert(strcmp(id_pair[1], "4") == 0);

    char *brand_pair[2];
    int brand_count = str_split(tokens[1], "=", brand_pair, 2);

    assert(brand_count == 2);
    assert(strcmp(brand_pair[0], "BRAND") == 0);
    assert(strcmp(brand_pair[1], "J_Crew") == 0);
}

void test_all_misc(void) {
    test_str_split_normal();
    test_str_split_no_delimiter();
    test_str_split_multiple_tokens();
    test_str_split_exactly_max_tokens();
    test_str_split_exceeds_max_tokens();
    test_str_split_empty_string();
    test_str_split_key_value_pairs();

    printf("misc: PASS\n");
}
