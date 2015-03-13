all:
	gcc -o pixelsorter pixelsorter.c -l:libpng16.so.16 -lz
