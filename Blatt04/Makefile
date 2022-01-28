CC=cc
CFLAGS=-g

SRC=(main.c tester.c)
OBJS=(main.o tester.o)

main: main.o tester.o
	$(CC) -o $@ $?

%.o: %.c
	$(CC) $(CFLAGS) $< -c

clean:
	rm -f *.o core main
