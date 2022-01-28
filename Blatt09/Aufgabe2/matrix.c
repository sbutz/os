#include <stdlib.h>
#include <pthread.h>

#include "matrix.h"

struct matrix_mul_param {
	matrix *m1, *m2;
	int row;
};
void *matrix_mul_row(void *data);

int matrix_init(matrix *m, int width, int height)
{
	int i;

	m->height = height;
	m->width = width;

	m->data = malloc(sizeof(int *) * height);
	for (i = 0; i < height; i++)
		m->data[i] = calloc(sizeof(int), width);

	return 0;
}

void matrix_set_val(matrix *m, int row, int col, int value)
{
	m->data[row][col] = value;
}

int matrix_mul(matrix *m1, matrix *m2)
{
	assert(m1->width == m2->height);

	int i, j;
	pthread_t *t;
	struct matrix_mul_param *param;
	void *res;

	t = malloc(sizeof(pthread_t) * m1->height);

	for (i = 0; i < m1->height; i++)
	{
		param = malloc(sizeof(struct matrix_mul_param));
		param->m1 = m1;
		param->m2 = m2;
		param->row = i;
		pthread_create(&t[i], NULL, matrix_mul_row, param);
	}

	for (i = 0; i < m1->height; i++)
	{
		pthread_join(t[i], &res);

		for (j = 0; j < m2->width; j++)
			m1->data[i][j] = ((int *) res)[j];

		free(res);
	}

	return 0;
}

void *matrix_mul_row(void *data)
{
	struct matrix_mul_param *param;
	int i, j;
	int *res;

	param = (struct matrix_mul_param *) data;
	res = calloc(sizeof(int), param->m2->width);

	for (i = 0; i < param->m1->width; i++)
		for (j = 0; j < param->m2->height; j++)
			res[i] += param->m1->data[param->row][j] * param->m2->data[i][j];

	free(param);

	return res;
}

void *matrix_print(FILE *stream, matrix *m)
{
	int i, j;

	for (i = 0; i < m->height; i++)
	{
		for (j = 0; j < m->width; j++)
			fprintf(stream, "%10d ", m->data[i][j]);
		fprintf(stream, "\n");
	}
}

void *matrix_destroy(matrix *m)
{
	int i;

	for (i = 0; i < m->height; i++)
		free(m->data[i]);
	free(m->data);
}
