#if !defined(IMAGE)
#define IMAGE

#if defined(WIN32)
	#define ZLIB_WINAPI
#endif

#include <zlib.h>
#include <png.h>
#include <math.h>
#include <stdio.h>

int save_image(char* file_name,int width, int height, unsigned char* image);

#endif