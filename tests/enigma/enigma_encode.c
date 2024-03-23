#include <enigma/enigma.h>

static wchar_t *cipher_text;
static const wchar_t *plain_text = L"daddy";

#include "utils.h"

#include "module.h"

TEST_CASE_SETUP(enigma_encode) {}

TEST_CASE(enigma_encode) {
    static Enigma engine = {
        .language = &language,
        .plugboard = NULL,
        .alphabet_rotors = &alphabet_rotors,
    };

    cipher_text = enigma_encode(&engine, plain_text);

    ASSERT_EQUAL_WIDE_STRING(cipher_text, L"ydaab");
}

TEST_CASE_TEARDOWN(enigma_encode) {
    free(cipher_text);
}
