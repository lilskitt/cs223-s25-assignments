/*----------------------------------------------
 * repear.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 4, 2025
 * Implements a program that asks for a string and a number then repeats that string that number of times
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("Enter a word: ");
  char s[32];
  scanf("%s", s);
  printf("Enter a number: ");
  int n;
  scanf("%d", &n);

  //dynamic allocation of array so that it can get bigger depending on # of repeats
  char * word = malloc(strlen(s) * n + 1);
  word[0] = '\0';

  if (n > 1000) {
    printf("Cannot allocate new string. Exiting...\n");
  } else {
    //concatenate string to repeat n number of times
    for(int i = 0; i < n; i++) {
      strcat(word, s);
    }
    printf("Your word is %s\n", word);
  }
  free(word);
  return 0;
}
