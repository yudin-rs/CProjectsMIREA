#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
    for (*e = 2; *e < fi; (*e)++) {
        if (gcd(*e, fi) == 1) {
            break;
        }
    }
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
        int index = (int) strtol(temp, NULL, 10);
        int encryptedValue = modExp(index, e, n);
        char encryptedString[20];
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
        while (encrypted[i] != '\0' && !isDelimiter(encrypted[i])) {
            temp[j++] = encrypted[i++];
        }
        temp[j] = '\0';
        if (encrypted[i] != '\0') {
            i++;
        }
        int encryptedValue = (int) strtol(temp, NULL, 10);
        int decryptedValue = modExp(encryptedValue, d, n);
        char decryptedChar[3];
        snprintf(decryptedChar, sizeof(decryptedChar), "%02d", decryptedValue);
        strcat(result, decryptedChar);
    }
    return result;
}
