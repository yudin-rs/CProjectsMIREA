#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void exportOneMatrix(int **matrix, int **transpMatrix, int m, int n) {
    FILE *file = fopen("out", "w");
    fprintf(file, "Исходная матрица %dx%d:\n", m, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "\nТранспонированная матрица %dx%d:\n", n, m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%d ", transpMatrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void exportTwoMatrix(int **matrixA, int **matrixB, int **resultMatrix, int m_a, int n_a, int m_b, int n_b) {
    FILE *file = fopen("out", "w");
    fprintf(file, "Первая матрица %dx%d:\n", m_a, n_a);
    for (int i = 0; i < m_a; i++) {
        for (int j = 0; j < n_a; j++) {
            fprintf(file, "%d ", matrixA[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "\nВторая матрица %dx%d:\n", m_b, n_b);
    for (int i = 0; i < m_b; i++) {
        for (int j = 0; j < n_b; j++) {
            fprintf(file, "%d ", matrixB[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "\nПроизведение матриц %dx%d:\n", m_a, n_b);
    for (int i = 0; i < m_a; i++) {
        for (int j = 0; j < n_b; j++) {
            fprintf(file, "%d ", resultMatrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int **inputOneMatrix(int *m, int *n) {
    FILE *file = fopen("input", "r");
    *m = 0;
    *n = 0;
    int value;
    while (fscanf(file, "%d", &value) == 1) {
        (*n)++;
        char currentChar;
        if (fscanf(file, "%c", &currentChar) == 1) {
            if (currentChar == '\n' || currentChar == EOF) {
                (*m)++;
                *n = 0;
            }
        }
    }
    fseek(file, 0, SEEK_SET);

    int **matrix = matrixGeneration(*m, *n);
    for (int i = 0; i < *m; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                exit(1);
            }
        }
    }
    fclose(file);
    return matrix;
}






