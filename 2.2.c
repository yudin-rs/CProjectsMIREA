#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf(":(");
    } else {
        for (int i = 1; i < argc; i++) {
            if (i % 2 == 0) {
                for (int k = 0; k < i / 2; k++) {
                    printf("\t");
                }
            }
            printf("%s\n", argv[i]);
        }
    }
}