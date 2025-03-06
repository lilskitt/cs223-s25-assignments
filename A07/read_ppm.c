/*----------------------------------------------
 * read_ppm.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 21 2025
 * Implements a function that can read PPM files stored in binary format
 ---------------------------------------------*/
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "read_ppm.h"
 
 // Choose *one* to implement (do not remove the other one!)


 /**
 * Read in a PPM file in binary format
 * @param w pointer argument for returning the width of the image
 * @param h pointer argument for returning the height of the image
 * @return returns a 1D array of ppm_pixel, or NULL, if the file cannot be loaded
 */
 struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
   FILE* file = fopen(filename, "rb");
   if (file == NULL) {
     return NULL;
   }
 
   //read the magic number which should be P6
   char magic_number[3];
   //fscanf reads formatted input from file, returns number of items read
   if (fscanf(file, "%2s", magic_number) != 1 || magic_number[0] != 'P' || magic_number[1] != '6') {
     fclose(file);
     return NULL;
   }
 
   char line[1024];
   //fgets reads a line from file and stores it
   fgets(line, sizeof(line), file); //read the newline after P6
   if (fgets(line, sizeof(line), file)) {
     if (line[0] != '#') {
       fclose(file);
       return NULL;
     }
   }
 
   //width and height check
   //sscanf is for formatted input, returns number of items read so it should be 2
   if (fgets(line, sizeof(line), file) == NULL || sscanf(line, "%d %d", w, h) != 2) {
     fclose(file);
     return NULL;
   }
 
   //max color value check
   int max_color_value;
   if (fscanf(file, "%d", &max_color_value) != 1 || max_color_value != 255) {
     fclose(file);
     return NULL;
   }
 
   fgetc(file); //to skip whitespace after max
 
   //allocate memory for the pixel data
   int total_pixels = (*w) * (*h); //differentiate multiplication
   struct ppm_pixel* pixels = (struct ppm_pixel*)malloc(total_pixels * sizeof(struct ppm_pixel));
   if (pixels == NULL) {
     fclose(file);
     return NULL;
   }
 
   //fread reads COUNT elements of SIZE bytes each 
   //from the FILE into the memory location pointed to by PTR
   size_t bytes_read = fread(pixels, sizeof(struct ppm_pixel), total_pixels, file);
   if (bytes_read != total_pixels) {
     free(pixels);
     fclose(file);
     return NULL;
   }
 
   fclose(file);
   return pixels;
 }
 
 struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
   return NULL;
 }
 