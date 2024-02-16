#ifndef _X_LANGUAGE_PACK_FARSI
#define _X_LANGUAGE_PACK_FARSI

#include <wchar.h>
#include <enigma/sequence.h>
#include <enigma/language.h>

static wchar_t alphabets[] = L"ءاآأإبپتثجچحخدذرزژسشصضطظعغفقکكگلمنوؤهةیئ";
static Sequence alphabets_sequence = {.values = alphabets, .len = 41};

static wchar_t digits[] = L"۰۱۲۳۴۵۶۷۸۹";
static Sequence digits_sequence = {.values = digits, .len = 10};

static wchar_t punctuations[] = L"[]{}|«»:٫٬،؛<>؟!﷼×÷٪";
static Sequence punctuations_sequence = {.values = punctuations, .len = 20};

#ifdef ENIGMA_DEFINE_LANGUAGE
static Language language = {
    .alphabet    = &alphabets_sequence,
    .digit       = &digits_sequence,
    .punctuation = &punctuations_sequence,
};
#endif // ENIGMA_DEFINE_LANGUAGE

#endif // _X_LANGUAGE_PACK_FARSI
