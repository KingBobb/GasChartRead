#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include "jpeglib.h"  

#define PUT_2B(array,offset,value)  (array[offset] = (char)((value)& 0xFF), \
	array[offset + 1] = (char)(((value) >> 8) & 0xFF))
#define PUT_4B(array,offset,value)  (array[offset] = (char)((value)& 0xFF), \
	array[offset + 1] = (char)(((value) >> 8) & 0xFF), \
	array[offset + 2] = (char)(((value) >> 16) & 0xFF), \
	array[offset + 3] = (char)(((value) >> 24) & 0xFF))

int read_jpeg_file(const char *input_filename, const char *output_filename);