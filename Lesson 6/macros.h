#ifndef CPROJECTSMIREA_MACROS_H
#define CPROJECTSMIREA_MACROS_H

#include <stdlib.h>

#define COMPARATOR(compare) int compare(const void *a, const void *b) { \
return (*(const int *)a > *(const int *)b) - (*(const int *)a < *(const int *)b); }
#define QSORT(array, size, comparator) qsort(array, size, sizeof(array[0]), comparator)

#endif //CPROJECTSMIREA_MACROS_H
