#include <stdio.h>
#include <stdlib.h>

int logarithm(int n) {
    int k = 0;
    while (n > 1) {
        n = n >> 1;
        k += 1;
    }
    return k;
}

int check(int n, int k) {
    if ((1 << k) == n) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    if (n < 0) {
        printf("-2\n");
    } else {
        int log = logarithm(n);
        if (check(n, log) == 1) {
            printf("%d\n", log);
        } else {
            printf("-1\n");
        }
    }
}