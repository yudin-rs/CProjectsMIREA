#include <stdio.h>
#include <stdlib.h>
#include <math.h>

union Number {
    long long ll_num;
    struct { long long low, high; } parts;
};

int countDigits(long long num) {
    return num == 0 ? 1 : (int)log10(llabs(num)) + 1;
}

long long karatsuba(union Number x, union Number y) {
    if (countDigits(x.ll_num) < 2 || countDigits(y.ll_num) < 2)
        return x.ll_num * y.ll_num;

    int m = fmax(countDigits(x.ll_num), countDigits(y.ll_num));
    int m2 = m / 2;

    union Number high1 = {.ll_num = x.ll_num / (long long)pow(10, m2)};
    union Number low1 = {.ll_num = x.ll_num % (long long)pow(10, m2)};
    union Number high2 = {.ll_num = y.ll_num / (long long)pow(10, m2)};
    union Number low2 = {.ll_num = y.ll_num % (long long)pow(10, m2)};

    long long z0 = karatsuba(low1, low2);
    long long z1 = karatsuba((union Number){.ll_num = low1.ll_num + high1.ll_num},
                             (union Number){.ll_num = low2.ll_num + high2.ll_num});
    long long z2 = karatsuba(high1, high2);

    return z2 * (long long)pow(10, 2 * m2) + (z1 - z2 - z0) * (long long)pow(10, m2) + z0;
}

int main() {
    union Number x = {.ll_num = 1234};
    union Number y = {.ll_num = 5678};

    printf("Результат умножения %lld на %lld: %lld\n", x.ll_num, y.ll_num, karatsuba(x, y));

    return 0;
}
