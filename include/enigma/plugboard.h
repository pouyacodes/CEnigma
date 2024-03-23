#ifndef _X_PLUGBOARD_
#define _X_PLUGBOARD_

#include <stddef.h>
#include "da_list.h"

/**
 * \brief   Plugboard pair
 *
 * \details A pair of wchar_t characters that are used in the plugboard.
 *          machine uses `y` (or `x`), for every occurrence of `x` (or `y`) in input/output.
 *
 * \member x one end
 * \member y other end
*/
typedef struct PlugPair {
    wchar_t x;
    wchar_t y;
} PlugPair;

/**
 * \brief   Represent Plugboard
 *
 * \details List of Plugboard pairs.
 *
 * \member  items Pointer to `PlugPair` instances
 * \member  len   length of List
 * \memebr  cap   capacity of List
 */
typedef struct PlugboardList {
    DYNAMIC_ARRAY(PlugPair)
} PlugboardList;

/**
 * \brief   Plugboard function
 *
 * \details This function accepts the list of plugpairs and a character.
 *          If the character found in the list returns another character.
 *
 * \param   plugboard  pointer to the PlugboardList instance
 * \param   c          a character
 *
 * \return  the changed form of the character.
 */
wchar_t enigma_plugboard(PlugboardList *plugboard, wchar_t c);

#endif // _X_PLUGBOARD_
