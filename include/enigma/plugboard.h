#ifndef _X_PLUGBOARD_
#define _X_PLUGBOARD_

#include <stddef.h>
#include "da_list.h"

typedef struct PlugPair {
    wchar_t x;
    wchar_t y;
} PlugPair;

typedef struct PlugboardList {
    DYNAMIC_ARRAY(PlugPair)
} PlugboardList;

wchar_t enigma_plugboard(PlugboardList *plugboard, wchar_t c);

#endif // _X_PLUGBOARD_
