#ifndef _X_DA_LIST
#define _X_DA_LIST

#include <stddef.h>

#ifndef DA_INIT_CA
#define DA_INIT_CAP 2
#endif

#ifndef DA_REALLOC
#    include <stdlib.h>
#    define DA_REALLOC(ptr, size) realloc(ptr, size)
#endif

#ifndef DA_FREE
#    include <stdlib.h>
#    define DA_FREE(ptr) free(ptr)
#endif

#ifndef DA_ASSERT
#    include <assert.h>
#    define DA_ASSERT(a) assert(a)
#endif

#define da_append(da, item) do { \
        DA_ASSERT((da) != NULL); \
        if ((da)->cap == (da)->len) { \
            (da)->cap = (da)->cap == 0 ? DA_INIT_CAP : (da)->cap * 2;\
            (da)->items = DA_REALLOC((da)->items, sizeof((da)->items[0]) * sizeof((da)->cap));\
            DA_ASSERT((da)->items != NULL);\
        } \
        (da)->items[(da)->len++] = (item); \
    } while (0)

#define da_free(da) DA_FREE((da)->items)

#define da_foreach(da) for (size_t i = 0; i < (da)->len; ++i)

#define da_rev_foreach(da) for (ssize_t i = (da)->len - 1; i >= 0; --i)

#define DYNAMIC_ARRAY(t) \
    size_t cap;\
    size_t len;\
    t *items;

#endif // _X_DA_LIST
