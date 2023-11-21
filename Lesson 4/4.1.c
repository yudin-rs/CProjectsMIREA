#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int t = atoi(argv[3]);

    srand(time(NULL));

    int *array = (int *) malloc(n * sizeof(int));

    printf("PART 1\n");
    for (int i = 0; i < n; i++) {
        array[i] = rand() % m;
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("PART 2\n");
    for (int i = 0; i < n; i++) {
        if (array[i] < t) {
            printf("%d\n", i);
        }
    }

    free(array);
}
