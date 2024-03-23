#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#ifndef TEST_MODULE
#error "ERROR: Module name is not defined!"
#endif

#ifndef CASES
#error "ERROR: Test cases is not defined!"
#endif

#include "test_skeleton.h"

#define CASE_NAME(name) TEST_CASE(name);

#define CASE_NAME_SETUP(name, _2) \
                CASE_NAME(name) \
                TEST_CASE_SETUP(name);

#define CASE_NAME_SETUP_TEARDOWN(name, _2, _3) \
                CASE_NAME_SETUP(name, _2) \
                TEST_CASE_TEARDOWN(name);


CASES

#undef CASE_NAME
#undef CASE_NAME_SETUP
#undef CASE_NAME_SETUP_TEARDOWN

static Result case_result;

typedef struct {
    const char *name;
    void (*setup)(void);
    void (*tester)(Result *result);
    void (*teardown)(void);
} Test;

static Test cases[] = {

    #define CASE_NAME(n)  \
            { \
                .name = #n, \
                .tester = TEST_CASE_NAME(n), \
                .setup = NULL, \
                .teardown = NULL \
            },

    #define CASE_NAME_SETUP(n, _2) \
            { \
                .name = #n, \
                .tester = TEST_CASE_NAME(n), \
                .setup = TEST_CASE_SETUP_NAME(n), \
                .teardown = NULL \
            },

    #define CASE_NAME_SETUP_TEARDOWN(n, _2, _3) \
            { \
                .name = #n, \
                .tester = TEST_CASE_NAME(n), \
                .setup = TEST_CASE_SETUP_NAME(n), \
                .teardown = TEST_CASE_TEARDOWN_NAME(n) \
            },

    CASES
    #undef CASE_NAME
    #undef CASE_NAME_SETUP
    #undef CASE_NAME_SETUP_TEARDOWN
};

#define ARRAY_LEN(a) ((sizeof(a)) / (sizeof (*a)))

static_assert(ARRAY_LEN(cases) > 0, "Test cases must not be empty");

extern int TEST_MODULE(void)
{
    int failed_tests = 0;

    for (size_t i = 0; i < ARRAY_LEN(cases); ++i) {
        Test current = cases[i];
        assert(current.tester != NULL);

        memset(&case_result, 0, sizeof(Result));
        case_result.passed = true;

        printf("\t- %s ", current.name);
        fflush(stdout);

        if (current.setup != NULL) current.setup();

        current.tester(&case_result);

        if (case_result.passed) {
            printf("(OK)\n");
        } else {
            printf("(FAILED) (%s:%d)\n", case_result.filename, case_result.line);
            ++failed_tests;
        }

        switch (case_result.status) {
            case TEST_NUMERIC_MATCH:
                printf("\t\texpected: %d\n", case_result.expected.xint);
                printf("\t\tactual: %d\n", case_result.actual.xint);
                break;
            case TEST_FLOAT_MATCH:
                printf("\t\texpected: %f\n", case_result.expected.xfloat);
                printf("\t\tactual: %f\n", case_result.actual.xfloat);
                break;
            case TEST_CHRACTER_MATCH:
                printf("\t\texpected: %c\n", case_result.expected.xchar);
                printf("\t\tactual: %c\n", case_result.actual.xchar);
                break;
            case TEST_WIDE_CHRACTER_MATCH:
                setlocale(LC_ALL, "");
                printf("\t\texpected: %lc\n", case_result.expected.xwchar_t);
                printf("\t\tactual: %lc\n", case_result.actual.xwchar_t);
                break;
            case TEST_STRING_MATCH:
                printf("\t\texpected: \"%s\"\n", case_result.expected.xstring);
                printf("\t\tactual: \"%s\"\n", case_result.actual.xstring);
                break;
            case TEST_WIDE_STRING_MATCH:
                setlocale(LC_ALL, "");
                printf("\t\texpected: \"%ls\"\n", case_result.expected.xwstring);
                printf("\t\tactual: \"%ls\"\n", case_result.actual.xwstring);
                break;
            case TEST_BOOL_MATCH:
                printf("\t\texpected: (%s)\n", case_result.expected.xbool ? "true" : "false");
                printf("\t\tactual: (%s)\n", case_result.actual.xbool ? "true" : "false");
                break;
        }

        if (current.teardown != NULL) current.teardown();
    }

    return failed_tests;
}
