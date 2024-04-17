#ifndef CPROJECTSMIREA_MATRIX_H
#define CPROJECTSMIREA_MATRIX_H

void PrintMatrix(int **matrix, int m, int n);

int **CreateMatrix(int m, int n, int mode);

int **fileRead(char *filename);

void FprintMatrix(int **matrix, int m, int n, char *resMatrix);

int **GenerateMatrix(int m, int n, int maxValue);

#endif //CPROJECTSMIREA_MATRIX_H
