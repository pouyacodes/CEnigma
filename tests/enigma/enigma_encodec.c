#include <enigma/enigma.h>

#include "utils.h"
#include "module.h"

TEST_CASE(enigma_encodec) {
    wchar_t input = L'd';
    wchar_t expected = L'y';

    static Enigma engine = {
        .language = &language,
        .plugboard = NULL,
        .alphabet_rotors = &alphabet_rotors,
    };

    wchar_t cipher = enigma_encodec(&engine, input);
    ASSERT_EQUAL_WIDE_CHARACTER(cipher, expected);
}
