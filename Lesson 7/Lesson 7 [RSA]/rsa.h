#ifndef CPROJECTSMIREA_RSA_H
#define CPROJECTSMIREA_RSA_H

void rsa(int p, int q, int *e, int *n);

int modExp(int base, int exp, int mod);

int gcd(int a, int b);

int isDelimiter(char c);

char *encryptRSA(char *encrypted, int e, int n);

char *decryptRSA(char *encrypted, int d, int n);

#endif //CPROJECTSMIREA_RSA_H
