#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
  FILE* fp = fopen(filename, "wb");
  if (!fp) {
    printf("Error opening output file");
    return;
  }

  fprintf(fp, "P6\n%d %d\n255\n", w, h); //print to file
    
  size_t size = w * h;
  if (fwrite(pixels, sizeof(struct ppm_pixel), size, fp) != size) {
    printf("Error writing pixel data.\n");
  }

  fclose(fp);
}

void write_ppm_2d(const char* filename, struct ppm_pixel** pxs, int w, int h) {
}
