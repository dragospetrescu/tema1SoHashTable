all: tema1

tema1: tema1.o hashtable.o
	gcc -Wall tema1.o hashtable.o -o tema1 -lhash -L.

tema1.o: tema1.c
	gcc -fPIC -c tema1.c

hashtable.o: hashtable.c
	gcc -fPIC -c hashtable.c

clean:
	rm *.o tema1



