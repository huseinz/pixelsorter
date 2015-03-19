#include "pixelsorter.h"

int main(int argc, char* argv[]) {

	if(argc != 3)
		abort_("Usage : %s, <png_in> <png_out>", argv[0]);

	read_png_file(argv[1]);


	flat = (png_byte*)malloc(sizeof(png_byte) * height * (width * 3));

	for(y = 0; y < height; y++) {
		png_byte* row = row_pointers[y];
		png_byte* flatrow = flat + width * y * 3;
		for(x = 0; x < width; x++) {
			png_byte* ptrA = &row[x*3];
			png_byte* ptrB = &flatrow[x*3];
			ptrB[0] = ptrA[0];
			ptrB[1] = ptrA[1];
			ptrB[2] = ptrA[2];
		}
	}

	pixel_sort();

	for(y = 0; y < height; y++) {
		png_byte* row = row_pointers[y];
		png_byte* flatrow = flat + width * y * 3;
		for(x = 0; x < width; x++) {
			png_byte* ptrB = &row[x*3];
			png_byte* ptrA = &flatrow[x*3];
			ptrB[0] = ptrA[0];
			ptrB[1] = ptrA[1];
			ptrB[2] = ptrA[2];
		}
	}
	write_png_image(argv[2]);

	cleanup();
	return 0;
}


