#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100

// your code here

int main(int argc, char *argv[]) {
  srand(time(0));

  int M[SIZE*SIZE];
  int u[SIZE];
  int result[SIZE];
  int result_threads[SIZE];
   
  for (int i = 0; i < SIZE; i++) {
    u[i] = rand() % 10 - 5;
    result[i] = 0;
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int value = rand() % 10 - 5;
      M[i*SIZE + j] = value;
      result[i] += value * u[j];
    }
  }

  // TODO: Implement your thread solution here
  printf("Test with 4 threads\n");



  int error = 0;
  for (int i = 0; i < SIZE; i++) {
    error += abs(result[i] - result_threads[i]);
  }
  printf("Error between ground truth and multithreaded version: %d\n", error);

  return 0;
}
