# ifndef __MATRIX_H
# include <stdlib.h>
#include <stdarg.h>
# include <stdio.h>
# include <math.h>
# include "lists.h"

typedef struct {
    int width;  int height;
    list *elements;
}  matrix;

matrix *createMatrix(int, int);
extern void setValue(matrix *, int, int, double) ;
extern double getValue(matrix *, int, int);
extern matrix *mult(matrix *, matrix *);
extern matrix *forkmult(matrix *, matrix *);
extern matrix *parmult(matrix *, matrix *);
extern void printMatrix(matrix *);

# define __MATRIX_H
# endif
