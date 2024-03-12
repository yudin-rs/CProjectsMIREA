#include "longnum.h"
#include <stdlib.h>
#include <stdio.h>

LongNumber init() {
    LongNumber num;
    num.length = 0;
    num.represent.digits = NULL;
    return num;
}

void print(LongNumber num) {
    if (num.length == 0) {
        printf("0");
    } else {
        for (int i = num.length - 1; i >= 0; i--) {
            printf("%d", num.represent.digits[i]);
        }
    }
    printf("\n");
}

void freeMemory(LongNumber num) {
    free(num.represent.digits);
}
