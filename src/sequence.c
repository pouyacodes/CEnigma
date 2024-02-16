#include <assert.h>

#include <enigma/sequence.h>

int enigma_sequence_find(const Sequence *seq, wchar_t needle)
{
    assert(seq != NULL);

    if (seq->values == NULL || seq->len == 0) return -1;

    for (size_t i = 0; i < seq->len; ++i) {
        if (seq->values[i] == needle) return i;
    }

    return -1;
}

wchar_t enigma_sequence_reflector(const Sequence *seq, wchar_t input)
{
    assert(seq != NULL);

    int pos = enigma_sequence_find(seq, input);
    if (pos < 0) return input;

    return seq->values[seq->len - 1 - pos];
}
