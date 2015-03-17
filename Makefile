all:
	g++ -o pixelsortercpp pixelsorter.cpp -lsfml-graphics -lsfml-window -lsfml-system
	gcc -o pixelsorterc pixelsorter.c -l:libpng16.so.16 -lz
c:
	gcc -o pixelsorter pixelsorter.c -l:libpng16.so.16 -lz
cpp:
	g++ -o pixelsortercpp pixelsorter.cpp -lsfml-graphics -lsfml-window -lsfml-system
