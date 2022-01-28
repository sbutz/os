struct matrix
{
	int width;
	int height;
};

program MATRIX_MUL {
	version MATRIX_MUL {
		matrix MATRIX_MUL(matrix) = 1;
	} = 1;
} = 0x2345678;
