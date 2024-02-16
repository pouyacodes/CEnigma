#ifndef _X_ENIGMA
#define _X_ENIGMA

#include <stddef.h>

#include "language.h"
#include "plugboard.h"
#include "rotor.h"

typedef struct Enigma {
    Language *language;
    PlugboardList *plugboard;

    RotorList *alphabet_rotors;
    RotorList *digit_rotors;
    RotorList *punctuation_rotors;
} Enigma;

wchar_t enigma_encodec(Enigma *engine, wchar_t c);
wchar_t *enigma_encode(Enigma *engine, const wchar_t *plain_text);

#endif // _X_ENIGMA
