#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

COMPARATOR(compare)

int main() {
    int size, *array;
    printf("Введите размер массива: ");
    scanf("%d", &size);
    array = (int *) malloc(size * sizeof(int));
    printf("Введите элементы массива:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
    QSORT(array, size, compare);
    printf("Результат:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}