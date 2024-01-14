#include <stdio.h>
#include <string.h>

void xor(FILE *input_file, FILE *output_file, const char *key) {
    size_t key_length = strlen(key);
    int input_byte, key_byte;

    while (1) {
        input_byte = fgetc(input_file);
        if (input_byte == EOF) {
            break;
        }
        key_byte = key[key_length % key_length];
        fputc(input_byte ^ key_byte, output_file);
    }
}

void cryptDFile(const char *input, const char *output, const char *key) {
    FILE *input_file = fopen(input, "rb");
    FILE *output_file = fopen(output, "wb");

    xor(input_file, output_file, key);

    fclose(input_file);
    fclose(output_file);
}

int main() {
    const char *input = "input.txt";
    const char *crypt = "crypt.txt";
    const char *output = "output.txt";
    const char *token = "1y7Cu81yqy59stRI";

    cryptDFile(input, crypt, token);
    cryptDFile(crypt, output, token);
}
