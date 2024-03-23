#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include <enigma/enigma.h>

static wchar_t enigma_machine(Sequence *sequence, RotorList *rotors, wchar_t c)
{
    da_foreach(rotors) {
        Rotor *rotor = &rotors->items[i];
        c = enigma_rotor_action(sequence, rotor, c, false);
    }

    c = enigma_sequence_reflector(sequence, c);

    da_rev_foreach(rotors) {
        Rotor *rotor = &rotors->items[i];
        c = enigma_rotor_action(sequence, rotor, c, true);
    }

    enigma_rotors_rotate(rotors);

    return c;
}

static wchar_t enigma_encode_alphabet(const Enigma *e, wchar_t c)
{
    if (e->plugboard) c = enigma_plugboard(e->plugboard, c);
    c = enigma_machine(e->language->alphabet, e->alphabet_rotors, c);
    if (e->plugboard) c = enigma_plugboard(e->plugboard, c);

    return c;
}

static wchar_t enigma_encode_digit(const Enigma *e, wchar_t c)
{
    return enigma_machine(e->language->digit, e->digit_rotors, c);
}

static wchar_t enigma_encode_punctuation(const Enigma *e, wchar_t c)
{
    return enigma_machine(e->language->punctuation, e->punctuation_rotors, c);
}

wchar_t enigma_encodec(Enigma *e, wchar_t c)
{
    Language *lang = e->language;

    wchar_t ret = c;

    if (lang->tolower != NULL) {
        ret = lang->tolower(ret);
    }

    if (enigma_sequence_find(lang->alphabet, ret) >= 0) {
        ret = enigma_encode_alphabet(e, ret);
    } else if (enigma_sequence_find(lang->digit, ret) >= 0) {
        ret = enigma_encode_digit(e, ret);
    } else if (enigma_sequence_find(lang->punctuation, ret) >= 0) {
        ret = enigma_encode_punctuation(e, ret);
    }

    if (lang->isupper != NULL && lang->isupper(c)) {
        if (lang->toupper != NULL) ret = lang->toupper(ret);
    }

    return ret;
}

wchar_t *enigma_encode(Enigma *e, const wchar_t *plain_text)
{
    assert(plain_text != NULL);

    size_t len = wcslen(plain_text);
    wchar_t *buffer = calloc(sizeof(wchar_t), len + 1);
    if (buffer == NULL) return NULL;

    for (size_t i = 0; i < len; ++i) {
        buffer[i] = enigma_encodec(e, plain_text[i]);
    }

    buffer[len] = L'\0';
    return buffer;
}
