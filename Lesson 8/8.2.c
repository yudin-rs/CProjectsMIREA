#include <stdio.h>

void SomeFunction(const char *str) {

    char *secret_data = "AAAABBBB";

    printf(str);

}

int main(int argc, char **argv) {

    SomeFunction(argv[1]);

    return 0;

}
