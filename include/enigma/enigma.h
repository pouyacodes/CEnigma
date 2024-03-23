#ifndef _X_ENIGMA
#define _X_ENIGMA

#include <stddef.h>

#include "language.h"
#include "plugboard.h"
#include "rotor.h"

/**
 * \brief   Represents a Enigma machine.
 *
 * \details The instance of this structure contains all the information
 *          required for encoding texts. Language that Enigma uses, Plugboard
 *          Rotors.
 *
 *
 * \member language             Pointer to a Language instance. Texts language
 * \member plugboard            Pointer to PlugboardList
 *
 * \member alphabet_rotors      List of rotors used for alphabet characters
 * \member digit_rotors         List of rotors used for digit characters
 * \member punctuation_rotors   List of rotors used for punctuation characters
 */
typedef struct Enigma {
    Language *language;
    PlugboardList *plugboard;

    RotorList *alphabet_rotors;
    RotorList *digit_rotors;
    RotorList *punctuation_rotors;
} Enigma;


/**
 * \brief   Encodes a wide character
 *
 * \details This function accepts the machine instance and a wchar_t that needs to be encoded.
 *
 * \param   engine  Pointer to the Enigma instance
 * \param   c       The character to be encoded
 *
 * \return  The encoded character
 */
wchar_t enigma_encodec(Enigma *engine, wchar_t c);

/**
 * \brief   Encodes a wide character string
 *
 * \details This function accepts the machine instance and a wchar_t string
 *          that needs to be encoded.
 *
 * \note    This function returns pointer to encoded string. Memory
 *          for encoded string is obtained by malloc(3) and you can later
 *          release that using free(3) to avoid memory leaks.
 *
 * \param   engine      Pointer to the Enigma instance
 * \param   plain_text  The string to be encoded
 *
 * \return  The encoded character
 *
 * \retval  NULL        If function fails to encode
 * \return  wchar_t *   The cipher text (encoded form of plain_text)
 */
wchar_t *enigma_encode(Enigma *engine, const wchar_t *plain_text);

#endif // _X_ENIGMA
