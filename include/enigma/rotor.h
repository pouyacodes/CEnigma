#ifndef _X_ROTOR
#define _X_ROTOR

#include <stdbool.h>
#include <stddef.h>

#include "sequence.h"
#include "da_list.h"

typedef struct Rotor {
    Sequence sequence;
    size_t rotations;
} Rotor;

typedef struct RotorList {
    DYNAMIC_ARRAY(Rotor)
} RotorList;

void enigma_rotor_free(Rotor *rotor);
Rotor enigma_rotor_random(Sequence *sequence);
wchar_t enigma_rotor_action(Sequence *sequence, Rotor *rotor, wchar_t input, bool reverse);
void enigma_rotor_rotation(Rotor *rotor);
void enigma_rotors_rotate(RotorList *rotors);

#endif // _X_ROTOR
