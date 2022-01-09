CC = gcc
Flags = -Wall -g 

all: graph
 
graph : main2.o algo2.o
	$(CC) $(Flags) main2.o algo2.o -o graph

algo2.o : algo2.c graph.h
	$(CC) -c algo2.c

main2.o : main2.c graph.h
	$(CC) -c main2.c	

.PHONY:clean all

clean:
	rm -f *.o graph