/*----------------------------------------------
 * glitch.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 21 2025
 * Take a PPM file and glitch it
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "read_ppm.h"
#include "write_ppm.h"

/**
* Apply random glitch
* @param pixels from PPM
* @param w width
* @param h height
* @return void
*/
void applyGlitch(struct ppm_pixel* pixels, int w, int h) {
  for (int i = 0; i < w * h; i++) {
    struct ppm_pixel* pixel = &pixels[i];

    int shift = rand() % 2 + 1;
    pixel->red   = (pixel->red   << shift) & 0xFF;
    pixel->green = (pixel->green << shift) & 0xFF;
    pixel->blue  = (pixel->blue  << shift) & 0xFF;
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
    return 1;
  }
  srand(time(NULL));

  int w, h;
  struct ppm_pixel* pixels = read_ppm(argv[1], &w, &h);
  if (pixels == NULL) {
    fprintf(stderr, "Error reading image %s\n", argv[1]);
    return 1;
  }

  printf("Reading %s with width %d and height %d\n", argv[1], w, h);
  applyGlitch(pixels, w, h);
  char output_filename[1024];
  snprintf(output_filename, sizeof(output_filename), "%s-glitch.ppm", argv[1]);

  printf("Writing file %s\n", output_filename);
  write_ppm(output_filename, pixels, w, h);

  free(pixels);
  return 0;
}
