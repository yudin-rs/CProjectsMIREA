#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

void rsa(int p, int q, int *e, int *n) {
    *n = p * q;
    int fi = (p - 1) * (q - 1);
    int d;
    *e = 5;
    d = modInverse(*e, fi);
    if ((*e * d) % fi != 1) {
        fprintf(stderr, "Ошибка: d не удовлетворяет условию (e * d) mod fi = 1\n");
        return;
    }
    FILE *crypt = fopen("crypt.txt", "w");
    fprintf(crypt, "%d %d", d, *n);
    fclose(crypt);
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
    size_t token_length = 32;
    char table[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789";
    char *token, *resultRSA, *encryptedValue, *resultDRSA, *key;
    int p = 7, q = 13, e, n, d;
    FILE *crypt;

    int choice;

    printf("Выберите режим работы:\n[1] Зашифровать;\n[2] Расшифровать;\n[0] Выход\n");

    while (1) {
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 0:
                printf("Выход\n");
                break;
            case 1:
                token = generateKey(token_length, table);
                encryptedValue = encryptString(token, table);
                xor(file, token);
                printf("Файл зашифрован\n");
                rsa(p, q, &e, &n);
                resultRSA = encryptRSA(encryptedValue, e, n);
                free(token);
                free(encryptedValue);
                break;
            case 2:
                crypt = fopen("crypt.txt", "r");
                if (crypt == NULL) {
                    perror("Ошибка открытия файла crypt.txt");
                    return EXIT_FAILURE;
                }
                fscanf(crypt, "%d", &d);
                fclose(crypt);
                resultDRSA = decryptRSA(resultRSA, d, n);
                key = decryptString(resultDRSA, table);
                xor(file, key);
                printf("Файл расшифрован\n");
                free(resultDRSA);
                free(resultRSA);
                resultRSA=NULL;
                free(key);
                break;
            default:
                printf("Некорректный ввод\n");
                break;
        }

        if (choice == 0) {
            break;  // Выход из цикла при выборе 0
        }
    }
}

