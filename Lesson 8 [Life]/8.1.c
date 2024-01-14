#include <stdio.h>
#include "life.h"

int main() {

    int N, t, k;
    FILE *input = fopen("input.txt", "r");
    fscanf(input, "%d %d %d", &N, &t, &k);
    fclose(input);

    FILE *output = fopen("output.txt", "w");

    generationBoard(N, t);

    for (int i = 0; i <= k; i++) {
        printf("Ход игры № %d\n", i);
        printBoard(N);

        fprintf(output, "Ход игры № %d\n", i);
        printToFile(N, output);
        if (i < k) {
            updateBoard(N);
        }
    }

    fclose(output);
}
