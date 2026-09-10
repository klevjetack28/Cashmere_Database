#include "test_payload.h"

static void assert_piece_type_equal(const PieceType *actual, int expected_id,
                                    const char *expected_name) {
    assert(actual->id == expected_id);
    assert(strcmp(actual->piece_type, expected_name) == 0);
}

static void test_encode_piece_type_success(void) {
    PieceType piece_type = {.id = 4, .piece_type = "Sleeve_Panel"};
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_piece_type(
        payload, sizeof(payload), &payload_length, &piece_type);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 PIECE_TYPE=Sleeve_Panel") == 0);
    assert(payload_length ==
           (int)strlen("ID=4 PIECE_TYPE=Sleeve_Panel"));
}

static void test_encode_piece_type_exact_capacity(void) {
    PieceType piece_type = {.id = 4, .piece_type = "Sleeve_Panel"};
    char payload[29]; /* 28 payload characters plus null terminator. */
    int payload_length = -1;

    PayloadStatus status = payload_encode_piece_type(
        payload, sizeof(payload), &payload_length, &piece_type);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 PIECE_TYPE=Sleeve_Panel") == 0);
    assert(payload_length == 28);
}

static void test_encode_piece_type_insufficient_capacity(void) {
    PieceType piece_type = {.id = 4, .piece_type = "Sleeve_Panel"};
    char payload[28] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_piece_type(
        payload, sizeof(payload), &payload_length, &piece_type);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_piece_type_success(void) {
    const char payload[] = "ID=4 PIECE_TYPE=Sleeve_Panel";
    PieceType piece_type = {0};

    PayloadStatus status = payload_decode_piece_type(
        payload, (int)strlen(payload), &piece_type);

    assert(status == PAYLOAD_STATUS_OK);
    assert_piece_type_equal(&piece_type, 4, "Sleeve_Panel");
}

static void test_decode_piece_type_without_null_in_length(void) {
    const char payload[] = {
        'I', 'D', '=', '7', ' ',
        'P', 'I', 'E', 'C', 'E', '_', 'T', 'Y', 'P', 'E', '=',
        'T', 'r', 'i', 'm', '_', 'P', 'i', 'e', 'c', 'e', 's'
    };
    PieceType piece_type = {0};

    PayloadStatus status = payload_decode_piece_type(
        payload, sizeof(payload), &piece_type);

    assert(status == PAYLOAD_STATUS_OK);
    assert_piece_type_equal(&piece_type, 7, "Trim_Pieces");
}

static void test_decode_piece_type_invalid_id(void) {
    const char payload[] = "ID=four PIECE_TYPE=Sleeve_Panel";
    PieceType piece_type = {0};

    PayloadStatus status = payload_decode_piece_type(
        payload, (int)strlen(payload), &piece_type);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_piece_type_missing_id(void) {
    const char payload[] = "PIECE_TYPE=Sleeve_Panel";
    PieceType piece_type = {0};

    PayloadStatus status = payload_decode_piece_type(
        payload, (int)strlen(payload), &piece_type);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_piece_type_missing_piece_type(void) {
    const char payload[] = "ID=4";
    PieceType piece_type = {0};

    PayloadStatus status = payload_decode_piece_type(
        payload, (int)strlen(payload), &piece_type);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_encode_piece_type_rows_success(void) {
    PieceType piece_types[] = {
        {.id = 1, .piece_type = "Torso_Panel"},
        {.id = 2, .piece_type = "Sleeve_Panel"},
    };
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_piece_type_rows(
        payload, sizeof(payload), &payload_length, piece_types, 2);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload,
                  "ID=1 PIECE_TYPE=Torso_Panel\n"
                  "ID=2 PIECE_TYPE=Sleeve_Panel") == 0);
    assert(payload_length == (int)strlen(payload));
}

static void test_encode_piece_type_rows_insufficient_capacity(void) {
    PieceType piece_types[] = {
        {.id = 1, .piece_type = "Torso_Panel"},
        {.id = 2, .piece_type = "Sleeve_Panel"},
    };
    char payload[12] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_piece_type_rows(
        payload, sizeof(payload), &payload_length, piece_types, 2);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_piece_type_rows_success(void) {
    const char payload[] =
        "ID=1 PIECE_TYPE=Torso_Panel\n"
        "ID=2 PIECE_TYPE=Sleeve_Panel";
    PieceType piece_types[2] = {0};
    int piece_type_count = -1;

    PayloadStatus status = payload_decode_piece_type_rows(
        payload, (int)strlen(payload), piece_types, 2,
        &piece_type_count);

    assert(status == PAYLOAD_STATUS_OK);
    assert(piece_type_count == 2);
    assert_piece_type_equal(&piece_types[0], 1, "Torso_Panel");
    assert_piece_type_equal(&piece_types[1], 2, "Sleeve_Panel");
}

static void test_decode_piece_type_rows_insufficient_capacity(void) {
    const char payload[] =
        "ID=1 PIECE_TYPE=Torso_Panel\n"
        "ID=2 PIECE_TYPE=Sleeve_Panel";
    PieceType piece_types[1] = {0};
    int piece_type_count = -1;

    PayloadStatus status = payload_decode_piece_type_rows(
        payload, (int)strlen(payload), piece_types, 1,
        &piece_type_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_piece_type_rows_malformed_row(void) {
    const char payload[] =
        "ID=1 PIECE_TYPE=Torso_Panel\n"
        "ID=bad PIECE_TYPE=Sleeve_Panel";
    PieceType piece_types[2] = {0};
    int piece_type_count = -1;

    PayloadStatus status = payload_decode_piece_type_rows(
        payload, (int)strlen(payload), piece_types, 2,
        &piece_type_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_all_piece_type(void) {
    test_encode_piece_type_success();
    test_encode_piece_type_exact_capacity();
    test_encode_piece_type_insufficient_capacity();
    test_decode_piece_type_success();
    test_decode_piece_type_without_null_in_length();
    test_decode_piece_type_invalid_id();
    test_decode_piece_type_missing_id();
    test_decode_piece_type_missing_piece_type();
    test_encode_piece_type_rows_success();
    test_encode_piece_type_rows_insufficient_capacity();
    test_decode_piece_type_rows_success();
    test_decode_piece_type_rows_insufficient_capacity();
    test_decode_piece_type_rows_malformed_row();

    printf("G payload_piece_type: PASS\n");
}

static void assert_brand_equal(const Brand *actual, int expected_id,
                               const char *expected_name) {
    assert(actual->id == expected_id);
    assert(strcmp(actual->brand, expected_name) == 0);
}

static void test_encode_brand_success(void) {
    Brand brand = {.id = 4, .brand = "J_Crew"};
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_brand(
        payload, sizeof(payload), &payload_length, &brand);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 BRAND=J_Crew") == 0);
    assert(payload_length == (int)strlen("ID=4 BRAND=J_Crew"));
}

static void test_encode_brand_exact_capacity(void) {
    Brand brand = {.id = 4, .brand = "J_Crew"};
    char payload[18]; /* 17 payload characters plus the null terminator. */
    int payload_length = -1;

    PayloadStatus status = payload_encode_brand(
        payload, sizeof(payload), &payload_length, &brand);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 BRAND=J_Crew") == 0);
    assert(payload_length == 17);
}

static void test_encode_brand_insufficient_capacity(void) {
    Brand brand = {.id = 4, .brand = "J_Crew"};
    char payload[17] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_brand(
        payload, sizeof(payload), &payload_length, &brand);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_brand_success(void) {
    const char payload[] = "ID=4 BRAND=J_Crew";
    Brand brand = {0};

    PayloadStatus status = payload_decode_brand(
        payload, (int)strlen(payload), &brand);

    assert(status == PAYLOAD_STATUS_OK);
    assert_brand_equal(&brand, 4, "J_Crew");
}

static void test_decode_brand_without_null_in_length(void) {
    const char payload[] = {'I', 'D', '=', '7', ' ', 'B', 'R', 'A', 'N', 'D',
                            '=', 'T', 'a', 'l', 'b', 'o', 't', 's'};
    Brand brand = {0};

    PayloadStatus status = payload_decode_brand(
        payload, sizeof(payload), &brand);

    assert(status == PAYLOAD_STATUS_OK);
    assert_brand_equal(&brand, 7, "Talbots");
}

static void test_decode_brand_invalid_id(void) {
    const char payload[] = "ID=four BRAND=J_Crew";
    Brand brand = {0};

    PayloadStatus status = payload_decode_brand(
        payload, (int)strlen(payload), &brand);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_brand_missing_id(void) {
    const char payload[] = "BRAND=J_Crew";
    Brand brand = {0};

    PayloadStatus status = payload_decode_brand(
        payload, (int)strlen(payload), &brand);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_brand_missing_brand(void) {
    const char payload[] = "ID=4";
    Brand brand = {0};

    PayloadStatus status = payload_decode_brand(
        payload, (int)strlen(payload), &brand);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_encode_brand_rows_success(void) {
    Brand brands[] = {
        {.id = 1, .brand = "J_Crew"},
        {.id = 2, .brand = "Talbots"},
    };
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_brand_rows(
        payload, sizeof(payload), &payload_length, brands, 2);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=1 BRAND=J_Crew\nID=2 BRAND=Talbots") == 0);
    assert(payload_length == (int)strlen(payload));
}

static void test_encode_brand_rows_insufficient_capacity(void) {
    Brand brands[] = {
        {.id = 1, .brand = "J_Crew"},
        {.id = 2, .brand = "Talbots"},
    };
    char payload[12] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_brand_rows(
        payload, sizeof(payload), &payload_length, brands, 2);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_brand_rows_success(void) {
    const char payload[] = "ID=1 BRAND=J_Crew\nID=2 BRAND=Talbots";
    Brand brands[2] = {0};
    int brand_count = -1;

    PayloadStatus status = payload_decode_brand_rows(
        payload, (int)strlen(payload), brands, 2, &brand_count);

    assert(status == PAYLOAD_STATUS_OK);
    assert(brand_count == 2);
    assert_brand_equal(&brands[0], 1, "J_Crew");
    assert_brand_equal(&brands[1], 2, "Talbots");
}

static void test_decode_brand_rows_insufficient_capacity(void) {
    const char payload[] = "ID=1 BRAND=J_Crew\nID=2 BRAND=Talbots";
    Brand brands[1] = {0};
    int brand_count = -1;

    PayloadStatus status = payload_decode_brand_rows(
        payload, (int)strlen(payload), brands, 1, &brand_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_brand_rows_malformed_row(void) {
    const char payload[] = "ID=1 BRAND=J_Crew\nID=bad BRAND=Talbots";
    Brand brands[2] = {0};
    int brand_count = -1;

    PayloadStatus status = payload_decode_brand_rows(
        payload, (int)strlen(payload), brands, 2, &brand_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_all_brand(void) {
    test_encode_brand_success();
    test_encode_brand_exact_capacity();
    test_encode_brand_insufficient_capacity();
    test_decode_brand_success();
    test_decode_brand_without_null_in_length();
    test_decode_brand_invalid_id();
    test_decode_brand_missing_id();
    test_decode_brand_missing_brand();
    test_encode_brand_rows_success();
    test_encode_brand_rows_insufficient_capacity();
    test_decode_brand_rows_success();
    test_decode_brand_rows_insufficient_capacity();
    test_decode_brand_rows_malformed_row();

    printf("G payload_brand: PASS\n");
}

static void assert_color_family_equal(const ColorFamily *actual,
                                      int expected_id,
                                      const char *expected_name) {
    assert(actual->id == expected_id);
    assert(strcmp(actual->color_family, expected_name) == 0);
}

static void test_encode_color_family_success(void) {
    ColorFamily color_family = {
        .id = 4,
        .color_family = "Blue"
    };
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_color_family(
        payload, sizeof(payload), &payload_length, &color_family);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 COLOR_FAMILY=Blue") == 0);
    assert(payload_length ==
           (int)strlen("ID=4 COLOR_FAMILY=Blue"));
}

static void test_encode_color_family_exact_capacity(void) {
    ColorFamily color_family = {
        .id = 4,
        .color_family = "Blue"
    };
    char payload[23]; /* 22 payload characters plus null terminator. */
    int payload_length = -1;

    PayloadStatus status = payload_encode_color_family(
        payload, sizeof(payload), &payload_length, &color_family);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 COLOR_FAMILY=Blue") == 0);
    assert(payload_length == 22);
}

static void test_encode_color_family_insufficient_capacity(void) {
    ColorFamily color_family = {
        .id = 4,
        .color_family = "Blue"
    };
    char payload[22] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_color_family(
        payload, sizeof(payload), &payload_length, &color_family);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_color_family_success(void) {
    const char payload[] = "ID=4 COLOR_FAMILY=Blue";
    ColorFamily color_family = {0};

    PayloadStatus status = payload_decode_color_family(
        payload, (int)strlen(payload), &color_family);

    assert(status == PAYLOAD_STATUS_OK);
    assert_color_family_equal(&color_family, 4, "Blue");
}

static void test_decode_color_family_without_null_in_length(void) {
    const char payload[] = {
        'I', 'D', '=', '7', ' ',
        'C', 'O', 'L', 'O', 'R', '_', 'F', 'A', 'M', 'I', 'L', 'Y', '=',
        'M', 'u', 'l', 't', 'i', 'c', 'o', 'l', 'o', 'r'
    };
    ColorFamily color_family = {0};

    PayloadStatus status = payload_decode_color_family(
        payload, sizeof(payload), &color_family);

    assert(status == PAYLOAD_STATUS_OK);
    assert_color_family_equal(&color_family, 7, "Multicolor");
}

static void test_decode_color_family_invalid_id(void) {
    const char payload[] = "ID=four COLOR_FAMILY=Blue";
    ColorFamily color_family = {0};

    PayloadStatus status = payload_decode_color_family(
        payload, (int)strlen(payload), &color_family);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_color_family_missing_id(void) {
    const char payload[] = "COLOR_FAMILY=Blue";
    ColorFamily color_family = {0};

    PayloadStatus status = payload_decode_color_family(
        payload, (int)strlen(payload), &color_family);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_color_family_missing_color_family(void) {
    const char payload[] = "ID=4";
    ColorFamily color_family = {0};

    PayloadStatus status = payload_decode_color_family(
        payload, (int)strlen(payload), &color_family);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_encode_color_family_rows_success(void) {
    ColorFamily color_families[] = {
        {.id = 1, .color_family = "Neutral"},
        {.id = 2, .color_family = "Blue"},
    };
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_color_family_rows(
        payload, sizeof(payload), &payload_length, color_families, 2);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload,
                  "ID=1 COLOR_FAMILY=Neutral\n"
                  "ID=2 COLOR_FAMILY=Blue") == 0);
    assert(payload_length == (int)strlen(payload));
}

static void test_encode_color_family_rows_insufficient_capacity(void) {
    ColorFamily color_families[] = {
        {.id = 1, .color_family = "Neutral"},
        {.id = 2, .color_family = "Blue"},
    };
    char payload[12] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_color_family_rows(
        payload, sizeof(payload), &payload_length, color_families, 2);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_color_family_rows_success(void) {
    const char payload[] =
        "ID=1 COLOR_FAMILY=Neutral\n"
        "ID=2 COLOR_FAMILY=Blue";
    ColorFamily color_families[2] = {0};
    int color_family_count = -1;

    PayloadStatus status = payload_decode_color_family_rows(
        payload, (int)strlen(payload), color_families, 2,
        &color_family_count);

    assert(status == PAYLOAD_STATUS_OK);
    assert(color_family_count == 2);
    assert_color_family_equal(&color_families[0], 1, "Neutral");
    assert_color_family_equal(&color_families[1], 2, "Blue");
}

static void test_decode_color_family_rows_insufficient_capacity(void) {
    const char payload[] =
        "ID=1 COLOR_FAMILY=Neutral\n"
        "ID=2 COLOR_FAMILY=Blue";
    ColorFamily color_families[1] = {0};
    int color_family_count = -1;

    PayloadStatus status = payload_decode_color_family_rows(
        payload, (int)strlen(payload), color_families, 1,
        &color_family_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_color_family_rows_malformed_row(void) {
    const char payload[] =
        "ID=1 COLOR_FAMILY=Neutral\n"
        "ID=bad COLOR_FAMILY=Blue";
    ColorFamily color_families[2] = {0};
    int color_family_count = -1;

    PayloadStatus status = payload_decode_color_family_rows(
        payload, (int)strlen(payload), color_families, 2,
        &color_family_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_all_color_family(void) {
    test_encode_color_family_success();
    test_encode_color_family_exact_capacity();
    test_encode_color_family_insufficient_capacity();
    test_decode_color_family_success();
    test_decode_color_family_without_null_in_length();
    test_decode_color_family_invalid_id();
    test_decode_color_family_missing_id();
    test_decode_color_family_missing_color_family();
    test_encode_color_family_rows_success();
    test_encode_color_family_rows_insufficient_capacity();
    test_decode_color_family_rows_success();
    test_decode_color_family_rows_insufficient_capacity();
    test_decode_color_family_rows_malformed_row();

    printf("G payload_color_family: PASS\n");
}

static void assert_neckline_equal(const Neckline *actual, int expected_id,
                                  const char *expected_name) {
    assert(actual->id == expected_id);
    assert(strcmp(actual->neckline, expected_name) == 0);
}

static void test_encode_neckline_success(void) {
    Neckline neckline = {.id = 4, .neckline = "Crewneck"};
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_neckline(
        payload, sizeof(payload), &payload_length, &neckline);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 NECKLINE=Crewneck") == 0);
    assert(payload_length == (int)strlen("ID=4 NECKLINE=Crewneck"));
}

static void test_encode_neckline_exact_capacity(void) {
    Neckline neckline = {.id = 4, .neckline = "Crewneck"};
    char payload[23]; /* 22 payload characters plus null terminator. */
    int payload_length = -1;

    PayloadStatus status = payload_encode_neckline(
        payload, sizeof(payload), &payload_length, &neckline);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 NECKLINE=Crewneck") == 0);
    assert(payload_length == 22);
}

static void test_encode_neckline_insufficient_capacity(void) {
    Neckline neckline = {.id = 4, .neckline = "Crewneck"};
    char payload[22] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_neckline(
        payload, sizeof(payload), &payload_length, &neckline);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_neckline_success(void) {
    const char payload[] = "ID=4 NECKLINE=Crewneck";
    Neckline neckline = {0};

    PayloadStatus status = payload_decode_neckline(
        payload, (int)strlen(payload), &neckline);

    assert(status == PAYLOAD_STATUS_OK);
    assert_neckline_equal(&neckline, 4, "Crewneck");
}

static void test_decode_neckline_without_null_in_length(void) {
    const char payload[] = {
        'I', 'D', '=', '7', ' ',
        'N', 'E', 'C', 'K', 'L', 'I', 'N', 'E', '=',
        'V', '_', 'N', 'e', 'c', 'k'
    };
    Neckline neckline = {0};

    PayloadStatus status = payload_decode_neckline(
        payload, sizeof(payload), &neckline);

    assert(status == PAYLOAD_STATUS_OK);
    assert_neckline_equal(&neckline, 7, "V_Neck");
}

static void test_decode_neckline_invalid_id(void) {
    const char payload[] = "ID=four NECKLINE=Crewneck";
    Neckline neckline = {0};

    PayloadStatus status = payload_decode_neckline(
        payload, (int)strlen(payload), &neckline);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_neckline_missing_id(void) {
    const char payload[] = "NECKLINE=Crewneck";
    Neckline neckline = {0};

    PayloadStatus status = payload_decode_neckline(
        payload, (int)strlen(payload), &neckline);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_neckline_missing_neckline(void) {
    const char payload[] = "ID=4";
    Neckline neckline = {0};

    PayloadStatus status = payload_decode_neckline(
        payload, (int)strlen(payload), &neckline);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_encode_neckline_rows_success(void) {
    Neckline necklines[] = {
        {.id = 1, .neckline = "Crewneck"},
        {.id = 2, .neckline = "V_Neck"},
    };
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_neckline_rows(
        payload, sizeof(payload), &payload_length, necklines, 2);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload,
                  "ID=1 NECKLINE=Crewneck\n"
                  "ID=2 NECKLINE=V_Neck") == 0);
    assert(payload_length == (int)strlen(payload));
}

static void test_encode_neckline_rows_insufficient_capacity(void) {
    Neckline necklines[] = {
        {.id = 1, .neckline = "Crewneck"},
        {.id = 2, .neckline = "V_Neck"},
    };
    char payload[12] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_neckline_rows(
        payload, sizeof(payload), &payload_length, necklines, 2);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_neckline_rows_success(void) {
    const char payload[] =
        "ID=1 NECKLINE=Crewneck\n"
        "ID=2 NECKLINE=V_Neck";
    Neckline necklines[2] = {0};
    int neckline_count = -1;

    PayloadStatus status = payload_decode_neckline_rows(
        payload, (int)strlen(payload), necklines, 2, &neckline_count);

    assert(status == PAYLOAD_STATUS_OK);
    assert(neckline_count == 2);
    assert_neckline_equal(&necklines[0], 1, "Crewneck");
    assert_neckline_equal(&necklines[1], 2, "V_Neck");
}

static void test_decode_neckline_rows_insufficient_capacity(void) {
    const char payload[] =
        "ID=1 NECKLINE=Crewneck\n"
        "ID=2 NECKLINE=V_Neck";
    Neckline necklines[1] = {0};
    int neckline_count = -1;

    PayloadStatus status = payload_decode_neckline_rows(
        payload, (int)strlen(payload), necklines, 1, &neckline_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_neckline_rows_malformed_row(void) {
    const char payload[] =
        "ID=1 NECKLINE=Crewneck\n"
        "ID=bad NECKLINE=V_Neck";
    Neckline necklines[2] = {0};
    int neckline_count = -1;

    PayloadStatus status = payload_decode_neckline_rows(
        payload, (int)strlen(payload), necklines, 2, &neckline_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_all_neckline(void) {
    test_encode_neckline_success();
    test_encode_neckline_exact_capacity();
    test_encode_neckline_insufficient_capacity();
    test_decode_neckline_success();
    test_decode_neckline_without_null_in_length();
    test_decode_neckline_invalid_id();
    test_decode_neckline_missing_id();
    test_decode_neckline_missing_neckline();
    test_encode_neckline_rows_success();
    test_encode_neckline_rows_insufficient_capacity();
    test_decode_neckline_rows_success();
    test_decode_neckline_rows_insufficient_capacity();
    test_decode_neckline_rows_malformed_row();

    printf("G payload_neckline: PASS\n");
}

static void assert_sleeves_equal(const Sleeves *actual, int expected_id,
                                 const char *expected_name) {
    assert(actual->id == expected_id);
    assert(strcmp(actual->sleeves, expected_name) == 0);
}

static void test_encode_sleeves_success(void) {
    Sleeves sleeves = {.id = 4, .sleeves = "Long"};
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_sleeves(
        payload, sizeof(payload), &payload_length, &sleeves);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 SLEEVES=Long") == 0);
    assert(payload_length == (int)strlen("ID=4 SLEEVES=Long"));
}

static void test_encode_sleeves_exact_capacity(void) {
    Sleeves sleeves = {.id = 4, .sleeves = "Long"};
    char payload[18]; /* 17 payload characters plus null terminator. */
    int payload_length = -1;

    PayloadStatus status = payload_encode_sleeves(
        payload, sizeof(payload), &payload_length, &sleeves);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 SLEEVES=Long") == 0);
    assert(payload_length == 17);
}

static void test_encode_sleeves_insufficient_capacity(void) {
    Sleeves sleeves = {.id = 4, .sleeves = "Long"};
    char payload[17] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_sleeves(
        payload, sizeof(payload), &payload_length, &sleeves);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_sleeves_success(void) {
    const char payload[] = "ID=4 SLEEVES=Long";
    Sleeves sleeves = {0};

    PayloadStatus status = payload_decode_sleeves(
        payload, (int)strlen(payload), &sleeves);

    assert(status == PAYLOAD_STATUS_OK);
    assert_sleeves_equal(&sleeves, 4, "Long");
}

static void test_decode_sleeves_without_null_in_length(void) {
    const char payload[] = {
        'I', 'D', '=', '7', ' ',
        'S', 'L', 'E', 'E', 'V', 'E', 'S', '=',
        'S', 'l', 'e', 'e', 'v', 'e', 'l', 'e', 's', 's'
    };
    Sleeves sleeves = {0};

    PayloadStatus status = payload_decode_sleeves(
        payload, sizeof(payload), &sleeves);

    assert(status == PAYLOAD_STATUS_OK);
    assert_sleeves_equal(&sleeves, 7, "Sleeveless");
}

static void test_decode_sleeves_invalid_id(void) {
    const char payload[] = "ID=four SLEEVES=Long";
    Sleeves sleeves = {0};

    PayloadStatus status = payload_decode_sleeves(
        payload, (int)strlen(payload), &sleeves);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_sleeves_missing_id(void) {
    const char payload[] = "SLEEVES=Long";
    Sleeves sleeves = {0};

    PayloadStatus status = payload_decode_sleeves(
        payload, (int)strlen(payload), &sleeves);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_sleeves_missing_sleeves(void) {
    const char payload[] = "ID=4";
    Sleeves sleeves = {0};

    PayloadStatus status = payload_decode_sleeves(
        payload, (int)strlen(payload), &sleeves);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_encode_sleeves_rows_success(void) {
    Sleeves sleeves[] = {
        {.id = 1, .sleeves = "Long"},
        {.id = 2, .sleeves = "Sleeveless"},
    };
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_sleeves_rows(
        payload, sizeof(payload), &payload_length, sleeves, 2);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload,
                  "ID=1 SLEEVES=Long\n"
                  "ID=2 SLEEVES=Sleeveless") == 0);
    assert(payload_length == (int)strlen(payload));
}

static void test_encode_sleeves_rows_insufficient_capacity(void) {
    Sleeves sleeves[] = {
        {.id = 1, .sleeves = "Long"},
        {.id = 2, .sleeves = "Sleeveless"},
    };
    char payload[12] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_sleeves_rows(
        payload, sizeof(payload), &payload_length, sleeves, 2);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_sleeves_rows_success(void) {
    const char payload[] =
        "ID=1 SLEEVES=Long\n"
        "ID=2 SLEEVES=Sleeveless";
    Sleeves sleeves[2] = {0};
    int sleeve_count = -1;

    PayloadStatus status = payload_decode_sleeves_rows(
        payload, (int)strlen(payload), sleeves, 2, &sleeve_count);

    assert(status == PAYLOAD_STATUS_OK);
    assert(sleeve_count == 2);
    assert_sleeves_equal(&sleeves[0], 1, "Long");
    assert_sleeves_equal(&sleeves[1], 2, "Sleeveless");
}

static void test_decode_sleeves_rows_insufficient_capacity(void) {
    const char payload[] =
        "ID=1 SLEEVES=Long\n"
        "ID=2 SLEEVES=Sleeveless";
    Sleeves sleeves[1] = {0};
    int sleeve_count = -1;

    PayloadStatus status = payload_decode_sleeves_rows(
        payload, (int)strlen(payload), sleeves, 1, &sleeve_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_sleeves_rows_malformed_row(void) {
    const char payload[] =
        "ID=1 SLEEVES=Long\n"
        "ID=bad SLEEVES=Sleeveless";
    Sleeves sleeves[2] = {0};
    int sleeve_count = -1;

    PayloadStatus status = payload_decode_sleeves_rows(
        payload, (int)strlen(payload), sleeves, 2, &sleeve_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_all_sleeves(void) {
    test_encode_sleeves_success();
    test_encode_sleeves_exact_capacity();
    test_encode_sleeves_insufficient_capacity();
    test_decode_sleeves_success();
    test_decode_sleeves_without_null_in_length();
    test_decode_sleeves_invalid_id();
    test_decode_sleeves_missing_id();
    test_decode_sleeves_missing_sleeves();
    test_encode_sleeves_rows_success();
    test_encode_sleeves_rows_insufficient_capacity();
    test_decode_sleeves_rows_success();
    test_decode_sleeves_rows_insufficient_capacity();
    test_decode_sleeves_rows_malformed_row();

    printf("G payload_sleeves: PASS\n");
}

static void assert_type_equal(const Type *actual, int expected_id,
                              const char *expected_name) {
    assert(actual->id == expected_id);
    assert(strcmp(actual->type, expected_name) == 0);
}

static void test_encode_type_success(void) {
    Type type = {.id = 4, .type = "Cardigan"};
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_type(
        payload, sizeof(payload), &payload_length, &type);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 TYPE=Cardigan") == 0);
    assert(payload_length == (int)strlen("ID=4 TYPE=Cardigan"));
}

static void test_encode_type_exact_capacity(void) {
    Type type = {.id = 4, .type = "Cardigan"};
    char payload[19]; /* 18 payload characters plus null terminator. */
    int payload_length = -1;

    PayloadStatus status = payload_encode_type(
        payload, sizeof(payload), &payload_length, &type);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 TYPE=Cardigan") == 0);
    assert(payload_length == 18);
}

static void test_encode_type_insufficient_capacity(void) {
    Type type = {.id = 4, .type = "Cardigan"};
    char payload[18] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_type(
        payload, sizeof(payload), &payload_length, &type);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_type_success(void) {
    const char payload[] = "ID=4 TYPE=Cardigan";
    Type type = {0};

    PayloadStatus status = payload_decode_type(
        payload, (int)strlen(payload), &type);

    assert(status == PAYLOAD_STATUS_OK);
    assert_type_equal(&type, 4, "Cardigan");
}

static void test_decode_type_without_null_in_length(void) {
    const char payload[] = {
        'I', 'D', '=', '7', ' ',
        'T', 'Y', 'P', 'E', '=',
        'P', 'u', 'l', 'l', 'o', 'v', 'e', 'r'
    };
    Type type = {0};

    PayloadStatus status = payload_decode_type(
        payload, sizeof(payload), &type);

    assert(status == PAYLOAD_STATUS_OK);
    assert_type_equal(&type, 7, "Pullover");
}

static void test_decode_type_invalid_id(void) {
    const char payload[] = "ID=four TYPE=Cardigan";
    Type type = {0};

    PayloadStatus status = payload_decode_type(
        payload, (int)strlen(payload), &type);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_type_missing_id(void) {
    const char payload[] = "TYPE=Cardigan";
    Type type = {0};

    PayloadStatus status = payload_decode_type(
        payload, (int)strlen(payload), &type);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_type_missing_type(void) {
    const char payload[] = "ID=4";
    Type type = {0};

    PayloadStatus status = payload_decode_type(
        payload, (int)strlen(payload), &type);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_encode_type_rows_success(void) {
    Type types[] = {
        {.id = 1, .type = "Pullover"},
        {.id = 2, .type = "Cardigan"},
    };
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_type_rows(
        payload, sizeof(payload), &payload_length, types, 2);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload,
                  "ID=1 TYPE=Pullover\n"
                  "ID=2 TYPE=Cardigan") == 0);
    assert(payload_length == (int)strlen(payload));
}

static void test_encode_type_rows_insufficient_capacity(void) {
    Type types[] = {
        {.id = 1, .type = "Pullover"},
        {.id = 2, .type = "Cardigan"},
    };
    char payload[12] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_type_rows(
        payload, sizeof(payload), &payload_length, types, 2);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_type_rows_success(void) {
    const char payload[] =
        "ID=1 TYPE=Pullover\n"
        "ID=2 TYPE=Cardigan";
    Type types[2] = {0};
    int type_count = -1;

    PayloadStatus status = payload_decode_type_rows(
        payload, (int)strlen(payload), types, 2, &type_count);

    assert(status == PAYLOAD_STATUS_OK);
    assert(type_count == 2);
    assert_type_equal(&types[0], 1, "Pullover");
    assert_type_equal(&types[1], 2, "Cardigan");
}

static void test_decode_type_rows_insufficient_capacity(void) {
    const char payload[] =
        "ID=1 TYPE=Pullover\n"
        "ID=2 TYPE=Cardigan";
    Type types[1] = {0};
    int type_count = -1;

    PayloadStatus status = payload_decode_type_rows(
        payload, (int)strlen(payload), types, 1, &type_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_type_rows_malformed_row(void) {
    const char payload[] =
        "ID=1 TYPE=Pullover\n"
        "ID=bad TYPE=Cardigan";
    Type types[2] = {0};
    int type_count = -1;

    PayloadStatus status = payload_decode_type_rows(
        payload, (int)strlen(payload), types, 2, &type_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_all_type(void) {
    test_encode_type_success();
    test_encode_type_exact_capacity();
    test_encode_type_insufficient_capacity();
    test_decode_type_success();
    test_decode_type_without_null_in_length();
    test_decode_type_invalid_id();
    test_decode_type_missing_id();
    test_decode_type_missing_type();
    test_encode_type_rows_success();
    test_encode_type_rows_insufficient_capacity();
    test_decode_type_rows_success();
    test_decode_type_rows_insufficient_capacity();
    test_decode_type_rows_malformed_row();

    printf("G payload_type: PASS\n");
}

static void assert_condition_equal(const Condition *actual, int expected_id,
                                   const char *expected_name) {
    assert(actual->id == expected_id);
    assert(strcmp(actual->condition, expected_name) == 0);
}

static void test_encode_condition_success(void) {
    Condition condition = {.id = 4, .condition = "Good"};
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_condition(
        payload, sizeof(payload), &payload_length, &condition);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 CONDITION=Good") == 0);
    assert(payload_length == (int)strlen("ID=4 CONDITION=Good"));
}

static void test_encode_condition_exact_capacity(void) {
    Condition condition = {.id = 4, .condition = "Good"};
    char payload[20]; /* 19 payload characters plus null terminator. */
    int payload_length = -1;

    PayloadStatus status = payload_encode_condition(
        payload, sizeof(payload), &payload_length, &condition);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 CONDITION=Good") == 0);
    assert(payload_length == 19);
}

static void test_encode_condition_insufficient_capacity(void) {
    Condition condition = {.id = 4, .condition = "Good"};
    char payload[19] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_condition(
        payload, sizeof(payload), &payload_length, &condition);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_condition_success(void) {
    const char payload[] = "ID=4 CONDITION=Good";
    Condition condition = {0};

    PayloadStatus status = payload_decode_condition(
        payload, (int)strlen(payload), &condition);

    assert(status == PAYLOAD_STATUS_OK);
    assert_condition_equal(&condition, 4, "Good");
}

static void test_decode_condition_without_null_in_length(void) {
    const char payload[] = {
        'I', 'D', '=', '7', ' ',
        'C', 'O', 'N', 'D', 'I', 'T', 'I', 'O', 'N', '=',
        'E', 'x', 'c', 'e', 'l', 'l', 'e', 'n', 't'
    };
    Condition condition = {0};

    PayloadStatus status = payload_decode_condition(
        payload, sizeof(payload), &condition);

    assert(status == PAYLOAD_STATUS_OK);
    assert_condition_equal(&condition, 7, "Excellent");
}

static void test_decode_condition_invalid_id(void) {
    const char payload[] = "ID=four CONDITION=Good";
    Condition condition = {0};

    PayloadStatus status = payload_decode_condition(
        payload, (int)strlen(payload), &condition);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_condition_missing_id(void) {
    const char payload[] = "CONDITION=Good";
    Condition condition = {0};

    PayloadStatus status = payload_decode_condition(
        payload, (int)strlen(payload), &condition);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_condition_missing_condition(void) {
    const char payload[] = "ID=4";
    Condition condition = {0};

    PayloadStatus status = payload_decode_condition(
        payload, (int)strlen(payload), &condition);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_encode_condition_rows_success(void) {
    Condition conditions[] = {
        {.id = 1, .condition = "Excellent"},
        {.id = 2, .condition = "Good"},
    };
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_condition_rows(
        payload, sizeof(payload), &payload_length, conditions, 2);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload,
                  "ID=1 CONDITION=Excellent\n"
                  "ID=2 CONDITION=Good") == 0);
    assert(payload_length == (int)strlen(payload));
}

static void test_encode_condition_rows_insufficient_capacity(void) {
    Condition conditions[] = {
        {.id = 1, .condition = "Excellent"},
        {.id = 2, .condition = "Good"},
    };
    char payload[12] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_condition_rows(
        payload, sizeof(payload), &payload_length, conditions, 2);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_condition_rows_success(void) {
    const char payload[] =
        "ID=1 CONDITION=Excellent\n"
        "ID=2 CONDITION=Good";
    Condition conditions[2] = {0};
    int condition_count = -1;

    PayloadStatus status = payload_decode_condition_rows(
        payload, (int)strlen(payload), conditions, 2, &condition_count);

    assert(status == PAYLOAD_STATUS_OK);
    assert(condition_count == 2);
    assert_condition_equal(&conditions[0], 1, "Excellent");
    assert_condition_equal(&conditions[1], 2, "Good");
}

static void test_decode_condition_rows_insufficient_capacity(void) {
    const char payload[] =
        "ID=1 CONDITION=Excellent\n"
        "ID=2 CONDITION=Good";
    Condition conditions[1] = {0};
    int condition_count = -1;

    PayloadStatus status = payload_decode_condition_rows(
        payload, (int)strlen(payload), conditions, 1, &condition_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_condition_rows_malformed_row(void) {
    const char payload[] =
        "ID=1 CONDITION=Excellent\n"
        "ID=bad CONDITION=Good";
    Condition conditions[2] = {0};
    int condition_count = -1;

    PayloadStatus status = payload_decode_condition_rows(
        payload, (int)strlen(payload), conditions, 2, &condition_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_all_condition(void) {
    test_encode_condition_success();
    test_encode_condition_exact_capacity();
    test_encode_condition_insufficient_capacity();
    test_decode_condition_success();
    test_decode_condition_without_null_in_length();
    test_decode_condition_invalid_id();
    test_decode_condition_missing_id();
    test_decode_condition_missing_condition();
    test_encode_condition_rows_success();
    test_encode_condition_rows_insufficient_capacity();
    test_decode_condition_rows_success();
    test_decode_condition_rows_insufficient_capacity();
    test_decode_condition_rows_malformed_row();

    printf("G payload_condition: PASS\n");
}

static void assert_size_equal(const Size *actual, int expected_id,
                              const char *expected_name) {
    assert(actual->id == expected_id);
    assert(strcmp(actual->size, expected_name) == 0);
}

static void test_encode_size_success(void) {
    Size size = {.id = 4, .size = "Medium"};
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_size(
        payload, sizeof(payload), &payload_length, &size);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 SIZE=Medium") == 0);
    assert(payload_length == (int)strlen("ID=4 SIZE=Medium"));
}

static void test_encode_size_exact_capacity(void) {
    Size size = {.id = 4, .size = "Medium"};
    char payload[17]; /* 16 payload characters plus null terminator. */
    int payload_length = -1;

    PayloadStatus status = payload_encode_size(
        payload, sizeof(payload), &payload_length, &size);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=4 SIZE=Medium") == 0);
    assert(payload_length == 16);
}

static void test_encode_size_insufficient_capacity(void) {
    Size size = {.id = 4, .size = "Medium"};
    char payload[16] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_size(
        payload, sizeof(payload), &payload_length, &size);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_size_success(void) {
    const char payload[] = "ID=4 SIZE=Medium";
    Size size = {0};

    PayloadStatus status = payload_decode_size(
        payload, (int)strlen(payload), &size);

    assert(status == PAYLOAD_STATUS_OK);
    assert_size_equal(&size, 4, "Medium");
}

static void test_decode_size_without_null_in_length(void) {
    const char payload[] = {
        'I', 'D', '=', '7', ' ',
        'S', 'I', 'Z', 'E', '=',
        'X', '_', 'L', 'a', 'r', 'g', 'e'
    };
    Size size = {0};

    PayloadStatus status = payload_decode_size(
        payload, sizeof(payload), &size);

    assert(status == PAYLOAD_STATUS_OK);
    assert_size_equal(&size, 7, "X_Large");
}

static void test_decode_size_invalid_id(void) {
    const char payload[] = "ID=four SIZE=Medium";
    Size size = {0};

    PayloadStatus status = payload_decode_size(
        payload, (int)strlen(payload), &size);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_size_missing_id(void) {
    const char payload[] = "SIZE=Medium";
    Size size = {0};

    PayloadStatus status = payload_decode_size(
        payload, (int)strlen(payload), &size);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_size_missing_size(void) {
    const char payload[] = "ID=4";
    Size size = {0};

    PayloadStatus status = payload_decode_size(
        payload, (int)strlen(payload), &size);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_encode_size_rows_success(void) {
    Size sizes[] = {
        {.id = 1, .size = "Small"},
        {.id = 2, .size = "Medium"},
    };
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_size_rows(
        payload, sizeof(payload), &payload_length, sizes, 2);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload,
                  "ID=1 SIZE=Small\n"
                  "ID=2 SIZE=Medium") == 0);
    assert(payload_length == (int)strlen(payload));
}

static void test_encode_size_rows_insufficient_capacity(void) {
    Size sizes[] = {
        {.id = 1, .size = "Small"},
        {.id = 2, .size = "Medium"},
    };
    char payload[12] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_size_rows(
        payload, sizeof(payload), &payload_length, sizes, 2);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_size_rows_success(void) {
    const char payload[] =
        "ID=1 SIZE=Small\n"
        "ID=2 SIZE=Medium";
    Size sizes[2] = {0};
    int size_count = -1;

    PayloadStatus status = payload_decode_size_rows(
        payload, (int)strlen(payload), sizes, 2, &size_count);

    assert(status == PAYLOAD_STATUS_OK);
    assert(size_count == 2);
    assert_size_equal(&sizes[0], 1, "Small");
    assert_size_equal(&sizes[1], 2, "Medium");
}

static void test_decode_size_rows_insufficient_capacity(void) {
    const char payload[] =
        "ID=1 SIZE=Small\n"
        "ID=2 SIZE=Medium";
    Size sizes[1] = {0};
    int size_count = -1;

    PayloadStatus status = payload_decode_size_rows(
        payload, (int)strlen(payload), sizes, 1, &size_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_decode_size_rows_malformed_row(void) {
    const char payload[] =
        "ID=1 SIZE=Small\n"
        "ID=bad SIZE=Medium";
    Size sizes[2] = {0};
    int size_count = -1;

    PayloadStatus status = payload_decode_size_rows(
        payload, (int)strlen(payload), sizes, 2, &size_count);

    assert(status == PAYLOAD_STATUS_ERROR);
}

static void test_all_size(void) {
    test_encode_size_success();
    test_encode_size_exact_capacity();
    test_encode_size_insufficient_capacity();
    test_decode_size_success();
    test_decode_size_without_null_in_length();
    test_decode_size_invalid_id();
    test_decode_size_missing_id();
    test_decode_size_missing_size();
    test_encode_size_rows_success();
    test_encode_size_rows_insufficient_capacity();
    test_decode_size_rows_success();
    test_decode_size_rows_insufficient_capacity();
    test_decode_size_rows_malformed_row();

    printf("G payload_size: PASS\n");
}

static void test_encode_id_success(void) {
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status =
        payload_encode_id(payload, sizeof(payload), &payload_length, 42);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=42") == 0);
    assert(payload_length == (int)strlen("ID=42"));
}

static void test_encode_id_exact_capacity(void) {
    char payload[6] = {0}; /* Five characters plus null. */
    int payload_length = -1;

    PayloadStatus status =
        payload_encode_id(payload, sizeof(payload), &payload_length, 42);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=42") == 0);
    assert(payload_length == 5);
}

static void test_encode_id_insufficient_capacity(void) {
    char payload[5] = "old";
    int payload_length = -1;

    PayloadStatus status =
        payload_encode_id(payload, sizeof(payload), &payload_length, 42);

    assert(status == PAYLOAD_STATUS_ERROR);
    assert(payload[0] == '\0');
    assert(payload_length == -1);
}

static void test_encode_id_negative(void) {
    char payload[STR_LENGTH] = "old";
    int payload_length = -1;

    PayloadStatus status =
        payload_encode_id(payload, sizeof(payload), &payload_length, -1);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "ID=-1") == 0);
    assert(payload_length == 5);
}

static void test_encode_id_null_arguments(void) {
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    assert(payload_encode_id(
        NULL, sizeof(payload), &payload_length, 4
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_encode_id(
        payload, sizeof(payload), NULL, 4
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_encode_id(
        payload, 0, &payload_length, 4
    ) == PAYLOAD_STATUS_ERROR);
}

static void test_decode_id_success(void) {
    const char payload[] = "ID=42";
    int id = -1;

    PayloadStatus status =
        payload_decode_id(payload, strlen(payload), &id);

    assert(status == PAYLOAD_STATUS_OK);
    assert(id == 42);
}

static void test_decode_id_without_null_in_length(void) {
    const char payload[] = {'I', 'D', '=', '4', '2'};
    int id = -1;

    PayloadStatus status =
        payload_decode_id(payload, sizeof(payload), &id);

    assert(status == PAYLOAD_STATUS_OK);
    assert(id == 42);
}

static void test_decode_id_invalid_payloads(void) {
    int id = 99;

    assert(payload_decode_id(
        "NUMBER=42", strlen("NUMBER=42"), &id
    ) == PAYLOAD_STATUS_ERROR);
    
    assert(payload_decode_id(
        "ID=abc", strlen("ID=abc"), &id
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_decode_id(
        "ID=4 EXTRA=5", strlen("ID=4 EXTRA=5"), &id
    ) == PAYLOAD_STATUS_ERROR);

    assert(id == 99);
}

static void test_decode_id_null_arguments(void) {
    int id = -1;

    assert(payload_decode_id(
        NULL, 4, &id
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_decode_id(
        "ID=4", 4, NULL
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_decode_id(
        "ID=4", 0, &id
    ) == PAYLOAD_STATUS_ERROR);
}

void test_all_id(void) {
    test_encode_id_success();
    test_encode_id_exact_capacity();
    test_encode_id_insufficient_capacity();
    test_encode_id_negative();
    test_encode_id_null_arguments();

    test_decode_id_success();
    test_decode_id_without_null_in_length();
    test_decode_id_invalid_payloads();
    test_decode_id_null_arguments();

    printf("G id: PASS\n");
}

static void assert_pagination_equal(
    const Pagination *actual,
    int expected_limit,
    int expected_offset
) {
    assert(actual->limit == expected_limit);
    assert(actual->offset == expected_offset);
}

static void test_encode_pagination_success(void) {
    Pagination pagination = {.limit = 10, .offset = 20};
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_pagination(
        payload, sizeof(payload), &payload_length, &pagination);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "LIMIT=10 OFFSET=20") == 0);
    assert(payload_length == (int)strlen("LIMIT=10 OFFSET=20"));
}

static void test_encode_pagination_exact_capacity(void) {
    Pagination pagination = {.limit = 10, .offset = 20};
    char payload[19] = {0};
    int payload_length = -1;

    PayloadStatus status = payload_encode_pagination(
        payload, sizeof(payload), &payload_length, &pagination);

    assert(status == PAYLOAD_STATUS_OK);
    assert(strcmp(payload, "LIMIT=10 OFFSET=20") == 0);
    assert(payload_length == 18);
}

static void test_encode_pagination_insufficient_capacity(void) {
    Pagination pagination = {.limit = 10, .offset = 20};
    char payload[18] = "old";
    int payload_length = -1;

    PayloadStatus status = payload_encode_pagination(
        payload, sizeof(payload), &payload_length, &pagination);

    assert(status == PAYLOAD_STATUS_ERROR);
    assert(payload[0] == '\0');
    assert(payload_length == -1);
}

static void test_encode_pagination_invalid_values(void) {
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    Pagination zero_limit = {.limit = 0, .offset = 0};
    assert(payload_encode_pagination(
        payload, sizeof(payload), &payload_length, &zero_limit
    ) == PAYLOAD_STATUS_ERROR);

    Pagination negative_offset = {.limit = 10, .offset = -1};
    assert(payload_encode_pagination(
        payload, sizeof(payload), &payload_length, &negative_offset
    ) == PAYLOAD_STATUS_ERROR);
}

static void test_encode_pagination_null_arguments(void) {
    Pagination pagination = {.limit = 10, .offset = 0};
    char payload[STR_LENGTH] = {0};
    int payload_length = -1;

    assert(payload_encode_pagination(
        NULL, sizeof(payload), &payload_length, &pagination
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_encode_pagination(
        payload, sizeof(payload), NULL, &pagination
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_encode_pagination(
        payload, sizeof(payload), &payload_length, NULL
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_encode_pagination(
        payload, 0, &payload_length, &pagination
    ) == PAYLOAD_STATUS_ERROR);
}

static void test_decode_pagination_success(void) {
    const char payload[] = "LIMIT=10 OFFSET=20";
    Pagination pagination = {0};

    PayloadStatus status = payload_decode_pagination(
        payload, strlen(payload), &pagination);

    assert(status == PAYLOAD_STATUS_OK);
    assert_pagination_equal(&pagination, 10, 20);
}

static void test_decode_pagination_reversed_order(void) {
    const char payload[] = "OFFSET=20 LIMIT=10";
    Pagination pagination = {0};

    PayloadStatus status = payload_decode_pagination(
        payload, strlen(payload), &pagination);

    assert(status == PAYLOAD_STATUS_OK);
    assert_pagination_equal(&pagination, 10, 20);
}

static void test_decode_pagination_without_null_in_length(void) {
    const char payload[] = {
        'L', 'I', 'M', 'I', 'T', '=', '1', '0', ' ',
        'O', 'F', 'F', 'S', 'E', 'T', '=', '2', '0'
    };
    Pagination pagination = {0};

    PayloadStatus status = payload_decode_pagination(
        payload, sizeof(payload), &pagination);

    assert(status == PAYLOAD_STATUS_OK);
    assert_pagination_equal(&pagination, 10, 20);
}

static void test_decode_pagination_invalid_payloads(void) {
    Pagination pagination = {.limit = 99, .offset = 99};

    assert(payload_decode_pagination(
        "LIMIT=10", strlen("LIMIT=10"), &pagination
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_decode_pagination(
        "LIMIT=abc OFFSET=20",
        strlen("LIMIT=abc OFFSET=20"),
        &pagination
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_decode_pagination(
        "LIMIT=10 LIMIT=20",
        strlen("LIMIT=10 LIMIT=20"),
        &pagination
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_decode_pagination(
        "LIMIT=10 UNKNOWN=20",
        strlen("LIMIT=10 UNKNOWN=20"),
        &pagination
    ) == PAYLOAD_STATUS_ERROR);

    assert_pagination_equal(&pagination, 99, 99);
}

static void test_decode_pagination_invalid_values(void) {
    Pagination pagination = {0};

    assert(payload_decode_pagination(
        "LIMIT=0 OFFSET=0",
        strlen("LIMIT=0 OFFSET=0"),
        &pagination
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_decode_pagination(
        "LIMIT=10 OFFSET=-1",
        strlen("LIMIT=10 OFFSET=-1"),
        &pagination
    ) == PAYLOAD_STATUS_ERROR);
}

static void test_decode_pagination_null_arguments(void) {
    Pagination pagination = {0};

    assert(payload_decode_pagination(
        NULL, 10, &pagination
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_decode_pagination(
        "LIMIT=10 OFFSET=0",
        strlen("LIMIT=10 OFFSET=0"),
        NULL
    ) == PAYLOAD_STATUS_ERROR);

    assert(payload_decode_pagination(
        "LIMIT=10 OFFSET=0", 0, &pagination
    ) == PAYLOAD_STATUS_ERROR);
}

void test_all_pagination(void) {
    test_encode_pagination_success();
    test_encode_pagination_exact_capacity();
    test_encode_pagination_insufficient_capacity();
    test_encode_pagination_invalid_values();
    test_encode_pagination_null_arguments();

    test_decode_pagination_success();
    test_decode_pagination_reversed_order();
    test_decode_pagination_without_null_in_length();
    test_decode_pagination_invalid_payloads();
    test_decode_pagination_invalid_values();
    test_decode_pagination_null_arguments();

    printf("G pagination: PASS\n");
}

void test_all_payload(void) {
    test_all_piece_type();
    test_all_brand();
    test_all_color_family();
    test_all_neckline();
    test_all_sleeves();
    test_all_type();
    test_all_condition();
    test_all_size();
    test_all_id();
    test_all_pagination();

    printf("payload: PASS\n----------\n");
}
