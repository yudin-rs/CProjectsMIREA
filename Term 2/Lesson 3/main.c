#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/sha.h>

int main(int argc, char*argv[]) {
    SSL_library_init();
    printf("Version is %s\n", OPENSSL_VERSION_TEXT);
    unsigned char out[128];
    SHA256(argv[1], strlen(argv[1]), out);

    for (int i=0; i<SHA256_DIGEST_LENGTH; i++) {
        printf("%x", out[i]);
    }
    printf("\n");

}