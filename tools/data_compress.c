/*
** Q'n'D compression/decompression program using Pithy
** MIT License
** usage: pithy_compress c/d input output
*/

#include <stdio.h>
#include <stdlib.h>

#include "pithy.h"

int main(int argc, char **argv) {
    // Get arguments
    char mode;
    char *input_file;
    char *output_file;

    if (argc != 4) {
        printf("usage: pithy_compress c/d input output\n");
        return 1;
    }

    mode = argv[1][0];
    input_file = argv[2];
    output_file = argv[3];

    // Check mode
    if (mode != 'c' && mode != 'd') {
        printf("Wrong mode, use c for compress or d for decompress\n");
        printf("usage: pithy_compress c/d input output\n");
        return 1;
    }

    // Open files
    FILE *input = fopen(input_file, "rb");
    FILE *output = fopen(output_file, "wb");

    if (input == NULL || output == NULL) {
        printf("Failed to open files\n");
        return 1;
    }

    printf("Compressing %s to %s\n", input_file, output_file);

    // Get input size
    fseek(input, 0, SEEK_END);
    size_t input_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    // Allocate memory
    char *input_buffer = malloc(input_size);
    char *output_buffer = malloc(input_size);

    if (input_buffer == NULL || output_buffer == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    // Read input
    size_t ret = fread(input_buffer, 1, input_size, input);

    if (ret != input_size) {
        printf("Failed to read input\n");
        return 1;
    }

    // Compress/decompress
    size_t output_size;

    printf("Input size: %ld\n", input_size);
    if (mode == 'c') {
        printf("Compressing...\n");
        output_size = pithy_Compress(input_buffer, input_size, output_buffer,
                                     pithy_MaxCompressedLength(input_size), 9);
    } else {
        pithy_GetDecompressedLength(input_buffer, input_size, &output_size);
        output_buffer = realloc(output_buffer, output_size);
        pithy_Decompress(input_buffer, input_size, output_buffer, output_size);
    }

    printf("Output size: %ld\n", output_size);

    // Write output
    ret = fwrite(output_buffer, 1, output_size, output);

    if (ret != output_size) {
        printf("Failed to write output\n");
        return 1;
    }

    // Close files
    fclose(input);
    fclose(output);

    // Free memory
    free(input_buffer);
    free(output_buffer);

    return 0;
}
