/*----------------------------------------------
 * warmup.c
 * Author: Lola Peyrouse-Bremer
 * Date: March 28 2025
 * Implements a program that spawns processes according to the diagram
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  printf("%d] A0\n", getpid());
  pid_t pidB = fork();
  if (pidB == 0) { //child
    printf("%d] B0\n", getpid());
    pid_t pidB1 = fork();
    if (pidB1 == 0) { //child
      printf("%d] B1\n", getpid());
      printf("%d] Bye\n", getpid());
      exit(0);
    }
    wait(NULL); //wait fro grandchild
    exit(0);
  }
  wait(NULL); //wait fr child
  printf("%d] C0\n", getpid());
  printf("%d] Bye\n", getpid());
  pid_t pidC = fork();
  if (pidC == 0) { //child again
    printf("%d] C1\n", getpid());
    exit(0);
  }
  wait(NULL); //final wait
  printf("%d] Bye\n", getpid());
  return 0;
}
