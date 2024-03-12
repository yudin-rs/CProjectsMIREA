#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc == 1) {
        printf(":(");
    } else if (argc < 4) {
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    } else {
        int sum = 0;
        for (int i = 0; i < argc * 3; i++) {
            sum += i;
        }
        printf("%d", sum);
    }
}