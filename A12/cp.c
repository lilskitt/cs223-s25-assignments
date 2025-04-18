/*----------------------------------------------
 * cp.c
 * Author: Lola Peyrouse-Bremer
 * Date: April 18 2025
 * Implement the producer/consumer demo from class
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h> //singal handling

#define N 10

//globals!
int buffer[N];
int in = 0;
int out = 0;
int count = 0;

//declare and initialize mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//condition var to wait for buffer to not be FULL
//producer
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

//condition var to wait for the buffer to not be EMPTY
//consumer
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

int produce_item() {
  return rand() % 10;
}

void consume_item(int item) {
  printf("Received item: %d\n", item);
}

/**
 * producer - makes items and puts them into buffer
 * @return void
 */
void *producer() {
  while (1) {
    //producer produces item
    int item = produce_item();

    //"Use sleep(1.0) to slow the production of values and make the output of your program easier to read"
    sleep(1);

    //lock before accessing shared buffer
    pthread_mutex_lock(&mutex);

    //wait if full
    while (count == N) {
      pthread_cond_wait(&not_full, &mutex);
    }

    //add item to buffer
    buffer[in] = item;
    in = (in + 1) % N;
    count++;

    //send signal to say item is ther
    pthread_cond_signal(&not_empty);

    //unlock when done
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

/**
 * consumer - removes items from buffer
 * @return void
 */
void *consumer() {
  while (1) {
    //lock before accessing shared buffer
    pthread_mutex_lock(&mutex);

    //wait if empty buffer
    while (count == 0) {
      pthread_cond_wait(&not_empty, &mutex);
    }

    //remove item
    int item = buffer[out];
    out = (out + 1) % N;
    count--;

    //send signal to say there is space available
    pthread_cond_signal(&not_full);

    //unlock after done
    pthread_mutex_unlock(&mutex);

    //item gets consumed after
    consume_item(item);
  }
  return NULL;
}

int main() {
  // todo

  //random num generator
  srand(time(NULL)); 

  //creating producer and consumer threads
  pthread_t prod, cons;
  pthread_create(&prod, NULL, producer, NULL);
  pthread_create(&cons, NULL, consumer, NULL);

  //join when ^C
  pthread_join(prod, NULL);
  pthread_join(cons, NULL);
  return 0;
}

