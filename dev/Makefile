OBJS = main.o swap.o
CC = gcc

swap: $(OBJS)
	$(CC) $(OBJS) -o swap

main.o: swap.h main.c
	$(CC) -c main.c

clean:
	rm -f $(OBJS)
