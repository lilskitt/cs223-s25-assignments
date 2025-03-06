/*----------------------------------------------
 * encode.c
 * Author: Lola Peyrouse-Bremer
 * Date: March 7 2025
 * Implements a program that reads PPM file and asks user for secret msg to hide in it
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

/**
 * Encodes secret message into given ppm
 * @param pixels original ppm
 * @param w width
 * @param h height
 * @param message from user input
 */
void encode(struct ppm_pixel *pixels, int w, int h, const char *message) {
  int pixelCount = w * h;
  int messageLength = strlen(message);

  //calculate # of bits needed
  int maxChars = (pixelCount * 3) / 8;  //3 for each color RGB
  int bitIndex = 0;  //keeping track of current bit
  for (int i = 0; i < messageLength; i++) {
    unsigned char currentChar = message[i];
    //loop thru each bit
    for (int j = 0; j < 8; j++) { 
      //finding the pixel to encode to
      int pixelIndex = bitIndex / 3;
      int colorIndex = bitIndex % 3;  //0 is red 1 is green 2 is blue

      struct ppm_pixel *pixel = &pixels[pixelIndex];

      unsigned char bit = (currentChar >> (7 - j)) & 1;
      if (colorIndex == 0) {
        pixel->red = (pixel->red & 0xFE) | bit;
      } else if (colorIndex == 1) {
        pixel->green = (pixel->green & 0xFE) | bit;
      } else {
        pixel->blue = (pixel->blue & 0xFE) | bit;
      }

       bitIndex++;
    }
  } //end outer loop
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }

  //file stuff
  char *filename = argv[1];
  int w = 0, h = 0;
  struct ppm_pixel *pixels = read_ppm(filename, &w, &h);
  if (pixels == NULL) {
    printf("Error reading %s\n", filename);
    return 1;
  }

  //print image size + max length
  printf("Reading %s with width %d and height %d\n", filename, w, h);
  int maxChars = (w * h * 3) / 8;
  printf("Max number of characters in the image: %d\n", maxChars);

  //user input secret msg
  char *message = malloc(maxChars + 1);
  printf("Enter a phrase: ");
  fgets(message, sizeof(message), stdin); //stdin with <

  encode(pixels, w, h, message);

  //new file by appending "-encoded"
  char outputFilename[256];
  snprintf(outputFilename, sizeof(outputFilename), "%s-encoded.ppm", filename);

  //new file gets the encoded image
  write_ppm(outputFilename, pixels, w, h);
  printf("Writing file %s\n", outputFilename);
  free(message);
  free(pixels);
  return 0;
}

