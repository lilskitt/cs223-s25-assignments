/*----------------------------------------------
 * ascii_image.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 21 2025
 * Displays PPM image as ASCII art
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

/**
* Converts intensity to ASCII
* @param intensity 
* @return char in ASCII
*/
char intensify(int intensity) {
  if (intensity <= 25) return '@';
  else if (intensity <= 50) return '#';
  else if (intensity <= 75) return '%';
  else if (intensity <= 100) return '*';
  else if (intensity <= 125) return 'o';
  else if (intensity <= 150) return ';';
  else if (intensity <= 175) return ':';
  else if (intensity <= 200) return ',';
  else if (intensity <= 225) return '.';
  else return ' ';  // for intensity > 225
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
    return 1;
  }

  int w, h;
  struct ppm_pixel *pixels = read_ppm(argv[1], &w, &h);
  if (pixels == NULL) {
    fprintf(stderr, "Error reading image %s\n", argv[1]);
    return 1;
  }

  printf("Reading %s with width %d and height %d\n", argv[1], w, h);

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel *pixel = &pixels[i * w + j];
      int intensity = (pixel->red + pixel->green + pixel->blue) / 3;
      printf("%c", intensify(intensity));
    }
    printf("\n");
  }

  free(pixels);
  return 0;
}
