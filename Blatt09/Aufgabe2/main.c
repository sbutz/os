#include <stdio.h>

#include "matrix.h"

int main(void)
{
	int i, j;
	matrix m1, m2;

	matrix_init(&m1, 3, 3);
	matrix_init(&m2, 3, 3);

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			matrix_set_val(&m1, i, j, 1);
			matrix_set_val(&m2, i, j, 1);
		}
	}

	matrix_print(stdout, &m1);
	printf("\n");
	matrix_print(stdout, &m2);

	matrix_mul(&m1, &m2);
	printf("\n");
	matrix_print(stdout, &m1);

	matrix_destroy(&m1);
	matrix_destroy(&m2);

	return 0;
}
