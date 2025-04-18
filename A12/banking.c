/*----------------------------------------------
 * banking.c
 * Author: Lola Peyrouse-Bremer
 * Date: April 18 2025
 * Edit the file, banking.c, so it correctly handles a series of transfers between two accounts
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h> //to sleep

struct account {
  float balance;
  pthread_mutex_t lock;
  pthread_cond_t cond;
};

struct thread_data {
  struct account* fromAccount;
  struct account* toAccount;
  float amount;
};

void *Transfer(void *args){
  struct thread_data* data = (struct thread_data*) args;
  struct account* fromAcct = data->fromAccount; 
  struct account* toAcct = data->toAccount; 
  float amt = data->amount;

  for (int i = 0; i < 1000; i++) {
    struct account *first, *second;

    //to avoid deadlock lock accounts in order
    if (fromAcct < toAcct) {
      first = fromAcct;
      second = toAcct;
    } else {
      first = toAcct;
      second = fromAcct;
    }

    pthread_mutex_lock(&first->lock);
    pthread_mutex_lock(&second->lock);

    //wait only if not enough funds
    while (fromAcct->balance < amt) {
      pthread_cond_wait(&fromAcct->cond, &second->lock);
    }

    fromAcct->balance -= amt;
    assert(fromAcct->balance >= 0);
    
    toAcct->balance += amt;

    //printf("Transferred %.2f from %p to %p\n", amt, (void*)fromAcct, (void*)toAcct);

    //signaling that fromAcct has enough funds
    pthread_cond_signal(&fromAcct->cond);
    pthread_cond_signal(&toAcct->cond);

    pthread_mutex_unlock(&second->lock);
    pthread_mutex_unlock(&first->lock);

    //added because thread wasn finishing
    usleep(1000);
    }

  return NULL;
}

int main() {
  struct account A, B;
  A.balance = 5000;
  B.balance = 5000;
  pthread_mutex_init(&(A.lock), NULL);
  pthread_mutex_init(&(B.lock), NULL);
  pthread_cond_init(&A.cond, NULL);
  pthread_cond_init(&B.cond, NULL);

  printf("Starting balance A: %.2f\n", A.balance);
  printf("Starting balance B: %.2f\n", B.balance);

  struct thread_data dataA;
  dataA.fromAccount = &B;
  dataA.toAccount = &A;
  dataA.amount = 1000;
  
  struct thread_data dataB;
  dataB.fromAccount = &A;
  dataB.toAccount = &B;
  dataB.amount = 1000;

  //actually running threads
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, Transfer, &dataA);
  pthread_create(&thread2, NULL, Transfer, &dataB);

  // wait for both threads to complete
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  // Should be the same because we transfer the same amount between both
  printf("Ending balance A: %.2f\n", A.balance);
  printf("Ending balance B: %.2f\n", B.balance);

  pthread_mutex_destroy(&A.lock);
  pthread_mutex_destroy(&B.lock);
  pthread_cond_destroy(&A.cond);
  pthread_cond_destroy(&B.cond);
  return 0;
}

