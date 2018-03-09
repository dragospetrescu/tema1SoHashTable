all: tema1

build: tema1

tema1: tema1.o hashtable.o hashtable_interface.o
	gcc -g -Wall tema1.o hashtable.o hashtable_interface.o -o tema1 -lhash -L.

tema1.o: tema1.c
	gcc -g -c tema1.c

hashtable.o: hashtable.c
	gcc -g -c hashtable.c

hashtable_interface.o: hashtable_interface.c
	gcc -g -c hashtable_interface.c

clean:
	rm *.o tema1



