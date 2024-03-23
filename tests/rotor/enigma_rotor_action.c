#include <enigma/rotor.h>

#include "module.h"

#include "utils.h"

static Rotor sample_rotor = {
    {.values = L"cbda", .len = 4}, 0
};

TEST_CASE(rotor_action_forward) {
    wchar_t result = enigma_rotor_action(&sample, &sample_rotor, L'c', false);
    ASSERT_EQUAL_WIDE_CHARACTER(result, L'd');
}

TEST_CASE(rotor_action_backward) {
    wchar_t result = enigma_rotor_action(&sample, &sample_rotor, L'c', true);
    ASSERT_EQUAL_WIDE_CHARACTER(result, L'a');
}
