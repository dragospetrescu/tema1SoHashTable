all: tema1

tema1: tema1.o
	gcc -Wall tema1.c -o tema1 -lhash -L.

tema1.o: tema1.c
	gcc -fPIC -c tema1.c

clean:
	rm *.o tema1



