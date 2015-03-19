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

void pixel_sort(){
	
	int byte_size = 3;
	if(png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGBA)
//		abort_("Error: Input file color type must be RGBA");
		byte_size = 4;
	
	printf("pixel size : %d\n",byte_size);

	/*for(y = 0; y < height; y++){
		

		png_byte* row  = row_pointers[y];

		qsort(row, width, byte_size, cmpwidthR);
		qsort(row, width, byte_size, cmpwidthG);
		qsort(row, width, byte_size, cmpwidthB);
		int j;
		for(x = width / 4, j = 0; x < width / 2 ; x++, j++){
			png_byte *ptrA = &row[x*byte_size];
			png_byte *ptrB = &row[(width-j-1)*byte_size];
			png_byte tmp[3];
			tmp[0] = ptrA[0];
			tmp[1] = ptrA[1];
			tmp[2] = ptrA[2];
			ptrA[0] = ptrB[0];
			ptrA[1] = ptrB[1];
			ptrA[2] = ptrB[2];
			ptrB[0] = tmp[0];
			ptrB[1] = tmp[1];
			ptrB[2] = tmp[2];
		}
	}
	qsort(row_pointers, height, sizeof(png_bytep), cmpheightR);
	qsort(row_pointers, height, sizeof(png_bytep), cmpheightG);
	qsort(row_pointers, height, sizeof(png_bytep), cmpheightB);*/

	qsort(flat, width * height, byte_size, cmpR);  
//	qsort(flat, width * height, byte_size, cmpwidthG);
//	qsort(flat, width * height, byte_size, cmpwidthB);
}


int main(int argc, char* argv[]){

	if(argc != 3)
		abort_("Usage : %s, <png_in> <png_out>", argv[0]);
	
	read_png_file(argv[1]);
	

	flat = (png_byte*)malloc(sizeof(png_byte) * height * (width * 3));

	for(y = 0; y < height; y++){
		png_byte* row = row_pointers[y];
		png_byte* flatrow = flat + width * y * 3;
		for(x = 0; x < width; x++){
			png_byte* ptrA = &row[x*3];
			png_byte* ptrB = &flatrow[x*3];
			ptrB[0] = ptrA[0];
			ptrB[1] = ptrA[1];
			ptrB[2] = ptrA[2];
		}
	}
	
	pixel_sort();

	for(y = 0; y < height; y++){
		png_byte* row = row_pointers[y];
		png_byte* flatrow = flat + width * y * 3;
		for(x = 0; x < width; x++){
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


int cmpR(const void* a, const void* b){
	return ((png_byte*)a)[0] - ((png_byte*)b)[0];
}
int cmpG(const void* a, const void* b){
	return ((png_byte*)a)[1] - ((png_byte*)b)[1];
}
int cmpB(const void* a, const void* b){
	return ((png_byte*)a)[2] - ((png_byte*)b)[2];
}

int cmpheightR(const void* a, const void* b){
	png_byte* A = *((png_bytep*)a);
	png_byte* B = *((png_bytep*)b);
	return cmpR(A, B);
}
int cmpheightG(const void* a, const void* b){
	png_byte* A = *((png_bytep*)a);
	png_byte* B = *((png_bytep*)b);
	return cmpG(A, B);
}
int cmpheightB(const void* a, const void* b){
	png_byte* A = *((png_bytep*)a);
	png_byte* B = *((png_bytep*)b);
	return cmpB(A, B);
}

void abort_(const char* s, ...){
	
	va_list args;
	va_start(args, s);
	vfprintf(stderr, s, args);
	fprintf(stderr, "\n");
	abort();
}


void read_png_file(char* filename){

	char header[8]; // 8 byte header
	
	//open file
	FILE* f = fopen(filename, "rb");
	if(!f)
		abort_("Error: [read png file] File %s could not be opened for reading", filename);
	//check header
	fread(header, 1, 8, f);
	if(png_sig_cmp(header,0,8))
		abort_("Error: [read png file] File %s could not be recognized as PNG image", filename);
	
	//initialize stuff
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png_ptr)
		abort_("Error: [read png file] png_create_read_struct failed");
	
	info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr)
		abort_("Error: [read png file] png_create_info_struct failed");

	if(setjmp(png_jmpbuf(png_ptr)))
		abort_("Error: init_io failed");
	
	png_init_io(png_ptr, f);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	
	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	
	color_type = png_get_color_type(png_ptr, info_ptr);
	bit_depth  = png_get_bit_depth(png_ptr, info_ptr);
	
	number_of_passes = png_set_interlace_handling(png_ptr);
	png_read_update_info(png_ptr, info_ptr);

	//read file 
	if( setjmp(png_jmpbuf(png_ptr)))
		abort_("Error: [read png file] during read_image");
	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	for(y = 0; y < height; y++)
		row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));

	png_read_image(png_ptr, row_pointers);
		
	fclose(f);

	//holy shit
}

void write_png_image(char* filename){
	
	FILE* f = fopen(filename, "wb");
	
	if(!f)
		abort_("Error: [write_png_image] could not open file %s for writing", filename);
	
	png_structp wrt_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!wrt_ptr)
		abort_("Error: [write_png_image] png_create_write_struct failed");
	
	if(setjmp(png_jmpbuf(wrt_ptr)))
		abort_("Error: [write_png_image] init_io failed");
	
	png_init_io(wrt_ptr, f);

	//write header
	if(setjmp(png_jmpbuf(wrt_ptr)))
		abort_("Error: [write_png_image] writing header failed");
	
	png_set_IHDR(wrt_ptr, info_ptr, width, height, bit_depth, color_type, 
		     PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(wrt_ptr, info_ptr);

	if(setjmp(png_jmpbuf(wrt_ptr)))
		abort_("Error: [write_png_image] writing bytes failed");
	
	png_write_image(wrt_ptr, row_pointers);

	//end write 
	if(setjmp(png_jmpbuf(wrt_ptr)))
		abort_("Error: [write_png_image] end of writing failed");
	
	png_write_end(wrt_ptr, NULL);

	//free memory
/*	for(y = 0; y < height; y++)
		free(row_pointers[y]);
	free(row_pointers);*/

	fclose(f);

	//holy shit 
}

void cleanup(){
	for(y = 0; y < height; y++)
		free(row_pointers[y]);
	free(row_pointers);

	free(flat);
}
