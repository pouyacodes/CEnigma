#include <enigma/sequence.h>

#include "module.h"
#include "utils.h"

TEST_CASE(sequence_pos_first) {
    ASSERT_EQUAL_NUMERIC(enigma_sequence_find(&sample, L't'),   0);
}

TEST_CASE(sequence_pos_third) {
    ASSERT_EQUAL_NUMERIC(enigma_sequence_find(&sample, L'e'),   2);
}

TEST_CASE(sequence_pos_not_exists) {
    ASSERT_EQUAL_NUMERIC(enigma_sequence_find(&sample, L'\0'), -1);
}
