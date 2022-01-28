#include <stdio.h>
#include <stdlib.h>

#define PROCESSES 5
#define TABLE_SIZE 100
#define FRAMES_PER_PROC 500
#define FRAME_SIZE 512
#define BASE 0
#define LIMIT 2500

struct frame {
	char data[FRAME_SIZE];
};

struct page {
	int pnr, pid, fnr;
};

int main()
{
	struct frame mem[LIMIT + BASE];
	struct page table[TABLE_SIZE];
	int p, a, i;

	srand(0);
	for (p = 0; p < TABLE_SIZE; p++)
	{
		table[p].pid = rand() % PROCESSES;
		table[p].pnr = rand() % FRAMES_PER_PROC;
		table[p].fnr = table[p].pid * FRAMES_PER_PROC + table[p].pnr;
		if (table[p].fnr > LIMIT)
			return 1;
		mem[table[p].fnr + BASE].data[0] = rand();
	}

	for (p = 0; p < PROCESSES; p++)
	{
		for (a = 0; a < FRAMES_PER_PROC; a++)
		{
			for (i = 0; i < TABLE_SIZE; i++)
			{
				if (table[i].pid == p && table[i].pnr == a)
				{
					if (table[i].fnr > LIMIT)
						return 1;
					mem[table[i].fnr + BASE].data;
					break;
				}
			}
		}
	}
	

	return 0;
}
