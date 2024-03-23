#ifndef _X_UTILS
#define _X_UTILS

#include <wctype.h>

#define SEQ_LEN 4

static wchar_t alphabets[] = L"abdy";
static Sequence alphabets_sequence = {.values = alphabets, .len = SEQ_LEN};

static Language language = {
    .alphabet    = &alphabets_sequence,
    .digit       = NULL,
    .punctuation = NULL,
    .isupper     = iswupper,
    .tolower     = towlower,
    .toupper     = towupper
};

#define ROTORS_LENGTH 3

static Rotor rotors[ROTORS_LENGTH] = {
    {{.values = (wchar_t[SEQ_LEN + 1]){ L"abyd" }, SEQ_LEN}, SEQ_LEN - 1},
    {{.values = (wchar_t[SEQ_LEN + 1]){ L"dayb" }, SEQ_LEN}, SEQ_LEN - 1},
    {{.values = (wchar_t[SEQ_LEN + 1]){ L"ydab" }, SEQ_LEN},           0},
};

static RotorList alphabet_rotors = {.items = rotors, .len = ROTORS_LENGTH};

#endif // _X_UTILS
