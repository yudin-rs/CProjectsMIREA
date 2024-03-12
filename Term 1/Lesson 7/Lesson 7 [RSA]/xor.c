#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *generateKey(size_t length, const char *table) {
    const size_t charset_size = strlen(table);
    srand((unsigned int) time(NULL));
    char *random_string = (char *) malloc(length + 1);
    for (size_t i = 0; i < length; i++) {
        int index = rand() % charset_size;
        random_string[i] = table[index];
    }
    random_string[length] = '\0';
    return random_string;
}

void xor(const char *input, const char *key) {
    FILE *input_file = fopen(input, "rb+");
    size_t key_length = strlen(key);
    int input_byte, key_byte;
    while ((input_byte = fgetc(input_file)) != EOF) {
        key_byte = key[key_length % key_length];
        fseek(input_file, -1, SEEK_CUR);
        fputc(input_byte ^ key_byte, input_file);
        fflush(input_file);
    }
    fclose(input_file);
}

char *cryptKey(const char *data, const char *table) {
    size_t result_length = strlen(data) * 3 + 1;
    char *result = (char *) malloc(result_length);
    result[0] = '\0';
    for (size_t i = 0; data[i] != '\0'; i++) {
        char currentChar = data[i];
        const char *charPtr = strchr(table, currentChar);
        if (charPtr != NULL) {
            int index = (int) (charPtr - table);
            char temp[4];
            snprintf(temp, sizeof(temp), "%03d", index);
            strcat(result, temp);
        }
    }
    return result;
}

char *decryptKey(char *data, const char *table) {
    size_t result_length = 1;
    char *result = (char *) malloc(result_length);
    result[0] = '\0';
    for (size_t i = 0; data[i] != '\0'; i += 3) {
        char temp[4];
        strncpy(temp, &data[i], 3);
        temp[3] = '\0';
        int index = (int) strtol(temp, NULL, 10);
        char decryptedChar = table[index];
        size_t current_length = strlen(result);
        result = (char *) realloc(result, current_length + 2);
        strncat(result, &decryptedChar, 1);
    }
    return result;
}
