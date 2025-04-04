/*----------------------------------------------
 * marco_polo.c
 * Author: Lola Peyrouse-Bremer
 * Date: April 4 2025
 * Implements a program that uses signals to coordinate between two processes (exampl on assignment sheet) 
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //to be able to use fork() and kill() and other
#include <signal.h> //for signaling stuff
#include <string.h>
#include <sys/wait.h> //to be able to use wait()

pid_t child_pid = 0;
pid_t parent_pid = 0;

void parent_handler(int sig) {
  printf("Polo [%d]\n", getpid());
  fflush(stdout); //forces the output
}

void child_handler(int sig) {
  printf("Marco [%d]\n", getpid());
  fflush(stdout); //forces the output
  kill(parent_pid, SIGALRM);
}

int main() {
  parent_pid = getpid();
  child_pid = fork();

  if (child_pid < 0) {
    printf("fork failed");
    exit(1);
  }

  if (child_pid == 0) { //only runs if in child
    signal(SIGALRM, child_handler); //so func runs when sigalrm is given
    signal(SIGTERM, SIG_DFL); //resets termination to its default so term works

    //loop to wait for signal to print marco forever
    while (1) {
      pause();
    }
  } else { //only runs if in parent
    signal(SIGALRM, parent_handler);
    printf("Parent is %d\n", parent_pid);
    printf("Press 'm' to start Marco Polo, 'q' to quit.\n");
    char input;

    while (1) { //parent waits for user input m/q and send signals accordingly
      input = getchar();

      if (input == 'm') {
        //'m' should send the initial signal that triggers the child to say "Marco"
        kill(child_pid, SIGALRM);
      } else if (input == 'q') {
        //'q' should send quit the application. This command should also send SIGTERM to the child, so the child also exits.
        kill(child_pid, SIGTERM);
        break;
      }
    }
    //waiting for child to terminate
    wait(NULL);
  }
  return 0;
}
