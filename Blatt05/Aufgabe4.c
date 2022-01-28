#include <stdlib.h>
#include <string.h>

int main()
{
	char *cp;
	cp = (char *)malloc(50);
	cp = strncpy(cp, "ohohoh", 50);
	free(cp);
	
	return 0;
};
