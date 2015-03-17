This is a intended to do some pixel sorting on PNG images. I have not fully decided whether I want to write this using C and libpng or with C++ and SFML. Currently only the C version actually does anything.
Algorithms are hardcoded. 

This program is not intended to be used by anyone at this stage.

C++ dependencies : SFML > 2.0
C   dependencies : zlib libpng > 1.6 

Compiling: type 'make' to compile both c and c++ versions, or use 'make c' to compile the c version and 'make cpp' to compile the c++ version
  
usage : pixelsorter infile.png outfile.png 
