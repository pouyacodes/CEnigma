#ifndef _X_ROTOR
#define _X_ROTOR

#include <stdbool.h>
#include <stddef.h>

#include "sequence.h"
#include "da_list.h"

/**
 * \brief   Represents a Rotor
 *
 * \details instances of this structure represent a rotor with
 *          a sequence and the number of rotations.
 *
 * \memebr  sequence  Sequence that the rotor works on
 * \member  rotations The number of time that sequence is rotated
 */
typedef struct Rotor {
    Sequence sequence;
    size_t rotations;
} Rotor;

/**
 * \brief   List of Rotors
 *
 * \details Represents List of Rotors.
 *
 * \member  items Pointer to `Rotor` instances
 * \member  len   length of List
 * \memebr  cap   capacity of List
 */
typedef struct RotorList {
    DYNAMIC_ARRAY(Rotor)
} RotorList;


/**
 * \brief   Releases a randomized rotor
 *
 * \details If you used `enigma_rotor_random`, you have to
 *          free that using this function.
 *
 * \param   rotor  pointer to the rotor instance.
 *
 * \return  void
 */
void enigma_rotor_free(Rotor *rotor);

/**
 * \brief   A Random rotor
 *
 * \details This function accepts a sequence and returns a rotor instance that is randomized.
 *
 * \note    This function used malloc(3) to obtain memory. After you are done
 *          with that you have to call the `enigma_rotor_free` function to
 *          release memory to avoid memory leaks.
 *
 * \param   sequence  pointer to a Sequence instance
 *
 * \return  A randomized rotor.
 */
Rotor enigma_rotor_random(Sequence *sequence);

/**
 * \brief   Rotor main function
 *
 * \details It accepts sequence and rotor instance and input character
 *          if not `reverse`, then looks up `input` in `sequence` and
 *          returns front character from `rotor.sequence`, and if `reverse`
 *          lookup in `rotor.sequence` and returns front character from `sequence`.
 *
 * \param   sequence    pointer to the PlugboardList instance
 * \param   rotor       rotor instance to work on
 * \param   input       input character
 * \param   reverse     front to back or else
 *
 * \return  the changed form of the character.
 */
wchar_t enigma_rotor_action(Sequence *sequence, Rotor *rotor, wchar_t input, bool reverse);

/**
 * \brief   Rotates a rotor one time
 *
 * \details This function rotates the rotor's sequence.
 *          On the other hands, shifts sequence for one time
 *          to the right. Also, that last shifted character
 *          is stored in the first index of the sequence,
 *          so the length always remains the same.
 *
 * \param   rotor  pointer to rotor instance
 *
 * \return  void
 */
void enigma_rotor_rotation(Rotor *rotor);

/**
 * \brief   Rotates a list of rotors
 *
 * \details This function iterates through rotors and rotates them
 *          one time using the `enigma_rotor_rotation` function
 *
 * \param   rotors  pointer to the RotorList instance
 *
 * \return  void
 */
void enigma_rotors_rotate(RotorList *rotors);

#endif // _X_ROTOR
