all: tema1

build: tema1

tema1: tema1.o hashtable.o hashtable_interface.o
	gcc -std=c89 -g -Wall tema1.o hashtable.o hashtable_interface.o -o tema1 -lhash -L.

tema1.o: tema1.c
	gcc -std=c89 -g -c tema1.c

hashtable.o: hashtable.c
	gcc -std=c89 -g -c hashtable.c

hashtable_interface.o: hashtable_interface.c
	gcc -std=c89 -g -c hashtable_interface.c

clean:
	rm *.o tema1



