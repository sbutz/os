#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 5

typedef struct {
	char data;
	int timestamp;
} record;

void printMemoryLayout(record **, int);
int replacementsLRU(char *, record **, int);
int replacementsFIFO(char *, record **, int);
int victimStack(char, record **, int);
int victimLRU(char, record **, int);
int victimFIFO(char, record **, int);
void push(int index);
int pop(void);

int clock = 0, qp = 0, sp = 0;
int *stack;

void printMemoryLayout(record **memory, int size)  {
	int i;
	printf("memory layout: \n-------");
	for (i = 0;  i < size;  ++i)
	  printf("--");
	printf("\nframe: ");
	for (i = 0;  i < size;  ++i)
	  printf("%d ", i + 1);
	printf("\npage:  ");
	for (i = 0;  i < size;  ++i)
	  if (memory[i]->data != 0)
	    printf("%c ", memory[i]->data);
	  else
	    printf("- ");
	printf("\n-------");
	for (i = 0;  i < size;  ++i)
	  printf("--");
	printf("\n");
}

int replacementsLRU(char *referenceStr, record **memory, int size)  {
}

int victimLRU(char page, record **frames, int size)  {
}

int replacementsFIFO(char *referenceStr, record **memory, int size)  {
}

int victimFIFO(char page, record **frames, int size)  {
}  

int main(int argc, char **argv)  {
	 int nframes;  int i;
	 record **frames;
	 if (argc < 2)  {
	   printf("usage: replace <referenceStr>\n");
	   return -1;
	 }
	 printf("number of frames? ");
	 scanf("%d", &nframes);
	 frames = (record **)malloc(nframes * sizeof(record *));
	 for (i = 0;  i < nframes;  ++i)  {
	    frames[i] = (record *)malloc(sizeof(record));
	    frames[i]->data = (char)0;
	 }
	 stack = (int *)malloc(STACK_SIZE * sizeof(int));
	 for (i = 0;  i < STACK_SIZE;  ++i)
	    stack[i] = -1;
	 printf("totally, %d replacements were required to store %s in %d frames\n",
	 replacementsFIFO(argv[1], frames, nframes), argv[1], nframes);
	 // replacementsLRU(argv[1], frames, nframes), argv[1], nframes);
}
