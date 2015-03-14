This is a intended to do some pixel sorting on PNG images. I have not fully decided whether I want to write this using C and libpng or with C++ and SFML. Currently the SFML version is the most up to date and it's what the makefile targets.
Algorithms are hardcoded. This program is not intended to be used by anyone at this stage.

dependencies : SFML > 2.0

usage : pixelsorter infile.png outfile.png 
