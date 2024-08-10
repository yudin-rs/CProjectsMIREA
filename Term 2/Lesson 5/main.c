#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/sha.h>

#define MAX_BLOCKS 128
#define MAX_DATA_LENGTH 128

struct Block {
    char data[MAX_DATA_LENGTH];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char prev_hash[SHA256_DIGEST_LENGTH];
};

struct Blockchain {
    struct Block blocks[MAX_BLOCKS];
    int length;
};

void calculateHash(struct Block *block) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, block->data, strlen(block->data));
    SHA256_Update(&ctx, block->prev_hash, SHA256_DIGEST_LENGTH);
    SHA256_Final(block->hash, &ctx);
}

void addBlock(struct Blockchain *chain, char *data) {
    if (chain->length > 0)
        memcpy(chain->blocks[chain->length].prev_hash, chain->blocks[chain->length - 1].hash, SHA256_DIGEST_LENGTH);
    strncpy(chain->blocks[chain->length].data, data, MAX_DATA_LENGTH);
    calculateHash(&chain->blocks[chain->length]);
    chain->length++;
}

void printBlockchain(struct Blockchain *chain) {
    if (chain->length == 0) {
        printf("Блокчейна нет\n");
        return;
    }

    for (int i = chain->length - 1; i >= 0; i--) {
        printf("\nДанные в блоке %d: %s\n", i + 1, chain->blocks[i].data);
        printf("Пред. хэш: ");
        for (int j = 0; j < SHA256_DIGEST_LENGTH; j++)
            printf("%02x", chain->blocks[i].prev_hash[j]);
        printf("\nХэш данного блока: ");
        for (int j = 0; j < SHA256_DIGEST_LENGTH; j++)
            printf("%02x", chain->blocks[i].hash[j]);
        if (i > 0) {
            printf("\nПроверка целостности хэша %d: %s\n", i + 1,
                   memcmp(chain->blocks[i].prev_hash, chain->blocks[i - 1].hash, SHA256_DIGEST_LENGTH) == 0 ? "Верно" : "Ошибка");
        } else {
            printf("\nПроверка целостности хэша %d: Верно\n", i + 1);
        }
    }
}

void createBlockchain(struct Blockchain *chain) {
    int length;
    char data[MAX_DATA_LENGTH];

    printf("Введите длину блокчейна: ");
    scanf("%d", &length);
    getchar();

    for (int i = 0; i < length; i++) {
        printf("Введите данные %d блока: ", i + 1);
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0';
        addBlock(chain, data);
    }
}

int main() {
    struct Blockchain chain = {0};
    int choice;

    while (1) {
        printf("[1] Создать блокчейн\n");
        printf("[2] Вывести блокчейн\n");
        printf("[0] Закончить\n");
        printf("Выберите опцию: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 0:
                printf("Завершение программы.\n");
                return 0;
            case 1:
                createBlockchain(&chain);
                break;
            case 2:
                printBlockchain(&chain);
                break;
            default:
                printf("Некорректный ввод.\n");
                break;
        }
    }
}
