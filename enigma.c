#include <assert.h>
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "da_list.h"

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

#define PLAIN_TEXT "Hello, World!"
#define VERSION "1.0"
#define VERSION_INFO \
    "CEnigma: Enigma machine in C (Simulation), version " VERSION "\n" \
    "License MIT: Copyright (c) 2023 PouyaCodes\n" \
    "Homepage: https://github.com/pouyacodes/CEnigma\n"

#define ARRAY_LEN(a) (sizeof a / sizeof *a)

#define DIGITS_LENGTH 10
#define ALPHA_LENGTH 26
#define ALPHANUM_LENGTH (DIGITS_LENGTH + ALPHA_LENGTH)

typedef struct {
    char sequence[ALPHANUM_LENGTH];
    size_t rotation;
} Rotor;

static Rotor rotors[] = {
    {
        .rotation = 0,
        .sequence = { 
            'c', 'p', 'j', 'd', 'e', 'z', 'v', 'h', 'n',
            'o', 'x', 'b', 't', 'g', 'a', 's', 'y', 'q',
            'f', 'r', 'k', 'i', 'm', 'l', 'u', 'w', '2',
            '0', '6', '7', '4', '9', '5', '1', '8', '3',
        }
    },
    {
        .rotation = 0,
        .sequence = {
            'm', 'e', 'z', 'r', 'n', 'u', 'g', 'f', 'k',
            'j', 'b', 'l', 't', 'v', 'x', 'w', 'q', 'd',
            'y', 'h', 's', 'a', 'o', 'p', 'c', 'i', '1',
            '4', '6', '2', '5', '9', '0', '3', '8', '7',
        }
    },
    {
        .rotation = 0,
        .sequence = {
            'i', 'v', 'k', 'o', 'g', 'y', 'p', 'm', 'd',
            'j', 'w', 'b', 'z', 'x', 'r', 'f', 'l', 's',
            'e', 'n', 'u', 'c', 'h', 't', 'q', 'a', '8',
            '3', '1', '4', '5', '0', '7', '6', '2', '9',
        }
    }
};

void rotor_rotate(char sequence[static ALPHANUM_LENGTH])
{
    char first = sequence[0];

    for (size_t i = 0; i < ALPHA_LENGTH - 1; ++i) {
        sequence[i] = sequence[i + 1];
    }

    sequence[ALPHA_LENGTH - 1] = first;

    char first_digit = sequence[ALPHA_LENGTH];
    for (size_t i = ALPHA_LENGTH; i < ALPHANUM_LENGTH - 1; ++i) {
        sequence[i] = sequence[i + 1];
    }

    sequence[ALPHANUM_LENGTH - 1] = first_digit;
}

int rotor_get_pos(const char sequence[static ALPHANUM_LENGTH], char needle)
{
    for (size_t i = 0; i < ALPHANUM_LENGTH; ++i) {
        if (sequence[i] == needle) return i;
    }

    return -1;
}

typedef struct {
    char x;
    char y;
} PlugPair;

typedef struct {
    DYNAMIC_ARRAY(PlugPair)
} PlugboardList;

static PlugboardList plugboard;

void init_plugboard(const char *plugboard_str)
{
    assert(plugboard_str != NULL);

    char *plugboard_dup = strdup(plugboard_str);
    char *part = strtok(plugboard_dup, ",");
    while (part != NULL) {
        PlugPair pair = {.x = part[0], .y = part[1]};
        da_append(&plugboard, pair);
        part = strtok(NULL, ",");
    }

    free(plugboard_dup);
}

char enigma_plugboard(char c)
{
    if (plugboard.items == NULL) return c;

    for (size_t i = 0; i < plugboard.len; ++i) {
        if (plugboard.items[i].x == c) return plugboard.items[i].y;
        else if (plugboard.items[i].y == c) return plugboard.items[i].x;
    }

    return c;
}

void enigma_rotor_rotate(void)
{
    bool next_update = false;

    for (size_t i = 0; i < ARRAY_LEN(rotors); ++i) {
        rotor_rotate(rotors[i].sequence);
        ++rotors[i].rotation;
        if (rotors[i].rotation == ALPHANUM_LENGTH) {
            rotors[i].rotation = 0;
            next_update = true;
        } else {
            next_update = false;
        }

        if (!next_update) return;
    }
}

char enigma_reflector(char c)
{
    if (!isalnum(c)) return c;
    return isdigit(c) ? '9' - c + '0' : 'z' - c + 'a';
}

char enigma_encodec(char c)
{
    if (!isalnum(c)) return c;

    char ret = tolower(c);

    ret = enigma_plugboard(ret);

    for (size_t i = 0; i < ARRAY_LEN(rotors); ++i) {
        if (ret - 'a' < 0)
            ret = rotors[i].sequence[ALPHA_LENGTH + (ret - '0')];
        else
            ret = rotors[i].sequence[ret - 'a'];
    }

    ret = enigma_reflector(ret);

    for (int i = ARRAY_LEN(rotors) - 1; i >= 0; --i) {
        if (ret - 'a' < 0)
            ret = '0' + (rotor_get_pos(rotors[i].sequence, ret) - ALPHA_LENGTH);
        else
            ret = 'a' + rotor_get_pos(rotors[i].sequence, ret);
    }

    enigma_rotor_rotate();

    ret = enigma_plugboard(ret);

    return isupper(c) ? toupper(ret) : ret;
}

const char *enigma_encodes(const char *str)
{
    assert(str != NULL);

    size_t len = strlen(str);
    char *buffer = calloc(sizeof(char), len + 1);
    if (buffer == NULL) return NULL;

    for (size_t i = 0; i < len; ++i) {
        buffer[i] = enigma_encodec(str[i]);
    }

    buffer[len] = '\0';
    return buffer;
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

static struct option opts[] = {
    {"text",      required_argument, 0, 't'},
    {"plugboard", required_argument, 0, 'p'},
    {"usage",     no_argument,       0, 'h'},
    {"help",      no_argument,       0, 'h'},
    {"version",   no_argument,       0, 'v'},
    {0,           0,                 0,  0},
};

int main(int argc, char *argv[])
{
    const char *plain_text = PLAIN_TEXT;

    int c;
    while ((c = getopt_long(argc, argv, "t:p:hv", opts, NULL)) != -1) {
        switch (c) {
            case 'h':
                usage(argv[0], EXIT_SUCCESS);
                return EXIT_SUCCESS;
            case 'v':
                puts(VERSION_INFO);
                return EXIT_SUCCESS;
            case '?':
                usage(argv[0], EXIT_FAILURE);
                return EXIT_FAILURE;
            case 't':
                plain_text = optarg;
                break;
            case 'p':
                init_plugboard(optarg);
                break;
            case -1:
                break;
        }
    }

    const char *cipher_text = enigma_encodes(plain_text);

    if (cipher_text == NULL) {
        fputs("ERROR: Can't allocate enough memory!\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%s\n", cipher_text);
    da_free(&plugboard);
    free(cipher_text);

    return EXIT_SUCCESS;
}
