CC=gcc
CFLAGS=-Wall -ansi -O3

wordmorph: main.o dic.o ficheiro.o pal.o grafo.o heap.o
	$(CC) $(CFLAGS) -o wordmorph main.o dic.o ficheiro.o pal.o grafo.o heap.o
main.o: main.c dic.h ficheiro.h pal.h grafo.h
	$(CC) -c $(CFLAGS) main.c

dic.o: dic.c dic.h
	$(CC) -c $(CFLAGS) dic.c

grafo.o: grafo.c grafo.h
	$(CC) -c $(CFLAGS) grafo.c

ficheiro.o: ficheiro.c ficheiro.h grafo.h
	$(CC) -c $(CFLAGS) ficheiro.c

heap.o: heap.c heap.h grafo.h
	$(CC) -c $(CFLAGS) heap.c


pal.o: pal.c pal.h dic.h grafo.h heap.h  ficheiro.h
	$(CC) -c $(CFLAGS) pal.c

clean::
	rm -f *.o core a.out wordmorph *~
