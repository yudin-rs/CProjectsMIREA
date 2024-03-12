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

void matrixOut(int **matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int **matrixTransp(int **matrix, int m, int n) {
    int **transposedMatrix = matrixGeneration(n, m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            transposedMatrix[j][i] = matrix[i][j];
        }
    }
    return transposedMatrix;
}


int **matrixFillRand(int **matrix, int m, int n) {
    srand(time(NULL));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 1001;
        }
    }
    return matrix;
}

int **matrixMultiply(int **matrixA, int m1, int n1, int **matrixB, int m2, int n2) {
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

void matrixFree(int **matrix, int m) {
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
}