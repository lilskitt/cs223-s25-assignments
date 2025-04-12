/*----------------------------------------------
 * glow_multithreaded.c
 * Author: Lola Peyrouse-Bremer
 * Date: April 11 2025
 * Implements a multi-threaded program that applies a glow effect to the images of earth
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

//NO GLOBAL VARIABLES

struct thread_data {
  int thread_id;
  int N;
  int w;
  int h;
  int threshold;
  int blursize;
  struct ppm_pixel* input;
  struct ppm_pixel* output;
};

/**
 * apply the filter. 
 * @param usr use generic ptr
 * @return void
 */
void* glow(void* usr) {
  struct thread_data* data = (struct thread_data*) usr; //generic pointer casted

  //assign section for thread to process
  int start_row = (data->h / data->N) * data->thread_id;
  int end_row = (data->h / data->N) * (data->thread_id + 1);
  int radius = data->blursize / 2; //radius of the blur filter (half the box size)
  printf("Thread sub-image block: cols (0, %d) to rows (%d,%d)\n", data->w, start_row, end_row);

  //loop thru section of pixels
  for (int y = start_row; y < end_row; y++) {
    for (int x = 0; x < data->w; x++) {
      //brightness
      int idx = y * data->w + x;
      int r = data->input[idx].red;
      int g = data->input[idx].green;
      int b = data->input[idx].blue;
      int brightness = (r + g + b) / 3;

      //if dark, just cpy
      if (brightness < data->threshold) {
        data->output[idx] = data->input[idx];
        continue;
      }

      int r_sum = 0, g_sum = 0, b_sum = 0, count = 0;

      //apply blur alterations
      for (int dy = -radius; dy <= radius; dy++) {
        int ny = y + dy;
        if (ny < 0 || ny >= data->h) continue;
        for (int dx = -radius; dx <= radius; dx++) {
          int nx = x + dx;
          if (nx < 0 || nx >= data->w) continue;

          int nidx = ny * data->w + nx;
          r_sum += data->input[nidx].red;
          g_sum += data->input[nidx].green;
          b_sum += data->input[nidx].blue;
          count++;
        }
      }

      //assigning alterations
      if (count > 0) {
        data->output[idx].red = r_sum / count;
        data->output[idx].green = g_sum / count;
        data->output[idx].blue = b_sum / count;
      }
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  int N = 4;
  int threshold = 200;
  int blursize = 24;
  const char* filename = "earth-small.ppm";

  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1) {
    switch (opt) {
      case 'N': N = atoi(optarg); break;
      case 't': threshold = atof(optarg); break;
      case 'b': blursize = atof(optarg); break;
      case 'f': filename = optarg; break;
      case '?': printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]); break;
    }
  }
  // todo: your code here
  // compute image

  int w, h;
  struct ppm_pixel* input = read_ppm(filename, &w, &h); //read
  if (!input) {
    printf("Failed to read input image.\n");
    return 1;
  }

  struct ppm_pixel* output = malloc(w * h * sizeof(struct ppm_pixel)); //alloctae
  if (!output) {
    printf("Failed to allocate output image.\n");
    free(input);
    return 1;
  }

  //N threads and its data (N is 4 to test)
  pthread_t threads[N]; 
  struct thread_data thread_args[N];

  //calling threads to do the work
  for (int i = 0; i < N; i++) {
    thread_args[i] = (struct thread_data) {
      .thread_id = i, //should be the same as thread_args[i].thread_id = i; and all in one line is crazy
      .N = N,
      .w = w,
      .h = h,
      .threshold = threshold,
      .blursize = blursize,
      .input = input,
      .output = output
    };
    pthread_create(&threads[i], NULL, glow, &thread_args[i]);
  }

  //join all threads at end
  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  write_ppm("glow.ppm", output, w, h); //writing
  
  //cleanup malloced stuff
  free(input);
  free(output);
  return 0;
}
