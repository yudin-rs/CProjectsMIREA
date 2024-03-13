


#include <stdio.h>
#include "matrix.h"

int main(int argc, char *argv[]) {
    int mode, input, m_a, n_a, out, m_b, n_b;
    int **matrixA, **matrixB, *resultMatrix;
    printf("Введите размерность матрицы A (m n): ");
    scanf("%d %d", &m_a, &n_a);
    printf("Введите размерность матрицы B (m n): ");
    scanf("%d %d", &m_b, &n_b);
    if (n_a != m_b) {
        printf("Число столбцов матрицы A не совпадает с числом строк матрицы B.\n");
    } else {
        printf("Заполнение матрицы A\n");
        matrixA = matrixFill(matrixGeneration(m_a, n_a), m_a, n_a);
        printf("Заполнение матрицы B\n");
        matrixB = matrixFill(matrixGeneration(m_b, n_b), m_b, n_b);
        resultMatrix = matrixMultiply(convert(matrixA, m_a, n_a), m_a, n_a ,convert(matrixB, m_b, n_b), m_b, n_b);
        printf("Результат умножения матриц A*B:\n");
        matrixOut(resultMatrix, m_a, n_b);
    }
}