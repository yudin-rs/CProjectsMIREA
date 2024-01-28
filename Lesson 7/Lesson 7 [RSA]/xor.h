#ifndef CPROJECTSMIREA_XOR_H
#define CPROJECTSMIREA_XOR_H

#include <string.h>

char *generateKey(size_t length, const char *table);

void xor(const char *input, const char *key);

char *cryptKey(const char *data, const char *table);

char *decryptKey(char *data, const char *table);

#endif //CPROJECTSMIREA_XOR_H
