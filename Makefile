all: tema1

tema1: tema1.o hashtable.o
	gcc -g -Wall tema1.o hashtable.o -o tema1 -lhash -L.

tema1.o: tema1.c
	gcc -g -c tema1.c

hashtable.o: hashtable.c
	gcc -g -c hashtable.c

clean:
	rm *.o tema1



