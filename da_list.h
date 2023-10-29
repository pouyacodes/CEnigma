#ifndef _X_DA_LIST
#define _X_DA_LIST

#ifndef DA_INIT_CAP
#define DA_INIT_CAP 2
#endif

#ifndef DA_REALLOC
#define DA_REALLOC(ptr, size) realloc(ptr, size)
#endif

#ifndef DA_FREE
#define DA_FREE(ptr) free(ptr)
#endif

#ifndef DA_ASSERT
#define DA_ASSERT(a) assert(a)
#endif

#define da_append(da, item) do { \
        assert((da) != NULL); \
        if ((da)->cap >= (da)->len) { \
            (da)->cap = (da)->cap == 0 ? DA_INIT_CAP : (da)->cap * 2;\
            (da)->items = DA_REALLOC((da)->items, sizeof((da)->items[0]) * sizeof((da)->cap));\
            assert((da)->items != NULL);\
        } \
        (da)->items[(da)->len++] = (item); \
    } while (0)

#define da_free(da) DA_FREE((da)->items)

#define DYNAMIC_ARRAY(t) \
    size_t cap;\
    size_t len;\
    t *items;

#endif // _X_DA_LIST
