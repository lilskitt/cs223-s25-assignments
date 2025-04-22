#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
  printf("AHHHHH IM SHOT!!!!\n");
  exit(0);
}

int main() {
  //write program that infinitely loops until user sends SIGINT signal by typing ctrl C
  //register a handler that prints "I've been shot" before exiting
  signal(SIGINT, handle_sigint);
  while (1) {
    pause(); //to wait for signal
  }
  return 0;
}
