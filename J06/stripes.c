//write a program that makes N horizontal stripes in a 1024x1024 ppm imag using N threads
//choose random color for each stripe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "write_ppm.h"

struct thread_data {
  int starti;
  int endi;
  int width;
  struct ppm_pixel color;
  struct ppm_pixel* image;
};

void *start(void* userdata) {
  struct thread_data* data = (struct thread_data*) userdata;
  // todo: your code here

  //msg each time
  printf("Thread is coloring rows %d to %d with color %d %d %d\n",
    data->starti, data->endi - 1,
    data->color.red, data->color.green, data->color.blue);

  for (int y = data->starti; y < data->endi; y++) {
    for (int x = 0; x < data->width; x++) {
      int idx = y * data->width + x;
      data->image[idx] = data->color;
    }
  }
  return NULL;
}

int main(int argc, char** argv) {

  if (argc != 2)
  {
    printf("usage: %s <num>\n", argv[0]);
    exit(0);
  }
  int N = strtol(argv[1], NULL, 10);
  srand(time(NULL));
  int size = 1024;
  struct ppm_pixel* image = malloc(sizeof(struct ppm_pixel) * size * size);
  struct ppm_pixel* colors = malloc(sizeof(struct ppm_pixel) * N);
  pthread_t* threads = malloc(sizeof(pthread_t) * N);
  struct thread_data* data = malloc(sizeof(struct thread_data) * N);

  int rows_per_thread = size/N;

  for (int i = 0; i < N; i++) {
    //assign a random color for each stripe/thread
    struct ppm_pixel color = {
      .red = rand() % 256,
      .green = rand() % 256,
      .blue = rand() % 256
    };

    data[i].starti = i * rows_per_thread;
    data[i].endi = (i + 1) * rows_per_thread;
    data[i].width = size;
    data[i].color = color;
    data[i].image = image;
    pthread_create(&threads[i], NULL, start, &data[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  write_ppm("stripes.ppm", image, size, size);

  free(image);
  free(threads);
  free(data);
  return 0;
}
