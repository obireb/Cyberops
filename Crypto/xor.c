#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funksjon for å kryptere eller dekryptere en fil ved hjelp av XOR
void xor_encrypt_decrypt(const char *input_filename, const char *output_filename, const char *key) {
    // Åpner input-filen for lesing i binærmodus ("rb")
    FILE *input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        // Skriver en feilmelding og avslutter programmet hvis filen ikke kan åpnes
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // Åpner output-filen for skriving i binærmodus ("wb")
    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        // Skriver en feilmelding, lukker input-filen, og avslutter programmet hvis output-filen ikke kan åpnes
        perror("Error opening output file");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    // Finner lengden på nøkkelen som brukes til XOR
    size_t key_length = strlen(key);
    size_t i = 0; // Teller for å holde styr på hvilken del av nøkkelen som brukes
    int ch;       // Variabel for å lese ett tegn (byte) av gangen

    // Leser input-filen byte for byte og krypterer/dekrypterer med XOR
    while ((ch = fgetc(input_file)) != EOF) { 
        // XOR hver byte i filen med tilsvarende byte i nøkkelen (bruker modulo for å loope over nøkkelen)
        fputc(ch ^ key[i % key_length], output_file); 
        i++; // Gå videre til neste byte
    }

    // Lukker både input- og output-filene
    fclose(input_file);
    fclose(output_file);
    
    // Informerer brukeren om at behandlingen er ferdig
    printf("File successfully processed.\n");
}

int main(int argc, char *argv[]) {
    // Sjekker om programmet ble kjørt med riktig antall argumenter
    if (argc != 4) {
        // Hvis ikke, skriv ut en brukerveiledning og avslutt
        printf("Usage: %s <input file> <output file> <key>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Kaller funksjonen for kryptering/dekryptering med argumentene som ble gitt
    xor_encrypt_decrypt(argv[1], argv[2], argv[3]);

    // Returnerer suksess
    return EXIT_SUCCESS;
}
