all: tema1

build: tema1

tema1: tema1.o bucket_interface.o hashtable_interface.o
	gcc -Wall tema1.o bucket_interface.o hashtable_interface.o -o tema1 -lhash -L.

tema1.o: tema1.c
	gcc -Wall -c tema1.c

bucket_interface.o: bucket_interface.c
	gcc -Wall -c bucket_interface.c

hashtable_interface.o: hashtable_interface.c
	gcc -Wall -c hashtable_interface.c

clean:
	rm *.o tema1



