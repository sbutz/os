#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef int(*dummy)(void);

void *fn_read(char *filename);

int main()
{
	void *p = fn_read("export");
	dummy test = p;
	printf("%d\n", test());

	return 0;
}

void *fn_read(char *filename)
{
	int fd;
	struct stat stat;
	void *p;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		printf("Error opening file.\n");

	if (fstat(fd, &stat) == -1)
		printf("Error reading file stats\n");

	p = mmap(NULL, stat.st_size, PROT_EXEC, MAP_PRIVATE, fd, 0);

	close(fd);

	return p;
}
