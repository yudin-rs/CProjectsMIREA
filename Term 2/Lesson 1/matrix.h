
#ifndef CPROJECTSMIREA_MATRIX_H
#define CPROJECTSMIREA_MATRIX_H

int **matrixGeneration(int m, int n);

int **matrixFill(int **matrix, int m, int n);

void matrixOut(int **matrix, int m, int n);

int **matrixTransp(int **matrix, int m, int n);

int **matrixFillRand(int **matrix, int m, int n);

int **matrixMultiply(int **matrixA, int m1, int n1, int **matrixB, int m2, int n2);

void matrixFree(int **matrix, int m);

#endif //CPROJECTSMIREA_MATRIX_H
