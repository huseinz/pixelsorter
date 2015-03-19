all:
	gcc -o pixelsorter main.c pixelsorter.c -lpng -lz
cpp:
	g++ -o pixelsortercpp pixelsorter.cpp -lsfml-graphics -lsfml-window -lsfml-system
