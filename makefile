CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: main

main:  main.o avl_tree.o processing.o preprocessing.o
	$(CC) -o forests $^


avl_tree.o: Avl_Tree_lib/avl_tree.c Avl_Tree_lib/avl_tree.h
	$(CC) $(CFLAGS) -c $<

processing.o: Input_Processing/processing.c Input_Processing/processing.h
	$(CC) $(CFLAGS) -c $<

preprocessing.o: Input_Preprocessing/preprocessing.c Input_Preprocessing/preprocessing.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c Input_Processing/processing.h Input_Preprocessing/preprocessing.h
	$(CC) $(CFLAGS) -c $<

# .c.o:
#     $(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o forests
