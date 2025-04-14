#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define N 10

int produce_item() {
    return rand() % 10;
}

void consume_item(int item) {
    printf("Received item: %d\n", item);
}

int main() {
  // todo
  return 0;
}

