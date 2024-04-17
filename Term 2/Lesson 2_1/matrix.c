#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include"matrix.h"

int** CreateMatrix(int m, int n, int mode){
    int** matrixA;

    matrixA = (int **)(malloc(sizeof(int*)*m));

    //sozdanie strok
    for (int i=0;i<m;i++){
        matrixA[i]=(int *)(malloc(sizeof(int)*n));
    }

    //zapolnenie massiva
    if (mode==1){
        printf("Vvedite elementy:\n");
        for (int i=0; i<m; i++){
            for (int j=0; j<n; j++){
                scanf("%d",&matrixA[i][j]);
            }
            printf("\n");
        }
    }

    return matrixA;
}

void PrintMatrix(int** matrix, int m, int n){
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}
int** GenerateMatrix(int m, int n, int maxValue){
    int** matrix;
    matrix = CreateMatrix(m,n,0);
    srand(time(NULL));
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            matrix[i][j] = (rand() % (maxValue));
        }
    }
    return matrix;

}
void FprintMatrix(int** matrix, int m, int n, char* resMatrix){
    FILE* file = fopen(resMatrix,"w");
    if (resMatrix == "result"){
        fprintf(file,"Result:\n");
    }
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            fprintf(file,"%d ",matrix[i][j]);
        }
        fprintf(file,"\n");
    }
    fclose(file);
    printf("The matrix is written in file.\n");
}

int** fileRead(char* filename){
    int m;
    int n;
    int** matrixA;
    FILE* file = fopen(filename,"r");
    fscanf(file, "%d,%d",&m,&n);
    matrixA = CreateMatrix(m,n,0);
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            fscanf(file,"%d",&matrixA[i][j]);
        }
    }

    return matrixA;
}