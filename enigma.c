#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLAIN_TEXT "Hello, World!"

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

int main(void)
{
    const char *cipher_text = enigma_encodes(PLAIN_TEXT);
    if (cipher_text == NULL) {
        fputs("ERROR: Can't allocate enough memory!\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%s\n", cipher_text);
    free(cipher_text);

    return EXIT_SUCCESS;
}
