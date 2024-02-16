#ifndef _X_SEQUENCE
#define _X_SEQUENCE

#include <stddef.h>

typedef struct Sequence {
    wchar_t *values;
    size_t len;
} Sequence;

int enigma_sequence_find(const Sequence *seq, wchar_t needle);
wchar_t enigma_sequence_reflector(const Sequence *seq, wchar_t input);

#endif // _X_SEQUENCE
