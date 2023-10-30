#ifndef _X_ENIGMA_X
#define _X_ENIGMA_X

#include <wchar.h>
#include "da_list.h"

typedef struct Language {
    const wchar_t *alphabet;
    const wchar_t *digit;
    const wchar_t *punctuation;
    int (*isalpha)(wint_t wc);
    int (*isdigit)(wint_t wc);
    int (*ispunct)(wint_t wc);
    int (*isupper)(wint_t wc);
    wint_t (*toupper)(wint_t wc);
    wint_t (*tolower)(wint_t wc);
} Language;

typedef struct PlugPair {
    wchar_t x;
    wchar_t y;
} PlugPair;

typedef struct PlugboardList {
    DYNAMIC_ARRAY(PlugPair)
} PlugboardList;

typedef struct Enigma { 
     const Language *language; 
     const PlugboardList *plugboard;
} Enigma;

wchar_t *enigma_encode(Enigma *engine, const wchar_t *plain_text);

#endif // _X_ENIGMA_X
