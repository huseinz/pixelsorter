all:
	gcc -o pixelsorter pixelsorter.c -lpng -lz
cpp:
	g++ -o pixelsortercpp pixelsorter.cpp -lsfml-graphics -lsfml-window -lsfml-system
