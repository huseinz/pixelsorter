#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <unistd.h>
#include <stdarg.h>
//#define png_jmpbuf(png_ptr) png_ptr->jmpbuf

int          width, height;
int          x, y;
int          number_of_passes;
png_byte     color_type;
png_byte     bit_depth;

png_structp  png_ptr;
png_infop    info_ptr;
png_bytep*   row_pointers;
png_byte*    flat;


void abort_(const char* s, ...);
void read_png_file(char* filename);
void write_png_image(char* filename);
void cleanup();
int cmpR(const void* a, const void* b);
int cmpG(const void* a, const void* b);
int cmpB(const void* a, const void* b);
void pixel_sort();
void rgb_to_hsl(png_byte* rgb, png_byte* hsl_ptr);
float _max(float r, float g, float b);
float _min(float r, float g, float b);



