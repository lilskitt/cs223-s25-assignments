/*----------------------------------------------
 * decode.c
 * Author: Lola Peyrouse-Bremer
 * Date: March 7 2025
 * Implements a program that reads PPM file and outputs its secret msg
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

/**
 * Decodes the message
 * @param pixels array of ppm_pixel structs from file
 * @param w is width
 * @param h is height
 */
void decode(struct ppm_pixel *pixels, int w, int h) {
  unsigned char currentChar = 0;
  int bitCount = 0;
  int pixelCount = w * h;

  //loop thru each pixel and get  least significant bit from R, G, B
  for (int i = 0; i < pixelCount; i++) {
    struct ppm_pixel *pixel = &pixels[i];
    for (int j = 0; j < 3; j++) {
      unsigned char lsb; 
      //get which color
      if (j == 0) {
        lsb = pixel->red & 1;  //get lsb of the red
      } else if (j == 1) {
        lsb = pixel->green & 1;  //get lsb of the green
      } else {
        lsb = pixel->blue & 1;  //get lsb of the blue
      }

      //shift + store
      currentChar = (currentChar << 1) | lsb;
      bitCount++;

      //if done print the current character and reset
      if (bitCount == 8) {
        if (currentChar == '\0') {
          return;
        }
        printf("%c", currentChar);
        bitCount = 0;
        currentChar = 0;
      }
    } // end for loop inner
  } //end for loop outer
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }

  char *filename = argv[1];
  struct ppm_pixel *pixels = NULL;
  int w = 0, h = 0;

  pixels = read_ppm(filename, &w, &h);
  if (pixels == NULL) {
    printf("Error reading %s\n", filename);
    return 1;
  }

  printf("Reading %s with width %d and height %d\n", filename, w, h);
  printf("Max number of characters in the image: %d\n", (w * h * 3) / 8);
  decode(pixels, w, h);
  free(pixels);
  return 0;
}

