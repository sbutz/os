#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <stdio.h>

typedef struct
{
	int height;
	int width;
	int **data;
} matrix;

int matrix_init(matrix *m, int width, int height);
void matrix_set_val(matrix *m, int row, int col, int value);
int matrix_mul(matrix *m1, matrix *m2);
void *matrix_print(FILE *stream, matrix *m);
void *matrix_destroy(matrix *m);

#endif
