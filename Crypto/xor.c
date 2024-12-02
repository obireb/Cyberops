#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void xor_encrypt_decrypt(const char *input_filename, const char *output_filename, const char *key) {
    FILE *input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    size_t key_length = strlen(key);
    size_t i = 0;
    int ch;

    // Read input file byte by byte and XOR with the key
    while ((ch = fgetc(input_file)) != EOF) {
        fputc(ch ^ key[i % key_length], output_file);
        i++;
    }

    fclose(input_file);
    fclose(output_file);
    printf("File successfully processed.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input file> <output file> <key>\n", argv[0]);
        return EXIT_FAILURE;
    }

    xor_encrypt_decrypt(argv[1], argv[2], argv[3]);
    return EXIT_SUCCESS;
}

