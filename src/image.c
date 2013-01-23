#include "image.h"


#define abort_(str) {printf(str);return 1;}

int save_image(char* file_name,int width, int height, unsigned char* image)
{
		int Bpp=4;
		int r=0;
		png_structp png_ptr;
		png_infop info_ptr;
		static png_FILE_p fp;

        /* create file */
        fp = fopen(file_name, "wb");
        if (!fp)
                abort_("[write_png_file] File  could not be opened for writing");


        /* initialize stuff */
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
                abort_("[write_png_file] png_create_write_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
                abort_("[write_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during init_io");

        png_init_io(png_ptr, fp);


        /* write header */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing header");

        png_set_IHDR(png_ptr, info_ptr, width, height,
                     8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        png_write_info(png_ptr, info_ptr);

		png_set_bgr(png_ptr);

        /* write bytes */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing bytes");

        //png_write_image(png_ptr, row_pointers);
		for(r=0;r<height;r++)
		png_write_row(png_ptr,(const unsigned char*)(&image[r*width*Bpp]));


        /* end write */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during end of write");

        png_write_end(png_ptr, NULL);

        /* cleanup heap allocation */
		/*
        for (y=0; y<height; y++)
                free(row_pointers[y]);
        free(row_pointers);
		*/

        fclose(fp);
		return 0;
}
