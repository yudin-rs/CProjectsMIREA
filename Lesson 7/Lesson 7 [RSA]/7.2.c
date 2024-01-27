#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rsa.h"
#include "xor.h"

int main(int argc, char *argv[]) {
    const char *file = argv[1];
    size_t token_length = 32;
    char table[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789";
    char *token, *resultRSA, *encryptedValue, *resultDRSA, *key;
    int p = 83, q = 89, e, n, d, choice;
    FILE *crypt;

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
                fscanf(crypt, "%d", &d);
                fclose(crypt);
                resultDRSA = decryptRSA(resultRSA, d, n);
                key = decryptString(resultDRSA, table);
                xor(file, key);
                printf("Файл расшифрован\n");
                free(resultDRSA);
                free(resultRSA);
                resultRSA = NULL;
                free(key);
                break;
            default:
                printf("Некорректный ввод\n");
                break;
        }
        if (choice == 0) {
            break;
        }
    }
}

