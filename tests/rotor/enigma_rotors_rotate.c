#include <enigma/rotor.h>

#include "module.h"

#define ROTORS_LENGTH 3
#define SEQ_LEN 4

static Rotor rotors[ROTORS_LENGTH] = {
    {{.values = (wchar_t[SEQ_LEN + 1]){ L"abcd" }, SEQ_LEN}, SEQ_LEN - 1},
    {{.values = (wchar_t[SEQ_LEN + 1]){ L"dacb" }, SEQ_LEN}, SEQ_LEN - 1},
    {{.values = (wchar_t[SEQ_LEN + 1]){ L"cdab" }, SEQ_LEN},           0},
};

static RotorList list_rotors = {.items = rotors, .len = ROTORS_LENGTH};

TEST_CASE(rotors_rotation) {
    enigma_rotors_rotate(&list_rotors);

    ASSERT_EQUAL_NUMERIC(rotors[0].rotations, 0);
    ASSERT_EQUAL_NUMERIC(rotors[1].rotations, 0);
    ASSERT_EQUAL_NUMERIC(rotors[2].rotations, 1);

    ASSERT_EQUAL_WIDE_STRING(rotors[0].sequence.values, L"bcda");
    ASSERT_EQUAL_WIDE_STRING(rotors[1].sequence.values, L"acbd");
    ASSERT_EQUAL_WIDE_STRING(rotors[2].sequence.values, L"dabc");
}
