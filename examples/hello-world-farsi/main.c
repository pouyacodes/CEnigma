#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include <enigma/enigma.h>

#define ENIGMA_DEFINE_LANGUAGE
#include <enigma/langs/fa.h>

#include <da_list.h>

#include "config.h"

static RotorList alphabet_rotors;
static RotorList digit_rotors;
static RotorList punctuation_rotors;

void init_rotors(void)
{
    FILE *fp = fopen(ROTOR_DATA_PATH, "rb");
    if (fp == NULL) return;

    static RotorList *lists[3] = { &alphabet_rotors, &digit_rotors, &punctuation_rotors };

    for (int r = 0; r < 3 && !feof(fp); ++r) {
        for (size_t i = 0; i < ROTOR_LEN; ++i) {
            size_t len = 0;
            fread(&len, sizeof(size_t), 1, fp);

            wchar_t *values = calloc(len, sizeof(wchar_t));
            fread(values, sizeof(wchar_t), len, fp);

            size_t rotations = 0;
            fread(&rotations, sizeof(size_t), 1, fp);

            (void)fgetc(fp); // Read & ignore the separator ('\n')

            Rotor rotor = {
                .sequence = {.values = values, .len = len},
                .rotations = rotations,
            };

            da_append(lists[r], rotor);
        }
    }

    fclose(fp);
}

int main(int argc, char **argv)
{
    (void)argc;

    init_rotors();
    const wchar_t *plain_text = L"سلام، دنیا!";

    Enigma engine = {
        .language = &language,
        .alphabet_rotors    = &alphabet_rotors,
        .digit_rotors       = &digit_rotors,
        .punctuation_rotors = &punctuation_rotors
    };

    setlocale(LC_ALL, "");

    wchar_t *cipher_text = enigma_encode(&engine, plain_text);
    if (cipher_text == NULL) {
        fprintf(stderr, "%s: enigma_encode(): %s\n", argv[0], strerror(errno));
        return EXIT_FAILURE;
    }

    printf("%ls\n", cipher_text);
    free((void *)cipher_text);

    return EXIT_SUCCESS;
}
