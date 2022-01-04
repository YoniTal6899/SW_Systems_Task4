CC=gcc
FLAGS= -Wall -g
.PHONY: clean all
#make all
all: graph

#make clean
clean: 
	rm -f *.o *.a *.so graph

graph: graph.o
	$(CC) $(FLAGS) -o graph graph.c graph.h

graph.o: graph.c 
	$(CC) $(FLAGS) -c graph.c