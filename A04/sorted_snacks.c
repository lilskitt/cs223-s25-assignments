/*----------------------------------------------
 * sorted_snacks.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 12, 2025
 * Implements program that allows users to add snacks to the snackbar and displays them in alphabetical order
 * Same as last week but using LINKED LIST
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//define what snacks are, what they hold
struct snack {
  char name[64];
  float cost;
  int quantity;
  struct snack * before;
};

/**
* Create a new snack struct and insert it at the beginning of the list
* @param inBefore head of list
* @return void
*/
void insert_first(struct snack ** inBefore) {
  struct snack * n = (struct snack *)malloc(sizeof(struct snack));
  if (n == NULL) {
    printf("ERROR: Out of space!\n");
    exit(1);
  }
  printf("Enter a name: ");
  scanf("%s", n->name);
  printf("Enter a cost: ");
  scanf("%f", &n->cost);
  printf("Enter a quantity: ");
  scanf("%d", &n->quantity); 

  n->before = *inBefore;
  *inBefore = n;
}

/**
* Helper function to swap two nodes
* @param a snack to be compared with b
* @param b snack to be compared with a
* @return void
*/
void swap(struct snack * a, struct snack * b) {
  char tempName[64];
  float tempCost;
  int tempQuantity;
    
  // save a's data
  strcpy(tempName, a->name);
  tempCost = a->cost;
  tempQuantity = a->quantity;
    
  // copy b's data to a
  strcpy(a->name, b->name);
  a->cost = b->cost;
  a->quantity = b->quantity;
    
  // copy saved data to b
  strcpy(b->name, tempName);
  b->cost = tempCost;
  b->quantity = tempQuantity;
}

/** 
* Helper function to compare two costs
* @param a snack to be compared with b
* @param b snack to be compared with a
* @return int difference between costs to know whether they should switch
*/
int compareCost(struct snack * a, struct snack * b){
  if (a->cost < b->cost) {
    return -1; // a is cheaper
  } else if (a->cost > b->cost) {
    return 1;  // b is cheaper
  }
  return 0;
}

/**
* Sorts the costs
* @param head of the list
* @return void
*/
void sortCost(struct snack * head) {
  struct snack *current = head;
  struct snack *prev, *min;

  while (current != NULL) {
    min = current;
    prev = current->before;
    while(prev != NULL) {
      //if prev is cheaper, make new min
      if(compareCost(min, prev) > 0) {
        min = prev;
      }
      prev = prev->before;
    }
    if(min != current) {
      swap(current, min);
    }
    current = current->before;
  }
}

/**
* Sorts the names
* @param head of list
* @return void
*/
void sortName(struct snack * head) {
  struct snack *current = head;
  struct snack *prev, *min;

  while (current != NULL) {
    min = current;
    prev = current->before;
    while(prev != NULL) {
      //if prev is less, make new min
      if(strcmp(min->name, prev->name) > 0) {
        min = prev;
      }
      prev = prev->before;
    }
    if(min != current) {
      swap(current, min);
    }
    current = current->before;
  }
}

/**
* Sorts the quanitities
* @param head of list
* @return void
*/
void sortQuantity(struct snack * head) {
  struct snack *current = head;
  struct snack *prev, *min;

  while (current != NULL) {
    min = current;
    prev = current->before;
    while(prev != NULL) {
      //if next quantity is less, make new min
      if(min->quantity > prev->quantity) {
        min = prev;
      }
      prev = prev->before;
    }
    if(min != current) {
      swap(current, min);
    }
    current = current->before;
  }
}

/**
* Print list
* @param head of the list
* @return void
*/
void print(struct snack * head) {
  struct snack *current = head;
  while (current != NULL) {
    printf("Snack: %s, Cost: %.2f, Quantity: %d\n", current->name, current->cost, current->quantity);
    current = current->before;
  }
}

/**
* Clear and free whole list
* @param head of the list
* @return void
*/
void clear(struct snack * head) {
  struct snack * current = head;
  struct snack * next = NULL;

  // traverse and free each node
  while (current != NULL) {
    next = current->before;
    free(current);
    current = next;
  }
}

int main() {
  printf("Enter a number of snacks: ");
  int inputNum;
  scanf("%d", &inputNum);

  //set first node of list to null
  struct snack * list = NULL;

  //only add the number of snacks as many times as user says
  int i = 0;
  while (i < inputNum) {
    insert_first(&list);
    i++;
  }
  printf("\nunsorted\n");
  print(list);

  printf("\nsorted by cost\n");
  sortCost(list);
  print(list);
  
  printf("\nsorted by name\n");
  sortName(list);
  print(list);

  printf("\nsorted by quantity\n");
  sortQuantity(list);
  print(list);
  
  clear(list);
  return 0;
}
