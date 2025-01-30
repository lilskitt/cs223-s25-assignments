/***************************************************
 * cypher.c
 * Author: Lola Peyrouse-Bremer 
 * Implements a program that asks the user for a word and then encodes it
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  //gathering word and designated shift
  printf("Enter a word: ");
  char * word = malloc(sizeof(char) * 10);
  scanf("%s", word);
  printf("Enter a shift: ");
  int shift = 0;
  scanf("%d", &shift);

  char * cypher = malloc(sizeof(char) * 10);
  strcpy(cypher, word);
  for(int i = 0; i < strlen(word); i++){
    //account for shifts outside of the alphabet
    int plus = word[i] + shift;
    if(plus < 97) {
      int difference = plus - 97;
      cypher[i] = 122 + difference;
    } else if (plus > 122) {
      int difference = plus - 122;
      cypher[i] = 97 + difference;
    } else {
      cypher[i] = word[i] + shift;
    }
  }
  
  printf("Your cypher is: %s\n", cypher);

  return 0;
}
