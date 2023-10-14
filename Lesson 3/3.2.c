#include <stdio.h>
#include <stdlib.h>

int binNod(int a, int b) {

    a = abs(a);
    b = abs(b);

    if ((a == b) || (b == 0 || a == 1)) {
        return a;
    } else if ((a == 0) || (b == 1)) {
        return b;
    } else if ((a % 2 == 0) && (b % 2 == 0)) {
        return 2 * binNod(a / 2, b / 2);
    } else if ((a % 2 == 0) && (b % 2 != 0)) {
        return binNod(a / 2, b);
    } else if ((a % 2 != 0) && (b % 2 == 0)) {
        return binNod(b / 2, a);
    } else if (a < b) {
        return binNod((b - 2) / 2, a);
    } else {
        return binNod((a - b) / 2, b);
    }
}

int main(int argc, char *argv[]) {

    if (argc == 1) {
        printf(":(");
    } else {
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);
        if (a == 0 || b == 0) {
            printf("%s\n", "Вы ввели 0. Введите любое натуральное число");
        } else {
            printf("%d\n", binNod(a, b));
        }
    }
}