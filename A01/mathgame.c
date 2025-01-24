/***************************************************
 * mathgame.c
 * Author: Lola Peyrouse-Bremer 
 * Implements a math game
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
  printf("Welcome to Math Game!\nHow many rounds do you want to play? ");

  int response = 0;
  scanf("%d", &response);

  //keep count of correct answers
  int count = 0;
  srand(time(NULL));

  for (int i = 1; i <= response; i++) {
    //generate random ints to add
    int a = rand() % 10;
    int b = rand() % 10;

    //promp the question and get input
    printf("%d + %d = ", a, b);
    int answer = 0;
    scanf("%d", &answer);

      //check if it's correct
      if (a + b == answer) {
        count++;
        printf("correct\n");
      } else {
        printf("incorrect\n");
      }
  }
  printf("You got %d/%d correct!", count, response);
  return 0;
}
