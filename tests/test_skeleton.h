#ifndef _X_TEST_SKELETON
#define _X_TEST_SKELETON

#include <stdbool.h>
#include <string.h>
#include <wchar.h>

#define __MA_CONCAT(a, b) a##b
#define _CONCAT(a, b) __MA_CONCAT(a, b)

#define _GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define CASE(...) _GET_MACRO(__VA_ARGS__, CASE_NAME_SETUP_TEARDOWN, CASE_NAME_SETUP, CASE_NAME)(__VA_ARGS__)

#define TEST_CASE_NAME(name) _CONCAT(TEST_MODULE, _##name##_test)
#define TEST_CASE(name) void TEST_CASE_NAME(name) (__attribute__((unused)) Result *r)

#define TEST_CASE_SETUP_NAME(name) _CONCAT(TEST_CASE_NAME(name), _setup)
#define TEST_CASE_SETUP(name) void TEST_CASE_SETUP_NAME(name) (void)

#define TEST_CASE_TEARDOWN_NAME(name) _CONCAT(TEST_CASE_NAME(name), _teardown)
#define TEST_CASE_TEARDOWN(name) void TEST_CASE_TEARDOWN_NAME(name) (void)

typedef enum {
    TEST_NUMERIC_MATCH,
    TEST_FLOAT_MATCH,

    TEST_CHRACTER_MATCH,
    TEST_WIDE_CHRACTER_MATCH,

    TEST_STRING_MATCH,
    TEST_WIDE_STRING_MATCH,

    TEST_BOOL_MATCH,
} ResultStatus;

typedef union {
    int xint;
    float xfloat;

    char xchar;
    wchar_t xwchar_t;

    const char *xstring;
    const wchar_t *xwstring;

    bool xbool;
} Types;

typedef struct {
    ResultStatus status;

    Types actual;
    Types expected;

    const char *filename;
    int line;

    bool passed;
} Result;

#define NUMERIC_EQUAL(lhs, rhs) ((lhs) == (rhs))
#define STR_EQUAL(lhs, rhs) (strcmp((lhs), (rhs)) == 0)
#define WSTR_EQUAL(lhs, rhs) (wcscmp((lhs), (rhs)) == 0)

#define ABS(a) ((a) < 0 ? -(a) : (a))
#define FLOAT_EQUAL(lhs, rhs) (ABS(lhs - rhs) < 1e-10)

#define _ASSERT_TEST(act, expec, comp_func, field_name, stat) \
    do { \
        r->status = (stat); \
        r->actual.field_name = (act); \
        r->expected.field_name = (expec); \
        r->line = __LINE__; \
        r->filename = __FILE__; \
        r->passed = comp_func(r->actual.field_name, r->expected.field_name); \
        if (!r->passed) return; \
   } while (0)

#define ASSERT_EQUAL_NUMERIC(actual, expected) _ASSERT_TEST(actual, expected, NUMERIC_EQUAL, xint, TEST_NUMERIC_MATCH)
#define ASSERT_EQUAL_FLOAT(actual, expected) _ASSERT_TEST(actual, expected, FLOAT_EQUAL, xfloat, TEST_FLOAT_MATCH)

#define ASSERT_EQUAL_CHARATCER(actual, expected) _ASSERT_TEST(actual, expected, NUMERIC_EQUAL, xchar, TEST_CHRACTER_MATCH)
#define ASSERT_EQUAL_WIDE_CHARACTER(actual, expected) _ASSERT_TEST(actual, expected, NUMERIC_EQUAL, xwchar_t, TEST_WIDE_CHRACTER_MATCH)

#define ASSERT_EQUAL_STRING(actual, expected) _ASSERT_TEST(actual, expected, STR_EQUAL, xstring, TEST_STRING_MATCH)
#define ASSERT_EQUAL_WIDE_STRING(actual, expected) _ASSERT_TEST(actual, expected, WSTR_EQUAL, xwstring, TEST_WIDE_STRING_MATCH)

#define ASSERT_EQUAL_BOOL(actual, expected) _ASSERT_TEST(actual, expected, NUMERIC_EQUAL, xbool, TEST_BOOL_MATCH)
#define ASSERT_EQUAL_TRUE(expr) ASSERT_EQUAL_BOOL(expr, true)
#define ASSERT_EQUAL_FALSE(expr) ASSERT_EQUAL_BOOL(expr, false)

#endif // _X_TEST_SKELETON
