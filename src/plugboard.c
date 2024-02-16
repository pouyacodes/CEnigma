#include <enigma/plugboard.h>

wchar_t enigma_plugboard(PlugboardList *plugboard, wchar_t c)
{
    if (plugboard->items == NULL) return c;

    da_foreach(plugboard) {
        if (plugboard->items[i].x == c) return plugboard->items[i].y;
        else if (plugboard->items[i].y == c) return plugboard->items[i].x;
    }

    return c;
}
