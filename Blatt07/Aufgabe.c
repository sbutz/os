#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void strToUpper(char *str);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s STRING\n", argv[0]);
		return 1;
	}

	int fromChild[2], toChild[2];
	char buffer[50], buffer2[50];
	int fd;
	struct stat stat;

	pipe(fromChild);
	pipe(toChild);

	if (fork() == 0)
	{
		while (read(toChild[0], &buffer, 50) > 0)
		{
			strToUpper(buffer);
			write(fromChild[1], buffer, strnlen(buffer, 50));
		}
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			printf("Cannot open %s\n", argv[1]);
			return 1;
		}

		while (read(fd, buffer, 50) > 0)
		{
			write(toChild[1], buffer, strnlen(buffer, 50));
			read(fromChild[0], buffer, 50);
			printf("%s", buffer);
		}

		close(fd);

		return 0;
	}
}

void strToUpper(char *s)
{
	while (*s != '\0')
	{
		*s = toupper((unsigned char) *s);
		s++;
	}
}
