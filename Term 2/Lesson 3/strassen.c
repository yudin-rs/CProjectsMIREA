#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrix.h"
#include "strassen.h"

int** strassen(int** A, int** B, int n) {
    if (n == 1) {
        int** C = matrixAllocate(1);
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }
    else {
        int** C = matrixAllocate(n);
        int newSize = n / 2;
        int** A11 = matrixAllocate(newSize);
        int** A12 = matrixAllocate(newSize);
        int** A21 = matrixAllocate(newSize);
        int** A22 = matrixAllocate(newSize);

        int** B11 = matrixAllocate(newSize);
        int** B12 = matrixAllocate(newSize);
        int** B21 = matrixAllocate(newSize);
        int** B22 = matrixAllocate(newSize);

        int** C11 = matrixAllocate(newSize);
        int** C12 = matrixAllocate(newSize);
        int** C21 = matrixAllocate(newSize);
        int** C22 = matrixAllocate(newSize);

        int** M1 = matrixAllocate(newSize);
        int** M2 = matrixAllocate(newSize);
        int** M3 = matrixAllocate(newSize);
        int** M4 = matrixAllocate(newSize);
        int** M5 = matrixAllocate(newSize);
        int** M6 = matrixAllocate(newSize);
        int** M7 = matrixAllocate(newSize);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }
        int** R1 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                R1[i][j] = B12[i][j] - B22[i][j];
            }
        }

        int** R2 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                R2[i][j] = A11[i][j] + A12[i][j];
            }
        }

        int** R3 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                R3[i][j] = A21[i][j] + A22[i][j];
            }
        }

        int** R4 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                R4[i][j] = B21[i][j] - B11[i][j];
            }
        }

        int** R5 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                R5[i][j] = A11[i][j] + A22[i][j];
            }
        }

        int** R6 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                R6[i][j] = B11[i][j] + B22[i][j];
            }
        }

        int** R7 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                R7[i][j] = A12[i][j] - A22[i][j];
            }
        }

        int** R8 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                R8[i][j] = B21[i][j] + B22[i][j];
            }
        }

        int** R9 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                R9[i][j] = A11[i][j] - A21[i][j];
            }
        }

        int** R10 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                R10[i][j] = B11[i][j] + B12[i][j];
            }
        }

        M1 = strassen(A11, R1, newSize);
        M2 = strassen(R2, B22, newSize);
        M3 = strassen(R3, B11, newSize);
        M4 = strassen(A22, R4, newSize);
        M5 = strassen(R5, R6, newSize);
        M6 = strassen(R7, R8, newSize);
        M7 = strassen(R9, R10, newSize);

        int** L1 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                L1[i][j] = M5[i][j] + M4[i][j];
            }
        }

        int** L2 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                L2[i][j] = L1[i][j] - M2[i][j];
            }
        }

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C11[i][j] = L2[i][j] + M6[i][j];
            }
        }

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C12[i][j] = M1[i][j] + M2[i][j];
            }
        }

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C21[i][j] = M3[i][j] + M4[i][j];
            }
        }

        int** L3 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                L3[i][j] = M5[i][j] + M1[i][j];
            }
        }

        int** L4 = matrixAllocate(newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                L4[i][j] = L3[i][j] - M3[i][j];
            }
        }

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C22[i][j] = L4[i][j] - M7[i][j];
            }
        }

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }

        freeMatrix(A11, newSize);
        freeMatrix(A12, newSize);
        freeMatrix(A21, newSize);
        freeMatrix(A22, newSize);

        freeMatrix(B11, newSize);
        freeMatrix(B12, newSize);
        freeMatrix(B21, newSize);
        freeMatrix(B22, newSize);

        freeMatrix(C11, newSize);
        freeMatrix(C12, newSize);
        freeMatrix(C21, newSize);
        freeMatrix(C22, newSize);

        freeMatrix(M1, newSize);
        freeMatrix(M2, newSize);
        freeMatrix(M3, newSize);
        freeMatrix(M4, newSize);
        freeMatrix(M5, newSize);
        freeMatrix(M6, newSize);
        freeMatrix(M7, newSize);

        freeMatrix(R1, newSize);
        freeMatrix(R2, newSize);
        freeMatrix(R3, newSize);
        freeMatrix(R4, newSize);
        freeMatrix(R5, newSize);
        freeMatrix(R6, newSize);
        freeMatrix(R7, newSize);
        freeMatrix(R8, newSize);
        freeMatrix(R9, newSize);
        freeMatrix(R10, newSize);

        freeMatrix(L1, newSize);
        freeMatrix(L2, newSize);
        freeMatrix(L3, newSize);
        freeMatrix(L4, newSize);
        return C;
    }
}

int maxDim(int rowsA, int colsA, int rowsB, int colsB) {
    int max_dim;
    if (rowsA >= colsA) {
        max_dim = rowsA;
    }
    else {
        max_dim = colsA;
    }

    int dimB;
    if (rowsB >= colsB) {
        dimB = rowsB;
    }
    else {
        dimB = colsB;
    }

    if (max_dim >= dimB) {
        return max_dim;
    }
    else {
        return dimB;
    }
}

int ordern(int n) {
    int i = 1;
    while (i < 12) {
        if (pow(2, i) < n && n <= pow(2, i + 1)) {
            return n = pow(2, i + 1);
        }
        else if (n == pow(2, i)) {
            return n = pow(2, i);
        }
        else {
            i++;
        }
    }
}