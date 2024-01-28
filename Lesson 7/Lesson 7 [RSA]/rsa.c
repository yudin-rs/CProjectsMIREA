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
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) {
            return i;
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
        printf("Ошибка: d не удовлетворяет условию (e * d) mod fi = 1\n");
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

int checkSeparator(char c) {
    return (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '&');
}

char *rsaCrypt(char *data, int e, int n) {
    size_t result_length = strlen(data) * 5 + 1;
    char *result = (char *) malloc(result_length);
    result[0] = '\0';
    srand((unsigned int) time(NULL));
    for (int i = 0; data[i] != '\0'; i += 2) {
        char temp[3];
        strncpy(temp, &data[i], 2);
        temp[2] = '\0';
        int index = (int) strtol(temp, NULL, 10);
        int cValue = modExp(index, e, n);
        char cryptString[32];
        snprintf(cryptString, sizeof(cryptString), "%d", cValue);
        strcat(result, cryptString);
        char randSeparator = "!@#$%&"[rand() % 6];
        strncat(result, &randSeparator, 1);
    }
    return result;
}

char *rsaDecrypt(char *data, int d, int n) {
    size_t result_length = strlen(data) / 5 + 1;
    char *result = (char *) malloc(result_length);
    result[0] = '\0';
    int i = 0;
    while (data[i] != '\0') {
        char temp[6];
        int j = 0;
        while (data[i] != '\0' && !checkSeparator(data[i])) {
            temp[j++] = data[i++];
        }
        temp[j] = '\0';
        if (data[i] != '\0') {
            i++;
        }
        int cValue = (int) strtol(temp, NULL, 10);
        int dcValue = modExp(cValue, d, n);
        char decryptedChar[3];
        snprintf(decryptedChar, sizeof(decryptedChar), "%02d", dcValue);
        strcat(result, decryptedChar);
    }
    return result;
}
