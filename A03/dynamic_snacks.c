/*----------------------------------------------
 * dynamic_snacks.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 4, 2025
 * Implements a program that allows users to add to snackbarvalgri
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//define what snacks are, what they hold
struct Snacks {
  char name[64];
  float cost;
  int quantity;
};

/**
* Void
* @param arr array of snacks
* @param a index in arr
* @return void
*/
void getSnack(struct Snacks * arr, int a) {
  //user input is assigned to new snack
  struct Snacks new;
  printf("Enter a name: ");
  scanf("%s", new.name);
  printf("Enter a cost: ");
  scanf("%f", &new.cost);
  getchar();
  printf("Enter a quantity: ");
  scanf("%d", &new.quantity); 
  getchar();
  arr[a] = new;
}

int main() {
  printf("Enter a number of snacks: ");
  int inputNum;
  scanf("%d", &inputNum);
  getchar(); //each getchar() call clears the buffer

  //create array of pointers for snacks
  struct Snacks * snackList = malloc(inputNum * sizeof(struct Snacks));
  if (snackList == NULL) {
    printf("Memory allocation failed!\n");
    return 1;
  }

  //only add the number of snacks as many times as user says
  int i = 0;
  while (i < inputNum) {
    getSnack(snackList, i);
    i++;
  }

  //print all the snacks
  printf("\nWelcome to Dynamic Donna's Snack Bar \n");
  for (int i = 0; i < inputNum; i++) {
    printf("%d) %s    cost: $%.2f   quantity: %d\n", i, snackList[i].name, snackList[i].cost, snackList[i].quantity);
  }
  free(snackList);
  return 0;
}
