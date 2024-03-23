#ifndef _X_SEQUENCE
#define _X_SEQUENCE

#include <stddef.h>

/**
 * \brief   Represents a Sequence
 *
 * \details instances of this structure represent a rotor that has
 *          a sequence and the number of times that sequence is rotated.
 *
 * \memebr  values  Pointer to sequence
 * \member  len     The length of the sequence
 */
typedef struct Sequence {
    wchar_t *values;
    size_t len;
} Sequence;

/**
 * \brief   Find index of a character in a sequence.
 *
 * \details This function iterates through a sequence and finds
 *          the index of `needle` in that sequence.
 *
 * \param   seq     pointer to Sequence instance.
 * \param   needle  Character that need to be found.
 *
 * \return  returns the index in the sequence
 *
 * \retval  -1  When index is not found in `seq`
 * \retval  int Index of `needle`
 */
int enigma_sequence_find(const Sequence *seq, wchar_t needle);

/**
 * \brief   Reflects a character.
 *
 * \details The function finds the index of 'input' in a sequence
 *          and returns the corresponding character from the end of the sequence.
 *
 * \param   seq     pointer to Sequence instance.
 * \param   input   Character that need to be reflected.
 *
 * \return  returns the reflected character
 *
 * \retval  input   When index is not found in `seq`
 * \retval  wchar_t Reflected form of `input`
 */
wchar_t enigma_sequence_reflector(const Sequence *seq, wchar_t input);

#endif // _X_SEQUENCE
