#include "module.h"

#include <enigma/plugboard.h>

static PlugPair pairs[] = {
    { 'p', 'x' },
    { 'f', 'g' },
    { 'z', 'a' },
    { 'b', 'c' },
};

#define ARRAY_LEN(a) (sizeof(a)/sizeof(*a))

static PlugboardList plugpairs = { .items = pairs, .len = ARRAY_LEN(pairs) };

TEST_CASE(plugboard_1) {
    ASSERT_EQUAL_WIDE_CHARACTER(enigma_plugboard(&plugpairs, 'p'), 'x');
}

TEST_CASE(plugboard_2) {
    ASSERT_EQUAL_WIDE_CHARACTER(enigma_plugboard(&plugpairs, 'x'), 'p');
}

TEST_CASE(plugboard_3) {
    ASSERT_EQUAL_WIDE_CHARACTER(enigma_plugboard(&plugpairs, 'f'), 'g');
}

TEST_CASE(plugboard_4) {
    ASSERT_EQUAL_WIDE_CHARACTER(enigma_plugboard(&plugpairs, 'c'), 'b');
}
