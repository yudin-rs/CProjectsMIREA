#include <stdio.h>
#include "matrix.h"
#include "file.h"

int main(int argc, char *argv[]) {
    int mode, input, m_a, n_a, out, m_b, n_b;
    int **matrixA, **matrixB, **resultMatrix;

    while (1) {
        printf("[1] Умножение матриц A*B;\n[2] Транспонировать матрицу A;\n[0] Выход\n");
        printf("Введите действие: ");
        scanf("%d", &mode);
        getchar();

        switch (mode) {
            case 0:
                return 0;

            case 1:
                while (1) {
                    printf("[1] Задать вручную;\n[2] Сгенерировать случайно;\n[3] Файл\n[0] Назад\n");
                    printf("Введите режим задачи матрицы: ");
                    scanf("%d", &input);
                    getchar();

                    switch (input) {
                        case 0:
                            break;
                        case 1:
                            printf("Введите размерность матрицы A (m n): ");
                            scanf("%d %d", &m_a, &n_a);
                            printf("Введите размерность матрицы B (m n): ");
                            scanf("%d %d", &m_b, &n_b);
                            if (n_a != m_b) {
                                printf("Число столбцов матрицы A не совпадает с числом строк матрицы B.\n");
                                break;
                            }
                            while (1) {
                                printf("[1] Консоль;\n[2] Файл\n[0] Назад\n");
                                printf("Введите режим вывода: ");
                                scanf("%d", &out);
                                getchar();
                                switch (out) {
                                    case 1:
                                        printf("Заполнение матрицы A\n");
                                        matrixA = matrixFill(matrixGeneration(m_a, n_a), m_a, n_a);
                                        printf("Заполнение матрицы B\n");
                                        matrixB = matrixFill(matrixGeneration(m_b, n_b), m_b, n_b);
                                        resultMatrix = matrixMultiply(matrixA, m_a, n_a, matrixB, m_b, n_b);
                                        printf("Результат умножения матриц A*B:\n");
                                        matrixOut(resultMatrix, m_a, n_b);
                                        matrixFree(matrixA, m_a);
                                        matrixFree(matrixB, m_b);
                                        matrixFree(resultMatrix, m_a);
                                        return 0;
                                    case 2:
                                        printf("Заполнение матрицы A\n");
                                        matrixA = matrixFill(matrixGeneration(m_a, n_a), m_a, n_a);
                                        printf("Заполнение матрицы B\n");
                                        matrixB = matrixFill(matrixGeneration(m_b, n_b), m_b, n_b);
                                        resultMatrix = matrixMultiply(matrixA, m_a, n_a, matrixB, m_b, n_b);
                                        exportTwoMatrix(matrixA, matrixB, resultMatrix, m_a, n_a, m_b, n_b);
                                        matrixFree(matrixA, m_a);
                                        matrixFree(matrixB, m_b);
                                        matrixFree(resultMatrix, m_a);
                                        return 0;
                                    case 0:
                                        break;
                                    default:
                                        printf("Некорректный ввод\n");
                                        break;
                                }
                                if (out == 0)
                                    break;
                            }
                            break;
                        case 2:
                            printf("Введите размерность матрицы A (m n): ");
                            scanf("%d %d", &m_a, &n_a);
                            printf("Введите размерность матрицы B (m n): ");
                            scanf("%d %d", &m_b, &n_b);
                            if (n_a != m_b) {
                                printf("Число столбцов матрицы A не совпадает с числом строк матрицы B.\n");
                                break;
                            }
                            while (1) {
                                printf("[1] Консоль;\n[2] Файл\n[0] Назад\n");
                                printf("Введите режим вывода: ");
                                scanf("%d", &out);
                                getchar();
                                switch (out) {
                                    case 1:
                                        matrixA = matrixFillRand(matrixGeneration(m_a, n_a), m_a, n_a);
                                        matrixB = matrixFillRand(matrixGeneration(m_b, n_b), m_b, n_b);
                                        resultMatrix = matrixMultiply(matrixA, m_a, n_a, matrixB, m_b, n_b);
                                        printf("Результат умножения матриц A*B:\n");
                                        matrixOut(resultMatrix, m_a, n_b);
                                        matrixFree(matrixA, m_a);
                                        matrixFree(matrixB, m_b);
                                        matrixFree(resultMatrix, m_a);
                                        return 0;
                                    case 2:
                                        matrixA = matrixFillRand(matrixGeneration(m_a, n_a), m_a, n_a);
                                        matrixB = matrixFillRand(matrixGeneration(m_b, n_b), m_b, n_b);
                                        resultMatrix = matrixMultiply(matrixA, m_a, n_a, matrixB, m_b, n_b);
                                        exportTwoMatrix(matrixA, matrixB, resultMatrix, m_a, n_a, m_b, n_b);
                                        matrixFree(matrixA, m_a);
                                        matrixFree(matrixB, m_b);
                                        matrixFree(resultMatrix, m_a);
                                        return 0;
                                    case 0:
                                        break;
                                    default:
                                        printf("Некорректный ввод\n");
                                        break;
                                }
                                if (out == 0)
                                    break;
                            }
                            break;
                        case 3:
                            // FILE INPUT
                            break;
                        default:
                            printf("Некорректный ввод\n");
                            break;
                    }
                    if (input == 0)
                        break;
                }
                break;

            case 2:
                while (1) {
                    printf("[1] Задать вручную;\n[2] Сгенерировать случайно;\n[3] Файл\n[0] Назад\n");
                    printf("Введите режим задачи матрицы: ");
                    scanf("%d", &input);
                    getchar();

                    switch (input) {
                        case 0:
                            break;
                        case 1:
                            printf("Введите размерность матрицы A (m n): ");
                            scanf("%d %d", &m_a, &n_a);
                            while (1) {
                                printf("[1] Консоль;\n[2] Файл\n[0] Назад\n");
                                printf("Введите режим вывода: ");
                                scanf("%d", &out);
                                getchar();
                                switch (out) {
                                    case 1:
                                        matrixA = matrixFill(matrixGeneration(n_a, m_a), n_a, m_a);
                                        matrixB = matrixTransp(matrixA, m_a, n_a);
                                        printf("Результат транспонирования матрицы:\n");
                                        matrixOut(matrixB, m_a, n_a);
                                        matrixFree(matrixA, m_a);
                                        matrixFree(matrixB, m_b);
                                        return 0;
                                    case 2:
                                        matrixA = matrixFill(matrixGeneration(n_a, m_a), n_a, m_a);
                                        matrixB = matrixTransp(matrixA, m_a, n_a);
                                        exportOneMatrix(matrixA, matrixB, m_a, n_a);
                                        matrixFree(matrixA, m_a);
                                        matrixFree(matrixB, m_b);
                                        return 0;
                                    case 0:
                                        break;
                                    default:
                                        printf("Некорректный ввод\n");
                                        break;
                                }
                                if (out == 0)
                                    break;
                            }
                            break;
                        case 2:
                            printf("Введите размерность матрицы A (m n): ");
                            scanf("%d %d", &m_a, &n_a);
                            while (1) {
                                printf("[1] Консоль;\n[2] Файл\n[0] Назад\n");
                                printf("Введите режим вывода: ");
                                scanf("%d", &out);
                                getchar();
                                switch (out) {
                                    case 1:
                                        matrixA = matrixFillRand(matrixGeneration(n_a, m_a), n_a, m_a);
                                        matrixB = matrixTransp(matrixA, m_a, n_a);
                                        printf("Результат транспонирования матрицы:\n");
                                        matrixOut(matrixB, m_a, n_a);
                                        matrixFree(matrixA, m_a);
                                        matrixFree(matrixB, m_b);
                                        return 0;
                                    case 2:
                                        matrixA = matrixFillRand(matrixGeneration(n_a, m_a), n_a, m_a);
                                        matrixB = matrixTransp(matrixA, m_a, n_a);
                                        exportOneMatrix(matrixA, matrixB, m_a, n_a);
                                        matrixFree(matrixA, m_a);
                                        matrixFree(matrixB, m_b);
                                        return 0;
                                    case 0:
                                        break;
                                    default:
                                        printf("Некорректный ввод\n");
                                        break;
                                }
                                if (out == 0)
                                    break;
                            }
                            break;
                        case 3:
                            matrixA = inputOneMatrix(&m_a, &n_a);
                            matrixOut(matrixA, m_a, n_a);
                            break;
                        default:
                            printf("Некорректный ввод\n");
                            break;
                    }
                    if (input == 0)
                        break;
                }
                break;

            default:
                printf("Некорректный ввод\n");
                break;
        }
    }
}
