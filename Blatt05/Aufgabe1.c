#include <stdio.h>
#include <string.h>

int dummy();
int fn_size(void *f);
int fn_write();

int main()
{
	printf("Wrote: %d Byte\n", fn_write(dummy));
	return 0;
}

int dummy()
{
	int x = 1;
	int y = 2;
	int z = x + y;
	return z;
}


int fn_size(void *f)
{
	int opcode = 0xc3;
	int i = 0;
	while (memcmp(&opcode, f+i, 1))
		i++;
	return i+1;
}

int fn_write(void *f)
{
	int size = fn_size(f);
	FILE *file = fopen("export", "w");
	fwrite(f, 1, fn_size(f), file);
	fclose(file);
	return size;
}
