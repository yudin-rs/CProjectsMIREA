#include<stdio.h>
#include"matrix.h"
#include<time.h>
#include<stdlib.h>
#define N 1000

void multiply_matrices(int *A, int *B, int *C) {
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
int main(){
    int m1;
    int n1;
    int m2;
    int n2;
    int **matrixA;
    int **matrixB;
    int **matrixC;
    int *A = (int *)malloc(N * N * sizeof(int));
    int *B = (int *)malloc(N * N * sizeof(int));
    int *C = (int *)malloc(N * N * sizeof(int));

    for (int iter=0; iter<2; iter++){
        clock_t begin = clock();
        if (iter==0){
            m1=m2=n1=n2=100;
            printf("100\n");
        }
        else{
            m1=m2=n1=n2=1000;
            printf("1000\n");
        }
        matrixA = GenerateMatrix(m1,n1,101);
        matrixB = GenerateMatrix(n2,m2,101);
        matrixC = CreateMatrix(m1,n2,0);

        //ijk
        for(int i = 0; i < m1; i++){
            for(int j = 0; j < n2; j++){
                matrixC[i][j] = 0;
                for(int k = 0; k < n1; k++){
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        clock_t end = clock();
        double total_time = (double)(end - begin)/CLOCKS_PER_SEC;

        printf("%lf\n",total_time);

        //ikj
        begin = clock();

        for(int i = 0; i < m1; i++){
            for(int k = 0; k < n2; k++){
                matrixC[i][k] = 0;
                for(int j = 0; j < n1; j++){
                    matrixC[i][k] += matrixA[i][j] * matrixB[j][k];
                }
            }
        }
        end = clock();
        total_time = (double)(end - begin)/CLOCKS_PER_SEC;

        printf("%lf\n",total_time);

        //kji
        begin = clock();

        for(int k = 0; k < m1; k++){
            for(int j = 0; j < n2; j++){
                matrixC[k][j] = 0;
                for(int i = 0; i < n1; i++){
                    matrixC[k][j] += matrixA[k][i] * matrixB[k][j];
                }
            }
        }
        end = clock();
        total_time = (double)(end - begin)/CLOCKS_PER_SEC;

        printf("%lf\n",total_time);

        //kij
        begin = clock();

        for(int k = 0; k < m1; k++){
            for(int i = 0; i < n2; i++){
                matrixC[k][i] = 0;
                for(int j = 0; j < n1; j++){
                    matrixC[k][i] += matrixA[k][j] * matrixB[k][i];
                }
            }
        }
        end = clock();
        total_time = (double)(end - begin)/CLOCKS_PER_SEC;

        printf("%lf\n",total_time);

        //jik
        begin = clock();

        for(int j = 0; j < m1; j++){
            for(int i = 0; i < n2; i++){
                matrixC[j][i] = 0;
                for(int k = 0; k < n1; k++){
                    matrixC[j][i] += matrixA[j][k] * matrixB[k][i];
                }
            }
        }
        end = clock();
        total_time = (double)(end - begin)/CLOCKS_PER_SEC;

        printf("%lf\n",total_time);

        //jki
        begin = clock();

        for(int j = 0; j < m1; j++){
            for(int k = 0; k < n2; k++){
                matrixC[j][k] = 0;
                for(int i = 0; i < n1; i++){
                    matrixC[j][k] += matrixA[j][i] * matrixB[i][k];
                }
            }
        }
        end = clock();
        total_time = (double)(end - begin)/CLOCKS_PER_SEC;

        printf("%lf\n",total_time);
    }

    //part2

    for (int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            A[i*N+j]=matrixA[i][j];
            B[i*N+j]=matrixB[i][j];
        }
    }
    clock_t start = clock();
    multiply_matrices(A, B, C);
    clock_t end = clock();
    double total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Cache-friendly multiply: %lf\n", total_time);
    free(A);
    free(B);
    free(C);


    return 0;
}