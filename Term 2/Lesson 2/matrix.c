#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int **matrixGeneration(int m, int n) {
    int **matrix = malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        matrix[i] = malloc(n * sizeof(int));
    }
    return matrix;
}

int **matrixFill(int **matrix, int m, int n) {
    printf("Введите матрицу:\n");
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &matrix[j][i]);
        }
    }
    return matrix;
}

void matrixOut(int *matrix, int m, int n) {
    for (int i = 0; i < m * n; i++) {
        printf("%d ", matrix[i]);
        if ((i + 1) % n == 0) {
            printf("\n");
        }
    }
}

int **matrixFillRand(int **matrix, int m, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 1001;
        }
    }
    return matrix;
}

int **matrixMultiplyTwo(int **matrixA, int m1, int n1, int **matrixB, int m2, int n2) {
    if (n1 != m2) {
        return NULL;
    }
    int **resultMatrix = malloc(m1 * sizeof(int *));
    for (int i = 0; i < m1; i++) {
        resultMatrix[i] = malloc(n2 * sizeof(int));
    }

    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n2; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < n1; k++) {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return resultMatrix;
}

int *matrixMultiply(int *matrixA, int m1, int n1, int *matrixB, int m2, int n2) {
    if (n1 != m2) {
        return NULL;
    }

    int *resultMatrix = malloc(m1 * n2 * sizeof(int));
    for (int i = 0; i < m1 * n2; i++) {
        resultMatrix[i] = 0;
    }

    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n2; j++) {
            for (int k = 0; k < n1; k++) {
                resultMatrix[i * n2 + j] += matrixA[i * n1 + k] * matrixB[k * n2 + j];
            }
        }
    }
    return resultMatrix;
}

int *convert(int **matrix, int m, int n) {
    int *result = malloc(m * n * sizeof(int));
    int index = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[index++] = matrix[i][j];
        }
    }
    return result;
}