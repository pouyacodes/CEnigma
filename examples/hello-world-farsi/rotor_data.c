#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <enigma/rotor.h>
#include <enigma/langs/fa.h>

#include "config.h"

#define LOG_INFO(format, ...) fprintf(stderr, "%s: INFO: " format "\n", argv[0]__VA_OPT__(,) __VA_ARGS__)

void serialize_rotor(Rotor *rotor, FILE *outfile)
{
    if (rotor->sequence.len > 0) {
        const size_t seq_len = sizeof(rotor->sequence.len),
                     val_len = rotor->sequence.len * sizeof(*rotor->sequence.values),
                     rot_len = sizeof(rotor->rotations);

        const size_t out_len = seq_len + val_len + rot_len + 1; // one extra byte for separator

        char *data_serialized = calloc(out_len, sizeof(char));
        assert(data_serialized != NULL);

        char *temp = data_serialized;

        temp = memcpy(temp, (void *)&rotor->sequence.len, seq_len);
        temp = memcpy(temp + seq_len, (void *)rotor->sequence.values, val_len);
        temp = memcpy(temp + val_len, (void *)&rotor->rotations, rot_len);
        *(temp + rot_len) = '\n'; // separator

        size_t written_len = fwrite(data_serialized, sizeof(char), out_len, outfile);
        assert(written_len == out_len);

        free(data_serialized);
    }
}

int main(int argc, char *argv[])
{
    (void)argc;

    srand(time(NULL));

    FILE *outfile = fopen(ROTOR_DATA_PATH, "wb");
    if (outfile == NULL) {
        fprintf(stderr, "%s: fopen(): %s\n", argv[0], strerror(errno));
        return EXIT_FAILURE;
    }

    LOG_INFO("Working with %s file", ROTOR_DATA_PATH);

    LOG_INFO("Serializing alpha_rotor");
    for (size_t i = 0; i < ROTOR_LEN; ++i) {
        Rotor alpha_rotor = enigma_rotor_random(&alphabets_sequence);
        serialize_rotor(&alpha_rotor, outfile);
        enigma_rotor_free(&alpha_rotor);
    }

    LOG_INFO("Serializing digit_rotor");
    for (size_t i = 0; i < ROTOR_LEN; ++i) {
        Rotor digit_rotor = enigma_rotor_random(&digits_sequence);
        serialize_rotor(&digit_rotor, outfile);
        enigma_rotor_free(&digit_rotor);
    }

    LOG_INFO("Serializing punct_rotor");
    for (size_t i = 0; i < ROTOR_LEN; ++i) {
        Rotor punct_rotor = enigma_rotor_random(&punctuations_sequence);
        serialize_rotor(&punct_rotor, outfile);
        enigma_rotor_free(&punct_rotor);
    }

    fclose(outfile);
    LOG_INFO("Serializing Done!");

    return EXIT_SUCCESS;
}
