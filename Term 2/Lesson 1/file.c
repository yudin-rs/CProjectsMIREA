#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void exportOneMatrix(int **matrix, int **transpMatrix, int m, int n) {
    FILE *file = fopen("out.txt", "w");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return;
    }

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
    FILE *file = fopen("out.txt", "w");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return;
    }

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

int **inputOneMatrix(const char *filename, int *m, int *n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return NULL;
    }

    fscanf(file, "%d %d", m, n);
    int **matrix = matrixGeneration(*m, *n);
    for (int i = 0; i < *m; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
    return matrix;
}