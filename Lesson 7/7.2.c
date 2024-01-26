#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char *generateKey(size_t length, char *encryptionTable) {
    const size_t charset_size = strlen(encryptionTable);
    srand((unsigned int) time(NULL));
    char *random_string = (char *) malloc(length + 1);
    for (size_t i = 0; i < length; i++) {
        int index = rand() % charset_size;
        random_string[i] = encryptionTable[index];
    }
    random_string[length] = '\0';
    return random_string;
}

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

char *encryptString(char *str, char *encryptionTable) {
    size_t result_length = strlen(str) * 3 + 1;
    char *result = (char *) malloc(result_length);
    result[0] = '\0';
    for (int i = 0; str[i] != '\0'; i++) {
        char currentChar = str[i];
        int index = 0;
        while (encryptionTable[index] != currentChar) {
            index++;
        }
        char temp[4];
        snprintf(temp, sizeof(temp), "%03d", index);
        strcat(result, temp);
    }
    return result;
}

char *decryptString(char *str, char *encryptionTable) {
    size_t result_length = 1;  // Начальная длина строки (1 для завершающего нуля)
    char *result = (char *)malloc(result_length);
    if (result == NULL) {
        fprintf(stderr, "Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    result[0] = '\0';

    for (int i = 0; str[i] != '\0'; i += 3) {
        char temp[4];
        strncpy(temp, &str[i], 3);
        temp[3] = '\0';

        int index = strtol(temp, NULL, 10);
        char decryptedChar = encryptionTable[index];

        size_t current_length = strlen(result);
        result = (char *)realloc(result, current_length + 2);  // Увеличиваем размер на 2 (1 для нового символа и 1 для завершающего нуля)

        if (result == NULL) {
            fprintf(stderr, "Error reallocating memory.\n");
            exit(EXIT_FAILURE);
        }

        strncat(result, &decryptedChar, 1);
    }

    return result;
}



int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 0;
}

void rsa(int p, int q, int *e, int *n, int *d) {
    *n = p * q;
    int fi = (p - 1) * (q - 1);
    *e = 5;
    *d = modInverse(*e, fi);
    if ((*e * *d) % fi != 1) {
        fprintf(stderr, "Ошибка: d не удовлетворяет условию (e * d) mod fi = 1\n");
        return;
    }
}

int modExp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int isDelimiter(char c) {
    return (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '&');
}

char *encryptRSA(char *encrypted, int e, int n) {
    size_t result_length = strlen(encrypted) * 5 + 1;
    char *result = (char *) malloc(result_length);
    result[0] = '\0';
    srand((unsigned int) time(NULL));
    for (int i = 0; encrypted[i] != '\0'; i += 2) {
        char temp[3];
        strncpy(temp, &encrypted[i], 2);
        temp[2] = '\0';
        int index = atoi(temp);
        int encryptedValue = modExp(index, e, n);
        char encryptedString[12];
        snprintf(encryptedString, sizeof(encryptedString), "%d", encryptedValue);
        strcat(result, encryptedString);
        char randomSymbol = "!@#$%&"[rand() % 6];
        strncat(result, &randomSymbol, 1);
    }
    return result;
}

char *decryptRSA(char *encrypted, int d, int n) {
    size_t result_length = strlen(encrypted) / 5 + 1;
    char *result = (char *) malloc(result_length);
    result[0] = '\0';
    int i = 0;
    while (encrypted[i] != '\0') {
        char temp[6];
        int j = 0;

        while (encrypted[i] != '\0' && encrypted[i] != '!' && encrypted[i] != '@' &&
               encrypted[i] != '#' && encrypted[i] != '$' && encrypted[i] != '%' &&
               encrypted[i] != '&') {
            temp[j++] = encrypted[i++];
        }
        temp[j] = '\0';

        if (encrypted[i] != '\0') {
            i++;
        }

        int encryptedValue = atoi(temp);
        int decryptedValue = modExp(encryptedValue, d, n);
        char decryptedChar[3];
        snprintf(decryptedChar, sizeof(decryptedChar), "%02d", decryptedValue);
        strcat(result, decryptedChar);
    }
    return result;
}

int main(int argc, char *argv[]) {
    const char *file = argv[1];
    size_t token_length = 16;
    char table[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789";
    char *token = generateKey(token_length, table);
    char *encryptedValue = encryptString(token, table);

    printf("Рандом ключ: %s\n", token);
    printf("Ключ по таблице: %s\n", encryptedValue);
    xor(file, token);
    printf("Зашифровано");

    free(token);

    int p = 7;
    int q = 13;
    int e, n, d;
    rsa(p, q, &e, &n, &d);
    printf("(e, n) = (%d, %d)\n", e, n);
    printf("(d, n) = (%d, %d)\n", d, n);

    char *resultRSA = encryptRSA(encryptedValue, e, n);
    printf("Зашифрованный табличный ключ рса: %s\n", resultRSA);
    free(encryptedValue);
    char *resultDRSA = decryptRSA(resultRSA, d, n);
    printf("Расшифрованный ключ рса: %s\n", resultDRSA);
    char *result = decryptString(resultDRSA, table);
    printf("Расшифрованный ключ рса: %s\n", result);
    free(resultRSA);
    free(resultDRSA);

    sleep(5);

    xor(file, result);
    printf("Расшифровано");

}

