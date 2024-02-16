#ifndef _X_LANGUAGE
#define _X_LANGUAGE

#include <wchar.h>
#include "sequence.h"

typedef struct Language {
    Sequence *alphabet;
    Sequence *digit;
    Sequence *punctuation;

    int (*isupper)(wint_t wc);
    wint_t (*toupper)(wint_t wc);
    wint_t (*tolower)(wint_t wc);
} Language;

#endif // _X_LANGUAGE
