CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

all: main

main:  main.o avl_tree.o output.o input.o
	$(CC) -o forests $^

avl_tree.o: Avl_Tree_lib/avl_tree.c Avl_Tree_lib/avl_tree.h
	$(CC) $(CFLAGS) -c $<

output.o: Output_Processing/output.c Output_Processing/output.h
	$(CC) $(CFLAGS) -c $<

input.o: Input_Processing/input.c Input_Processing/input.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c Output_Processing/output.h Input_Processing/input.h
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f *.o forests
