#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "life.h"

int **board;

void generationBoard(int N, int t) {
    srand(time(NULL));
    board = (int **) malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        board[i] = (int *) malloc(N * sizeof(int));;
    }
    for (int i = 0; i < t; i++) {
        int row = rand() % N;
        int col = rand() % N;
        board[row][col] = 1;
    }
}

void clearBoard(int N) {
    for (int i; i<N; i++) {
        free(board[i]);
    }
    free(board);
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
        tempBoard[i] = (int *) malloc(N * sizeof(int));;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int liveNeighCells = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    int cellsRow = (i + x + N) % N;
                    int cellsCol = (j + y + N) % N;
                    liveNeighCells += board[cellsRow][cellsCol];
                }
            }

            liveNeighCells -= board[i][j];

            if ((board[i][j] == 1) && (liveNeighCells < 2 || liveNeighCells > 3)) {
                tempBoard[i][j] = 0;
            } else if ((board[i][j] == 0) && (liveNeighCells == 3)) {
                tempBoard[i][j] = 1;
            } else {
                tempBoard[i][j] = board[i][j];
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


