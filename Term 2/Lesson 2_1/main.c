#include<stdio.h>
#include"matrix.h"
#include<time.h>
#include<stdlib.h>

#define N 1000

void matrixMultiply(int *A, int *B, int *C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

int main() {
    int m1, n1, m2, n2;
    int **matrixA, **matrixB, **matrixC;
    int *A = (int *) malloc(N * N * sizeof(int));
    int *B = (int *) malloc(N * N * sizeof(int));
    int *C = (int *) malloc(N * N * sizeof(int));

    for (int iter = 0; iter < 2; iter++) {
        clock_t begin = clock();
        if (iter == 0) {
            m1 = m2 = n1 = n2 = 100;
            printf("При 100:\n");
        } else {
            m1 = m2 = n1 = n2 = 1000;
            printf("При 1000:\n");
        }
        matrixA = matrixFillRand(m1, n1, 101);
        matrixB = matrixFillRand(n2, m2, 101);
        matrixC = matrixGeneration(m1, n2);

        printf("ijk: ");
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                matrixC[i][j] = 0;
                for (int k = 0; k < n1; k++) {
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        clock_t end = clock();
        double total_time = (double) (end - begin) / CLOCKS_PER_SEC;

        printf("%lf\n", total_time);

        printf("ikj: ");
        begin = clock();

        for (int i = 0; i < m1; i++) {
            for (int k = 0; k < n2; k++) {
                matrixC[i][k] = 0;
                for (int j = 0; j < n1; j++) {
                    matrixC[i][k] += matrixA[i][j] * matrixB[j][k];
                }
            }
        }
        end = clock();
        total_time = (double) (end - begin) / CLOCKS_PER_SEC;

        printf("%lf\n", total_time);

        printf("kji: ");
        begin = clock();

        for (int k = 0; k < m1; k++) {
            for (int j = 0; j < n2; j++) {
                matrixC[k][j] = 0;
                for (int i = 0; i < n1; i++) {
                    matrixC[k][j] += matrixA[k][i] * matrixB[k][j];
                }
            }
        }
        end = clock();
        total_time = (double) (end - begin) / CLOCKS_PER_SEC;

        printf("%lf\n", total_time);

        printf("kij: ");
        begin = clock();

        for (int k = 0; k < m1; k++) {
            for (int i = 0; i < n2; i++) {
                matrixC[k][i] = 0;
                for (int j = 0; j < n1; j++) {
                    matrixC[k][i] += matrixA[k][j] * matrixB[k][i];
                }
            }
        }
        end = clock();
        total_time = (double) (end - begin) / CLOCKS_PER_SEC;

        printf("%lf\n", total_time);

        printf("jik: ");
        begin = clock();

        for (int j = 0; j < m1; j++) {
            for (int i = 0; i < n2; i++) {
                matrixC[j][i] = 0;
                for (int k = 0; k < n1; k++) {
                    matrixC[j][i] += matrixA[j][k] * matrixB[k][i];
                }
            }
        }
        end = clock();
        total_time = (double) (end - begin) / CLOCKS_PER_SEC;

        printf("%lf\n", total_time);

        printf("jki: ");
        begin = clock();

        for (int j = 0; j < m1; j++) {
            for (int k = 0; k < n2; k++) {
                matrixC[j][k] = 0;
                for (int i = 0; i < n1; i++) {
                    matrixC[j][k] += matrixA[j][i] * matrixB[i][k];
                }
            }
        }
        end = clock();
        total_time = (double) (end - begin) / CLOCKS_PER_SEC;

        printf("%lf\n", total_time);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = matrixA[i][j];
            B[i * N + j] = matrixB[i][j];
        }
    }
    clock_t start = clock();
    matrixMultiply(A, B, C);
    clock_t end = clock();
    double total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Умножение кешфр: %lf\n", total_time);
    free(A);
    free(B);
    free(C);


    return 0;
}