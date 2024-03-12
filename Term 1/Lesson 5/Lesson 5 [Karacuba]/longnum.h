#ifndef CPROJECTSMIREA_LONGNUM_H
#define CPROJECTSMIREA_LONGNUM_H

typedef union {
    int *digits;
    char *str;
} numRepresent;

typedef struct {
    numRepresent represent;
    int length;
} LongNumber;

LongNumber init();

void print(LongNumber num);

void freeMemory(LongNumber num);

#endif //CPROJECTSMIREA_LONGNUM_H
