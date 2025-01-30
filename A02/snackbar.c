/***************************************************
 * snackbar.c
 * Author: Lola Peyrouse-Bremer 
 * Implements a program that that maintains a list of snacks available for purchase
 */
#include <stdio.h>
#include <string.h>

//define what snacks are, what they hold
struct Snacks {
  char name[64];
  float cost;
  int quantity;
};

struct Snacks puffs, cheese, beans;

int main() {
  //define three snacks and store them in array
  struct Snacks snackList[3];
  snackList[0] = (struct Snacks) {"Coco Puffs", 1.50, 4};
  snackList[1] = (struct Snacks) {"Manchego Cheese", 15.50, 6};
  snackList[2] = (struct Snacks) {"Magic Beans", 0.50, 0};

  printf("Welcome to Lola's Questionable Snack Bar.\nHow much money do you have? ");
  float amount = 0;
  scanf("%f", &amount);

  //print contents of snackList
  for (int i = 0; i < 3; i++) {
    printf("%d)  %s cost: %.2f  quanitity: %d\n", i, snackList[i].name, snackList[i].cost, snackList[i].quantity);
  }

  //ask for what they want here, respond according to how much money they have
  printf("What snack would you like to buy? [0,1,2] ");
  int buy = 0;
  scanf("%d", &buy);

  //check for inventory + enough money + transactions
  if(snackList[buy].quantity == 0) {
    printf("Sorry, we are out of %s\n", snackList[buy].name);
  } else if (amount - snackList[buy].cost < 0) {
    printf("You can't afford it!\n");
  } else {
    printf("You bought %s\n", snackList[buy].name);
    amount -= snackList[buy].cost;
    printf("You have $%.2f left\n", amount);
  }

  return 0;
}
