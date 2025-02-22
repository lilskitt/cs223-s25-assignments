/*----------------------------------------------
 * test_read.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 21 2025
 * This file writes a short test that calls read_ppm function and prints the contents of feep-raw.ppm
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  int w, h;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);

  if (pixels == NULL) {
    fprintf(stderr, "Failed to read PPM file\n");
    return 1;
  }

  // todo: print out the grid of pixels
  printf("Testing file feep-raw.ppm: %d %d\n", w, h);
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      struct ppm_pixel* pixel = &pixels[y * w + x];  // Access the pixel at (x, y)
      printf("(%d,%d,%d) ", pixel->red, pixel->green, pixel->blue);
    }
    printf("\n");
  }

  free(pixels);
  return 0;
}

