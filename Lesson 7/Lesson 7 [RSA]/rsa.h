#ifndef CPROJECTSMIREA_RSA_H
#define CPROJECTSMIREA_RSA_H

void rsa(int p, int q, int *e, int *n);

int modExp(int base, int exp, int mod);

int gcd(int a, int b);

int checkSeparator(char c);

char *rsaCrypt(char *data, int e, int n);

char *rsaDecrypt(char *data, int d, int n);

#endif //CPROJECTSMIREA_RSA_H
