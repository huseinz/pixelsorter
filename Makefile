CC = gcc
CFLAGS = -lpng -lz
DEPS = pixelsorter.h
OBJ = pixelsorter.o main.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pixelsorter: pixelsorter.o main.o
	gcc -o pixelsorter main.o pixelsorter.o -lpng -lz

clean:
	rm *.o
