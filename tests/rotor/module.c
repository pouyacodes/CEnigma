#include "module.h"

#define CASES \
    CASE(rotor_action_forward) \
    CASE(rotor_action_backward) \
    CASE(rotor_rotation_is_ok, SETUP, TEARDOWN) \
    CASE(rotors_rotation)

#include "../test_skeleton.c"
