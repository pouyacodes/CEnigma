#include <enigma/sequence.h>

#include "module.h"
#include "utils.h"

TEST_CASE(sequence_reflect_first) {
    ASSERT_EQUAL_WIDE_CHARACTER(enigma_sequence_reflector(&sample, L't'), L'g');
}

TEST_CASE(sequence_reflect_last) {
    ASSERT_EQUAL_WIDE_CHARACTER(enigma_sequence_reflector(&sample, L'g'), L't');
}

TEST_CASE(sequence_reflect_mid) {
    size_t mid_pos = sample.len / 2;
    wchar_t expected = sample.values[sample.len % 2 == 0 ? mid_pos - 1 : mid_pos];
    ASSERT_EQUAL_WIDE_CHARACTER(enigma_sequence_reflector(&sample, sample.values[mid_pos]), expected);
}
