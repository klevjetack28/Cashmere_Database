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

static void test_all_str_split(void) {
    test_str_split_normal();
    test_str_split_no_delimiter();
    test_str_split_multiple_tokens();
    test_str_split_exactly_max_tokens();
    test_str_split_exceeds_max_tokens();
    test_str_split_empty_string();
    test_str_split_key_value_pairs();

    printf("F str_split: PASS\n");
}

static void test_str_to_int_positive(void) {
    int value = -1;

    bool result = str_to_int("123", &value);

    assert(result == true);
    assert(value == 123);
}

static void test_str_to_int_zero(void) {
    int value = -1;

    bool result = str_to_int("0", &value);

    assert(result == true);
    assert(value == 0);
}

static void test_str_to_int_negative(void) {
    int value = 0;

    bool result = str_to_int("-123", &value);

    assert(result == true);
    assert(value == -123);
}

static void test_str_to_int_positive_sign(void) {
    int value = 0;

    bool result = str_to_int("+123", &value);

    assert(result == true);
    assert(value == 123);
}

static void test_str_to_int_int_max(void) {
    char input[32];
    int value = 0;

    snprintf(input, sizeof(input), "%d", INT_MAX);
    bool result = str_to_int(input, &value);

    assert(result == true);
    assert(value == INT_MAX);
}

static void test_str_to_int_int_min(void) {
    char input[32];
    int value = 0;

    snprintf(input, sizeof(input), "%d", INT_MIN);
    bool result = str_to_int(input, &value);

    assert(result == true);
    assert(value == INT_MIN);
}

static void test_str_to_int_letters(void) {
    int value = 99;

    bool result = str_to_int("four", &value);

    assert(result == false);
    assert(value == 99);
}

static void test_str_to_int_trailing_characters(void) {
    int value = 99;

    bool result = str_to_int("123abc", &value);

    assert(result == false);
    assert(value == 99);
}

static void test_str_to_int_empty(void) {
    int value = 99;

    bool result = str_to_int("", &value);

    assert(result == false);
    assert(value == 99);
}

static void test_str_to_int_too_large(void) {
    int value = 99;

    bool result = str_to_int("999999999999999999999999999", &value);

    assert(result == false);
    assert(value == 99);
}

static void test_str_to_int_too_small(void) {
    int value = 99;

    bool result = str_to_int("-999999999999999999999999999", &value);

    assert(result == false);
    assert(value == 99);
}

static void test_str_to_int_null_string(void) {
    int value = 99;

    bool result = str_to_int(NULL, &value);

    assert(result == false);
    assert(value == 99);
}

static void test_str_to_int_null_output(void) {
    bool result = str_to_int("123", NULL);

    assert(result == false);
}

static void test_all_str_to_int(void) {
    test_str_to_int_positive();
    test_str_to_int_zero();
    test_str_to_int_negative();
    test_str_to_int_positive_sign();
    test_str_to_int_int_max();
    test_str_to_int_int_min();
    test_str_to_int_letters();
    test_str_to_int_trailing_characters();
    test_str_to_int_empty();
    test_str_to_int_too_large();
    test_str_to_int_too_small();
    test_str_to_int_null_string();
    test_str_to_int_null_output();

    printf("F str_to_int: PASS\n");
}

void test_all_misc(void) {
    test_all_str_split();
    test_all_str_to_int();

    printf("misc: PASS\n----------\n");
}
