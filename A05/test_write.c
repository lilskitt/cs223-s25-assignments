/*----------------------------------------------
 * test_write.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 21 2025
 * Test the write_ppm function
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  int w, h;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);
  if (pixels == NULL) {
    printf("Error reading PPM file\n");
    return 1;
  }

  //write  pixels to test.ppm
  write_ppm("test.ppm", pixels, w, h);

  //verify success in writing 
  struct ppm_pixel* new_pixels = read_ppm("test.ppm", &w, &h);
  if (new_pixels == NULL) {
    printf("Error reading the written PPM file\n");
    free(pixels);
    return 1;
  }

  //print data
  printf("Testing file test.ppm: %d %d\n", w, h);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel* pixel = &new_pixels[i * w + j];
      printf("(%d,%d,%d) ", pixel->red, pixel->green, pixel->blue);
    }
    printf("\n");
  }

  free(pixels);
  free(new_pixels);

  return 0;
}
