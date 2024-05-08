#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "strassen.h"
#include "matrix.h"


void outMatrix(int** matrix1, int m1, int n1, int** matrix2, int m2, int n2, int** res) {
    int o;
    printf("\nВведите режим вывода::\n");
    printf("[1] Консоль;\n[2] Файл\n");
    scanf("%d", &o);
    switch (o) {
    case 1:
        printf("\nРезультат:\n");
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                printf("%d ", res[i][j]);
            }
            printf("\n");
        }
        break;
    case 2:
        FILE * outfile = fopen("out.txt", "w");
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                fprintf(outfile, "%d ", res[i][j]);
            }
            fprintf(outfile, "\n");
        }
        fclose(outfile);
        break;
    }
}

void printMatrix(int** matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rowsA, colsA, rowsB, colsB, resultSize, newSize;
    srand(time(NULL));
    printf("Введите размерность матрицы A (m x n)\n");
    scanf("%d%d", &rowsA, &colsA);
    printf("Введите размерность матрицы B (m x n)\n");
    scanf("%d%d", &rowsB, &colsB);
    if (colsA != rowsB) {
        printf("Нельзя умножать матрицы, если количество строк A не равно количеству столбцов B\n");
        return 1;
    }
    resultSize = maxDim(rowsA, colsA, rowsB, colsB);
    newSize = ordern(resultSize);
    int** matrixA = matrixAllocate(newSize);
    int** matrixB = matrixAllocate(newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
        }
    }
    int** resultMatrix = strassen(matrixA, matrixB, newSize);
    outMatrix(matrixA, rowsA, colsA, matrixB, rowsB, colsB, resultMatrix);
    freeMatrix(matrixA, newSize);
    freeMatrix(matrixB, newSize);
    freeMatrix(resultMatrix, newSize);
}