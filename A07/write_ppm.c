/*----------------------------------------------
 * write_ppm.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 21 2025
 * Implements function to write in a PPM file in binary format
 ---------------------------------------------*/
 #include "write_ppm.h"
 #include <stdio.h>
 #include <string.h>
 
 // implement *one* (but do not remove the other one)!
 
 /**
 * Read in a PPM file in binary format
 * @param filename the file to save to
 * @param pixels a 1D array of ppm_pixel to save
 * @param w width of the image
 * @param h height of the image
 * @return returns a 1D array of ppm_pixel, or NULL, if the file cannot be loaded
 */
 void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
   FILE* file = fopen(filename, "wb");
   if (file == NULL) {
     return; //failed
   }
 
   //write header with magic number, w, h, and max
   fprintf(file, "P6\n");
   fprintf(file, "%d %d\n", w, h);
   fprintf(file, "255\n");
 
   // write the pixel data as binary
   //size_t --> only positive, fwrite --> writes pixel stuff in binary
   size_t bytes_written = fwrite(pixels, sizeof(struct ppm_pixel), w * h, file);
   if (bytes_written != (size_t)(w * h)) {
     fclose(file);
     return; //failed
   }
 
   fclose(file);
 }
 
 void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
 
 }
 