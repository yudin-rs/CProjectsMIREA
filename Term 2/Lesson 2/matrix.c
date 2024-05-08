#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"matrix.h"

int **matrixGeneration(int m, int n) {
    int **matrixA;
    matrixA = (int **) (malloc(sizeof(int *) * m));

    for (int i = 0; i < m; i++) {
        matrixA[i] = (int *) (malloc(sizeof(int) * n));
    }
    return matrixA;
}

void matrixOut(int **matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

int **matrixFillRand(int m, int n, int maxValue) {
    int **matrix;
    matrix = matrixGeneration(m, n);
    srand(time(NULL));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (rand() % (maxValue));
        }
    }
    return matrix;
}