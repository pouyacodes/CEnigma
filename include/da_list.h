#ifndef _X_DA_LIST
#define _X_DA_LIST

#include <stddef.h>

/**
 * \brief Initial Capacity of the da_list
 */
#ifndef DA_INIT_CA
#define DA_INIT_CAP 2
#endif


/**
 * \brief   Allocator function
 *
 * \details By default this library uses `realloc` function
 *          from libc (glibc) to allocate memory. You can
 *          replace this macro with your custom allocator.
 */
#ifndef DA_REALLOC
#    include <stdlib.h>
#    define DA_REALLOC(ptr, size) realloc(ptr, size)
#endif


/**
 * \brief   Deallocator function
 *
 * \details By default this library uses `free` function
 *          from libc (glibc) to release memory. You can
 *          replace this macro with your custom deallocator.
 */
#ifndef DA_FREE
#    include <stdlib.h>
#    define DA_FREE(ptr) free(ptr)
#endif

/**
 * \brief   Assertion function
 *
 * \details By default this library uses `assert` macro
 *          from libc (glibc) to handle errors. You can
 *          replace this macro with your custom deallocator.
 */
#ifndef DA_ASSERT
#    include <assert.h>
#    define DA_ASSERT(a) assert(a)
#endif

/**
 * \brief   Append `item` to the dynamic array
 *
 * \details This function-like macro is used to push back item
 *          to the dynamic array. Capacity increases exponentially.
 *
 * \param   da      Pointer to the dynamic array instance
 * \param   item    Item to push
 */
#define da_append(da, item) do { \
        DA_ASSERT((da) != NULL); \
        if ((da)->cap == (da)->len) { \
            (da)->cap = (da)->cap == 0 ? DA_INIT_CAP : (da)->cap * 2;\
            (da)->items = DA_REALLOC((da)->items, sizeof((da)->items[0]) * sizeof((da)->cap));\
            DA_ASSERT((da)->items != NULL);\
        } \
        (da)->items[(da)->len++] = (item); \
    } while (0)


/**
 * \brief   Free the dynamic array
 *
 * \details deallocates items and frees dynamic array
 *
 * \param   da  Pointer to the dynamic array instance
 */
#define da_free(da) DA_FREE((da)->items)

/**
 * \brief   Iterating through items
 *
 * \details This macro expands to a simple for statement that
 *          used for iterating.
 *
 * \param   da  Pointer to the dynamic array instance
 *
 */
#define da_foreach(da) for (size_t i = 0; i < (da)->len; ++i)

/**
 * \brief   Iterating through items in reverse order
 *
 * \details This macro expands to a simple for statement that
 *          used for iterating in reverse order.
 *
 * \param   da Pointer to the dynamic array instance
 *
 */
#define da_rev_foreach(da) for (ssize_t i = (da)->len - 1; i >= 0; --i)

/**
 * \brief   Required fields for turning a structure to dynamic array
 *
 * \details Every structure that needs to be a List, has to define these three fields.
 *          This convenient macro expands to those three fields and
 *          is used inside the dynamic array macros.
 *
 * \param   t   type of items
 */
#define DYNAMIC_ARRAY(t) \
    size_t cap;\
    size_t len;\
    t *items;

#endif // _X_DA_LIST
