#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>

#include <enigma.h>
#include "da_list.h"

#define PLAIN_TEXT L"Hello, World!"
#define VERSION "1.0"
#define VERSION_INFO \
    "CEnigma: Enigma machine in C (Simulation), version " VERSION "\n" \
    "License MIT: Copyright (c) 2023 PouyaCodes\n" \
    "Homepage: https://github.com/pouyacodes/CEnigma\n"

#define ARRAY_LEN(a) (sizeof a / sizeof *a)

#if !defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 200809L
char *strdup(const char *str)
{
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    char *ret = malloc(sizeof(char) * len);
    if (ret != NULL) {
        ret = memcpy(ret, str, len + 1);
    }

    return ret;
}
#endif

typedef struct Error {
    bool result;
    const char *error_str;
};

static PlugboardList plugboard;

void init_plugboard(const char *plugboard_str, Error *err)
{
    assert(plugboard_str != NULL);

    err->error_str = NULL;
    err->result = true;

    char *plugboard_dup = strdup(plugboard_str);
    char *part = strtok(plugboard_dup, ",");
    while (part != NULL) {
        wchar_t pair[2] = {};
        size_t len = strlen(part), parsed_bytes = 0;
        mbstate_t ps = {};

        for (size_t i = 0; i < 2; ++i) {
            size_t ret = mbrtowc(pair + i, part + parsed_bytes, len - parsed_bytes, &ps);
            if ((size_t)-1 == ret) {
                // fprintf(stderr, "%s: mbrtowc(): %s", argv[0], strerror(errno));
                err->result = false;
                err->error_str = strerror(errno);
                goto defer;
            } else if ((size_t)-2 == ret) {
                // fprintf(stderr, "%s: mbrtowc(): Couldn't parse a complete multibyte character\n", argv[0]);
                err->result = false;
                err->error_str = "Couldn't parse a complete multibyte character";
                goto defer;
            } else if (ret == 0) {
                // fprintf(stderr, "%s: ERROR: Couldn't parse a complete pair\n", argv[0]);
                err->result = false;
                err->error_str = "Couldn't parse a complete pair";
                goto defer;
            }

            parsed_bytes += ret;
        }

        PlugPair plug_pair = {.x = pair[0], .y = pair[1]};
        da_append(&plugboard, plug_pair);
        part = strtok(NULL, ",");
    }

defer:
    free(plugboard_dup);
}

void usage(const char *program_name, int exit_status)
{
    FILE *stream = stdout;
    if (exit_status != EXIT_SUCCESS) stream = stderr;

    fprintf(stream,
            "Usage: %s [OPTION]...\n"
            "\n"
            "CEnigma is a simple program that simulates the Enigma engine.\n"
            "\n"
            "Options: \n"
            "   -t|--text <plaintext>       encode <plaintext> as a plain text instead\n"
            "                               instead of default text. (Default: Hello, World!)\n"
            "   -p|--plugboard <plugpairs>  a set of pair chars separated by a ',' character to\n"
            "                               use as plugboard for example: xy,wa,sw\n"
            "                               the engine doesn't use plugboard by default\n"
            "\n"
            VERSION_INFO,
    program_name);
}

#if 0
int iswalpha(wint_t wc);
int iswdigit(wint_t wc);
int iswpunct(wint_t wc);
int iswupper(wint_t wc);
wint_t towupper(wint_t wc);
wint_t towlower(wint_t wc);
#endif

size_t strlen_mb(const char *ptr)
{
    size_t result = 0;
    const char* end = ptr + strlen(ptr);
    mblen(NULL, 0);

    while (ptr < end) {
        int next = mblen(ptr, end - ptr);
        if (next == -1) {
           perror("strlen_mb");
           break;
        }
        ptr += next;
        ++result;
    }

    return result;
}

static struct option opts[] = {
    {"text",      required_argument, 0, 't'},
    {"plugboard", required_argument, 0, 'p'},
    {"usage",     no_argument,       0, 'h'},
    {"help",      no_argument,       0, 'h'},
    {"version",   no_argument,       0, 'v'},
    {0,           0,                 0,  0 },
};


int main(int argc, char *argv[])
{
    Language language = {
        .alphabet    = L"abcdefghijklmnopqrstuvwxyz",
        .digit       = L"0123456789",
        .punctuation = L"!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~",
        .isalpha     = iswalpha,
        .isdigit     = iswdigit,
        .ispunct     = iswpunct,
        .isupper     = iswupper,
        .tolower     = towlower,
        .toupper     = towupper
    };

    Enigma engine = { .language = &language, .plugboard = &plugboard };

    setlocale(LC_ALL, "");
    const wchar_t *plain_text = PLAIN_TEXT;

    Error err = {};
    int c;
    while ((c = getopt_long(argc, argv, "t:p:hv", opts, NULL)) != -1) {
        switch (c) {
            case 'h': {
                usage(argv[0], EXIT_SUCCESS);
                return EXIT_SUCCESS;
            }
            case 'v': {
                puts(VERSION_INFO);
                return EXIT_SUCCESS;
            }
            case '?': {
                usage(argv[0], EXIT_FAILURE);
                return EXIT_FAILURE;
            }
            case 't': {
                size_t len = strlen_mb(optarg);
                plain_text = malloc(sizeof(wchar_t) * len);
                if (plain_text == NULL) {
                    fprintf(stderr, "%s: malloc(): %s\n", argv[0], strerror(errno));
                    return EXIT_FAILURE;
                }
                size_t read_len = mbstowcs(plain_text, optarg, len);
                if (read_len < len) {
                    fprintf(stderr, "%s: mbstowcs(): %s\n", argv[0], strerror(errno));
                    return EXIT_FAILURE;
                }
                break;
            }
            case 'p': {
                parse_plugpair(optarg, &err);
                if (!err->result) { // TODO: Handle error somehow
                }
                break;
            }
            case -1:
                break;
        }
    }

    wchar_t *cipher_text = enigma_encode(&engine, plain_text);
    if (cipher_text == NULL) {
        fprintf(stderr, "%s: enigma_encode(): %s\n", argv[0], strerror(errno));
        return EXIT_FAILURE;
    }

    printf("%ls\n", cipher_text);
    da_free(&plugboard);
    free(cipher_text);

    return EXIT_SUCCESS;
}
