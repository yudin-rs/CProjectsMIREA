#include <stdio.h>
#include "matrix.h"
#include <time.h>

int main(int argc, char *argv[]) {
    int m_a, n_a, m_b, n_b;
    int **matrixA, **matrixB, **matrixC, **resultMatrixTwo, *resultMatrix;
    printf("Введите размерность матрицы A (m n): ");
    scanf("%d %d", &m_a, &n_a);
    printf("Введите размерность матрицы B (m n): ");
    scanf("%d %d", &m_b, &n_b);
    if (n_a != m_b) {
        printf("Число столбцов матрицы A не совпадает с числом строк матрицы B.\n");
    } else {
        matrixA = matrixFillRand(matrixGeneration(m_a, n_a), m_a, n_a);
        srand(time(NULL));
        matrixB = matrixFillRand(matrixGeneration(m_b, n_b), m_b, n_b);
        clock_t start = clock();
        resultMatrixTwo = matrixMultiply(matrixA, m_a, n_a, matrixB, m_b, n_b);
        clock_t end = clock();
        double naive_time = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%f сек\n",naive_time);
        start = clock();
        resultMatrix = matrixMultiply(convert(matrixA, m_a, n_a), m_a, n_a ,convert(matrixB, m_b, n_b), m_b, n_b);
        end = clock();
        double time = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%f сек\n", time);
        printf("Результат умножения матриц A*B:\n");
        matrixOut(resultMatrix, m_a, n_b);
    }
}