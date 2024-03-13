
#ifndef CPROJECTSMIREA_MATRIX_H
#define CPROJECTSMIREA_MATRIX_H

int **matrixGeneration(int m, int n);

int **matrixFill(int **matrix, int m, int n);

void matrixOut(int *matrix, int m, int n);

int **matrixFillRand(int **matrix, int m, int n);

int *matrixMultiply(int *matrixA, int m1, int n1, int *matrixB, int m2, int n2);

int *convert(int **matrix, int m, int n);

#endif //CPROJECTSMIREA_MATRIX_H
