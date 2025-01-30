/***************************************************
 * password.c
 * Author: Lola Peyrouse-Bremer
 * Implements a game to make passwords out of regular words
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("Enter a word: ");

  //allocate an array of 10 chars on the heap
  char *response = malloc(sizeof(char) * 10);
  scanf("%s", response);

  char * pass = response;
  int len = strlen(pass);

//iterate through input to change e's to 3's, l's to 1's, and a's to @'s
  for (int i = 0; i < len; i++) {
    if (response[i] == 'e') {
      pass[i] = '3';
    }
    if (response[i] == 'l') {
      pass[i] = '1';
    }
    if (response[i] == 'a') {
      pass[i] = '@';
    }
  }
  printf("Your bad password is %s\n", pass);
  
  free(response);
  return 0;
}
