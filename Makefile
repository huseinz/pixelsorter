CC = gcc
CFLAGS = 
LIBS = -lpng -lz
DEPS = pixelsorter.h
OBJ = pixelsorter.o main.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

pixelsorter: pixelsorter.o main.o
	gcc -o pixelsorter main.o pixelsorter.o -lpng -lz

clean:
	rm *.o
