#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 32

int main() {
    int boolean;
    int num_adjectives;
    char temp[MAXSIZE];
    //ask user for a boolean
    printf("Boolean: ");
    scanf("%d", &boolean);

    //ask for number of adjectives to recieve
    printf("Number: ");
    scanf("%d", &num_adjectives);

    //ask for adjectives
    //using malloc to allocate space (so we can reverse order later)
    char **adjectives = malloc(num_adjectives * sizeof(char *));

    for (int i = 0; i < num_adjectives; i++) {
      printf("Adjective: ", i + 1);
      scanf("%s", temp);
      adjectives[i] = malloc((strlen(temp) + 1) * sizeof(char));
      strcpy(adjectives[i], temp);
    }

    //print out sentence using adjectives (format: commas between adjectives, boolean decides "true" or "false" in sentence, list adj in reverse order)
    printf("You are the most ");
    
    //reverse order list adjectives
    for (int i = num_adjectives - 1; i >= 0; i--) {
      printf("%s", adjectives[i]); 
      if (i == 1 && num_adjectives > 2) {
        printf(", and "); 
      } else if (i == 1 && num_adjectives < 3) {
        printf(" and ");
      } else if (i > 0) {
        printf(", ");
      }
    }

    //continue sentence
    printf(" person that I know and you know it's ");
    if (boolean) {
      printf("true!\n");
    } else {
      printf("false!\n");
    }

    //free
    for (int i = 0; i < num_adjectives; i++) {
      free(adjectives[i]);
    }
    free(adjectives);
    return 0;
}
