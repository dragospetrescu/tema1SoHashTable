all: tema1

tema1: main.o
        gcc -Wall main.c -o tema1 -lhash -L.

main.o: main.c
        gcc -fPIC -c main.c

clean:
        rm *.o tema1



