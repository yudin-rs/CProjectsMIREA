#include <stdio.h>
#include <string.h>

void xor(const char *input, const char *key) {

    FILE *input_file = fopen(input, "rb+");

    size_t key_length = strlen(key);
    int input_byte, key_byte;

    while (1) {
        input_byte = fgetc(input_file);
        if (input_byte == EOF) {
            break;
        }
        key_byte = key[key_length % key_length];
        fseek(input_file, -1, SEEK_CUR);
        fputc(input_byte ^ key_byte, input_file);
        fflush(input_file);
    }
    fclose(input_file);
}

int main(int argc, char *argv[]) {
    const char *input = argv[1];
    const char *token = argv[2];

    xor(input, token);
    printf("Успешно");
}