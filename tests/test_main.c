#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MODULES \
    MODULE(enigma) \
    MODULE(plugboard) \
    MODULE(sequence) \
    MODULE(rotor)

#define MODULE(name) bool (name) (void);
MODULES
#undef MODULE

typedef struct {
    const char *name;
    bool (*entrypoint)(void);
} Module;

static Module modules[] = {
    #define MODULE(name) {#name, (name)},
    MODULES
    #undef MODULE
};

#define ARRAY_SIZE(a) (sizeof (a) / sizeof (*a))

int main(void)
{
    bool result = true;

    int total_count = 0;

    for (size_t i = 0; i < ARRAY_SIZE(modules) && result; ++i) {
        Module current = modules[i];

        printf("---<%s>---\n", current.name);
        int failed_tests = current.entrypoint();
        if (failed_tests > 0) {
            ++total_count;
            result = false;
        }
        putchar('\n');
    }

    printf("Modules tested! (Failed: %d)\n", total_count);

    return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
