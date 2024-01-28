#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "longnum.h"
#include "longnum_utils.h"

int main() {
    char numOne[1000], numTwo[1000];
    printf("Введите первое число: ");
    scanf("%s", numOne);
    printf("Введите второе число: ");
    scanf("%s", numTwo);

    LongNumber longNumOne = init();
    LongNumber longNumTwo = init();

    longNumOne.represent.digits = (int *) malloc(strlen(numOne) * sizeof(int));
    for (int i = (int) strlen(numOne) - 1; i >= 0; i--) {
        longNumOne.represent.digits[longNumOne.length++] = numOne[i] - '0';
    }

    longNumTwo.represent.digits = (int *) malloc(strlen(numTwo) * sizeof(int));
    for (int i = (int) strlen(numTwo) - 1; i >= 0; i--) {
        longNumTwo.represent.digits[longNumTwo.length++] = numTwo[i] - '0';
    }

    LongNumber result = multiply(longNumOne, longNumTwo);

    printf("Результат: ");
    print(result);

    freeMemory(longNumOne);
    freeMemory(longNumTwo);
    freeMemory(result);
}
