#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	char *shared_memory;
	int i_parent, i_child;
	int value;

	shared_memory = mmap(0, sizeof(int), PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (shared_memory == MAP_FAILED)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return errno;
	}
	*shared_memory = -1;

	if ((pid = fork()) == -1)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return errno;
	}

	if (pid == 0)
	{
		printf("Child process begins.\n");
		for (i_child = 0; i_child < 10; i_child++)
		{
			//sleep(1);
			while ((value = *shared_memory) == -1)
			value = *shared_memory;
			printf("Child reports: current_value = %2d\n", value);
			*shared_memory = -1;
		}
		printf("Child is done.\n");
	}
	else
	{
		int childExitStatus;

		printf("Parent process begins.\n");
		for (i_parent = 0; i_parent < 10; i_parent++)
		{
			while (*shared_memory != -1);
			*shared_memory = i_parent * i_parent;
			printf("Parent reports: current_index = %2d\n", i_parent);
			//sleep(1);
		}
		wait(&childExitStatus);
		printf("Parent is done.\n");
		return 0;
	}
}
