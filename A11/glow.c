/*----------------------------------------------
 * glow.c
 * Author: Lola Peyrouse-Bremer
 * Date: April 11 2025
 * Implements a single-threaded program that applies a glow effect to the image "earth-small.ppm"
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

#define THRESHOLD 200
#define BOX_SIZE 25
#define INPUT_FILE "earth-small.ppm"
#define OUTPUT_FILE "glow.ppm"

/**
 * apply the filter. 
 * @param input without glow
 * @param outpit with glow
 * @param w width
 * @param h height
 * @return void
 */
void glow(struct ppm_pixel* input, struct ppm_pixel* output, int w, int h) {
  int radius = BOX_SIZE / 2;
  int image_size = w * h;

  //copy original over
  memcpy(output, input, image_size * sizeof(struct ppm_pixel));

  //BE THOROUGH
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      int idx = y * w + x;

      //computing brightness
      int r = input[idx].red;
      int g = input[idx].green;
      int b = input[idx].blue;
      int brightness = (r + g + b) / 3;

      if (brightness < THRESHOLD) continue;

      //apply filter
      int r_sum = 0, g_sum = 0, b_sum = 0, count = 0;

      for (int dy = -radius; dy <= radius; dy++) {
        int ny = y + dy;

        if (ny < 0 || ny >= h) continue;

        for (int dx = -radius; dx <= radius; dx++) {
          int nx = x + dx;
          if (nx < 0 || nx >= w) continue;

          int nidx = ny * w + nx;
          r_sum += input[nidx].red;
          g_sum += input[nidx].green;
          b_sum += input[nidx].blue;
          count++;
        }
      }
      //putting into output struct (changes save bc pointer)
      if (count > 0) {
        output[idx].red     = r_sum / count;
        output[idx].green = g_sum / count;
        output[idx].blue = b_sum / count;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  // todo: your code here
  // compute image

  int w, h;
  struct ppm_pixel* input = read_ppm(INPUT_FILE, &w, &h); //deref!!
  if (!input) {
    printf("Error reading input file.\n");
    return 1;
  }

  struct ppm_pixel* output = malloc(w * h * sizeof(struct ppm_pixel)); //allocating memory for glow version

  if (!output) {
    printf("Memory allocation failed.\n");
    free(output);
    return 1;
  }

  glow(input, output, w, h); //caling it
  write_ppm(OUTPUT_FILE, output, w, h); //writting it

  //cleanup
  free(input);
  free(output);
  return 0;
}
