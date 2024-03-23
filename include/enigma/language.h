#ifndef _X_LANGUAGE
#define _X_LANGUAGE

#include <wchar.h>
#include "sequence.h"

/**
 * \brief   Represents a Language
 *
 * \details The instance of this structure contains all the information
 *          required for defining a language. Such as alphabet, digits
 *          punctuation, etc. Also, if the language distinguishes between
 *          cases of letters (like upper/lower case in English) you can
 *          pass appropriate functions that are used for checking those cases.
 *          Engima uses this language to know how to encode such letters.
 *
 * \member alphabet Alphabet sequence
 * \member digit Digit sequence
 * \member punctuation Punctuation sequence
 * \member isupper Pointer to a function that checks if a specific character is upper
 * \member toupper Pointer to a function that returns uppercase of a character
 * \member tolower Pointer to a function that returns lowercase of a character
 */
typedef struct Language {
    Sequence *alphabet;
    Sequence *digit;
    Sequence *punctuation;

    int (*isupper)(wint_t wc);
    wint_t (*toupper)(wint_t wc);
    wint_t (*tolower)(wint_t wc);
} Language;

#endif // _X_LANGUAGE
