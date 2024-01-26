#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "life.h"

int **board;

void generationBoard(int N, int t) {
    srand(time(NULL));
    board = (int **) malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        board[i] = (int *) malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    int count = 0;
    while (count < t) {
        int row = rand() % N;
        int col = rand() % N;
        if (board[row][col] == 0) {
            board[row][col] = 1;
            count++;
        }
    }
}


void clearBoard(int N) {
    for (int i = 0; i < N; i++) {
        free(board[i]);
    }
    free(board);
}

int countNeigh(int row, int col, int N) {
    int liveNeighbors = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < N && j >= 0 && j < N && !(i == row && j == col)) {
                liveNeighbors += board[i][j];
            }
        }
    }
    return liveNeighbors;
}

void printBoard(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void updateBoard(int N) {
    int **tempBoard;
    tempBoard = (int **) malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        tempBoard[i] = (int *) malloc(N * sizeof(int));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int liveNeighCells = countNeigh(i, j, N);

            if (board[i][j] == 0) {
                if (liveNeighCells == 3) {
                    tempBoard[i][j] = 1;
                } else {
                    tempBoard[i][j] = 0;
                }
            } else {
                if (liveNeighCells < 2 || liveNeighCells > 3) {
                    tempBoard[i][j] = 0;
                } else {
                    tempBoard[i][j] = 1;
                }
            }
        }
    }
    clearBoard(N);
    board = tempBoard;
}

void printToFile(int N, FILE *file) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(file, "%d ", board[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
}
