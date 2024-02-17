#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <unistd.h>
#include <getopt.h>

#include <enigma/enigma.h>

#define ENIGMA_DEFINE_LANGUAGE
#include <enigma/langs/en.h>

#include <da_list.h>

#include "config.h"

#define ARRAY_LEN(a) (sizeof a / sizeof *a)

#ifdef ENABLE_PLUGBOARD
static PlugPair plugpairs[] = {
    {.x = L'x', .y = L'y'},
    // ...
};

static PlugboardList plugboard = {
    .items = &plugpairs,
    .len   = ARRAY_LEN(plugpairs)
};
#endif

static RotorList alphabet_rotors;
static RotorList digit_rotors;
static RotorList punctuation_rotors;

static Enigma engine = {
    .language = &language,
#ifdef ENABLE_PLUGBOARD
    .plugboard = &plugboard,
#endif
    .alphabet_rotors    = &alphabet_rotors,
    .digit_rotors       = &digit_rotors,
    .punctuation_rotors = &punctuation_rotors
};

static struct option options[] = {
    {"from",   optional_argument, NULL, 'f'},
    {"to", optional_argument, NULL,     't'},
    {"help",   no_argument,       NULL, 'h'},
    {0},
};


#define LINE_BUFFER_SIZE 1024

void usage(const char *program_name, bool exit_status)
{
    FILE *out_file = exit_status == EXIT_SUCCESS ? stdout : stderr;
    fprintf(out_file,
        "Usage: %s [-f|--file [input_file]] [-o|--output [output_file]]\n"
        "\n"
        " [-f|--from [-|input_file]]    read input_file as input.\n"
        "                               default: stdin (-)\n"
        " [-t|--to [-|output_file]]     write output to output_file.\n"
        "                               default: stdout (-)\n"
        " [-h|--help]                   shows this help\n",
    program_name);
}

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

int repl(const char *program_name, FILE *input, FILE *output)
{
    int input_fd = fileno(input);
    if (input_fd < 0) {
        fprintf(stderr, "%s: ERROR: input is not a valid stream: %s\n", program_name, strerror(errno));
        return EXIT_FAILURE;
    }

    bool is_tty = input_fd == STDIN_FILENO && isatty(STDIN_FILENO) && isatty(STDERR_FILENO);

    wchar_t *plain_text = calloc(sizeof(wchar_t), LINE_BUFFER_SIZE);
    if (plain_text == NULL) {
        fprintf(stderr, "%s: ERROR: malloc(): %s\n", program_name, strerror(errno));
        return EXIT_FAILURE;
    }

    while (true) {
        if (is_tty) {
            fprintf(stderr, REPL_PROMPT);
            fflush(stderr);
        }

        if (fgetws(plain_text, LINE_BUFFER_SIZE, input) == NULL) break;

        wchar_t *cipher_text = enigma_encode(&engine, plain_text);
        if (cipher_text == NULL) {
            fprintf(stderr, "%s: enigma_encode(): %s\n", program_name, strerror(errno));
            return EXIT_FAILURE;
        }

        if (fputws(cipher_text, output) == EOF) break;
        free((void *)cipher_text);
    }


    free((void *)plain_text);

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    (void)argc;

    init_rotors();
    setlocale(LC_ALL, "");

    const char *in_filepath = NULL, *out_filepath = NULL;

    for (int op = 0; (op = getopt_long(argc, argv, "hf::t::", options, NULL)) != -1; ) {
        switch (op) {
            case 'f':
                if (optarg) in_filepath = optarg;
                else if (argv[optind] && argv[optind][0] != '-') in_filepath = argv[optind];
                break;
            case 't':
                if (optarg) out_filepath = optarg;
                else if (argv[optind] && argv[optind][0] != '-') out_filepath = argv[optind];
                break;
            case 'h':
                usage(argv[0], EXIT_SUCCESS);
                return EXIT_SUCCESS;
            case '?':
                usage(argv[0], EXIT_FAILURE);
                return EXIT_FAILURE;
        }
    }

    // Opening the input file
    FILE *input = in_filepath == NULL || strcmp(in_filepath, "-") == 0 ? stdin : fopen(in_filepath, "rb");
    if (input == NULL) {
        fprintf(stderr, "%s: ERROR: Could not open the input file: %s\n", argv[0], strerror(errno));
        return EXIT_FAILURE;
    }

    // Opening the output file
    FILE *output = out_filepath == NULL || strcmp(out_filepath, "-") == 0 ? stdout : fopen(out_filepath, "wb");
    if (output == NULL) {
        fprintf(stderr, "%s: ERROR: Could not open the output file: %s\n", argv[0], strerror(errno));
        return EXIT_FAILURE;
    }

    return repl(argv[0], input, output);
}
