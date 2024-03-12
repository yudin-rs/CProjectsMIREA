#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    double array_one[n + 1];
    double array_two[m + 1];
    double out[n + m + 1];

    printf("Введите кф многочлена 1:\n");
    for (int i = 0; i <= n; i++) {
        scanf("%lf", &array_one[i]);
    }

    printf("Введите кф многочлена 2:\n");
    for (int i = 0; i <= m; i++) {
        scanf("%lf", &array_two[i]);
    }

    for (int i = 0; i <= n + m; ++i) {
        out[i] = 0;
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            out[i + j] += array_one[i] * array_two[j];
        }
    }

    for (int i = 0; i <= n + m; ++i) {
        printf("%.2lf ", out[i]);
    }
    printf("\n");
}
