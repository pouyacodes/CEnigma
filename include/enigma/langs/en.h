#ifndef _X_LANGUAGE_PACK_ENGLISH
#define _X_LANGUAGE_PACK_ENGLISH

#include <wctype.h>
#include <enigma/sequence.h>
#include <enigma/language.h>

static wchar_t alphabets[] = L"abcdefghijklmnopqrstuvwxyz";
static Sequence alphabets_sequence = {.values = alphabets, .len = 26};

static wchar_t digits[] = L"0123456789";
static Sequence digits_sequence = {.values = digits, .len = 10};

static wchar_t punctuations[] = L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
static Sequence punctuations_sequence = {.values = punctuations, .len = 32};

#ifdef ENIGMA_DEFINE_LANGUAGE
static Language language = {
    .alphabet    = &alphabets_sequence,
    .digit       = &digits_sequence,
    .punctuation = &punctuations_sequence,
    .isupper     = iswupper,
    .tolower     = towlower,
    .toupper     = towupper
};
#endif // ENIGMA_DEFINE_LANGUAGE

#endif // _X_LANGUAGE_PACK_ENGLISH
