#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <enigma/rotor.h>

void enigma_rotor_free(Rotor *rotor)
{
    assert(rotor != NULL);
    free(rotor->sequence.values);
}

Rotor enigma_rotor_random(Sequence *sequence)
{
    assert(sequence != NULL);

    Rotor rotor = {0};
    if (sequence->len == 0 || sequence->values == NULL) return rotor;

    rotor.sequence.values = calloc(sizeof(wchar_t), sequence->len);
    if (rotor.sequence.values == NULL) return rotor;

    memcpy(rotor.sequence.values, sequence->values, sequence->len * sizeof(wchar_t));

    rotor.sequence.len = sequence->len;

    for (size_t i = 0; i < rotor.sequence.len; ++i) {
        size_t rand_idx = rand() % rotor.sequence.len;

        wchar_t temp = rotor.sequence.values[i];
        rotor.sequence.values[i] = rotor.sequence.values[rand_idx];
        rotor.sequence.values[rand_idx] = temp;
    }

    return rotor;
}

void enigma_rotor_rotation(Rotor *rotor)
{
    assert(rotor->sequence.len > 0);

    wchar_t first = rotor->sequence.values[0];

    for (size_t i = 0; i < rotor->sequence.len - 1; ++i) {
        rotor->sequence.values[i] = rotor->sequence.values[i + 1];
    }

    rotor->sequence.values[rotor->sequence.len - 1] = first;
}

void enigma_rotors_rotate(RotorList *rotors)
{
    bool next_update = false;

    da_foreach(rotors) {
        Rotor *it = &rotors->items[i];
        enigma_rotor_rotation(it);

        it->rotations += 1;

        if (it->rotations == it->sequence.len) {
            it->rotations = 0;
            next_update = true;
        } else {
            next_update = false;
        }

        if (!next_update) return;
    }
}

wchar_t enigma_rotor_action(Sequence *sequence, Rotor *rotor, wchar_t input, bool reverse)
{
    Sequence *input_sequence = !reverse ? sequence : &rotor->sequence;
    Sequence *front_sequence = !reverse ? &rotor->sequence : sequence;

    int pos = enigma_sequence_find(input_sequence, input);
    assert(pos != -1);

    return front_sequence->values[pos];
}
