#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *p = malloc(1);
	*p = 'a';
	char c = *(p+0);
	printf("%c\n", c);
	free(p);

	return 0;
}
