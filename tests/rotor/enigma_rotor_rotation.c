#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <enigma/rotor.h>

#include "module.h"
#include "utils.h"

static Rotor rotor;

TEST_CASE_SETUP(rotor_rotation_is_ok) {
    if (sample.len > 0) {
        rotor.sequence.len = sample.len;
        rotor.sequence.values = calloc(sizeof(wchar_t), sample.len + 1);
        assert(rotor.sequence.values != NULL);

        memcpy(rotor.sequence.values, sample.values, sizeof(wchar_t) * sample.len);
        rotor.sequence.values[sample.len] = '\0';
    }
}

TEST_CASE(rotor_rotation_is_ok) {
    enigma_rotor_rotation(&rotor);
    ASSERT_EQUAL_WIDE_STRING(rotor.sequence.values, L"bcda");
}

TEST_CASE_TEARDOWN(rotor_rotation_is_ok) {
    free(rotor.sequence.values);
}
