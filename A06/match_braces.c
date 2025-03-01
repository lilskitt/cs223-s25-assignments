/*----------------------------------------------
 * match_braces.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 28 2025
 * Use a stack to check matching braces
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure to hold line and column of a brace
typedef struct {
  int line;
  int column;
} BraceLocation;

//structure for managing the stack
typedef struct StackNode {
  BraceLocation brace;
  struct StackNode *next;
} StackNode;

/**
 * Pushes a new brace location onto the stack
 * @param top pointer to the top of the stack
 * @param brace location of brace to push
 * @return new top of the stack
 */
StackNode* push(StackNode *top, BraceLocation brace) {
  StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));
  if (newNode == NULL) {
    printf("Unable to allocate memory for new stack node");
    exit(1);
  }
  newNode->brace = brace;
  newNode->next = top;
  return newNode;
}

/**
 * Pops the top brace location from the stack
 * @param top pointer to the top of the stack
 * @param brace pointer to the brace location to store the popped value
 * @return new top of the stack
 */
StackNode* pop(StackNode *top, BraceLocation *brace) {
  if (top == NULL) {
    return NULL;
  }
  *brace = top->brace;
  StackNode *newTop = top->next;
  free(top);
  return newTop;
}

/**
 * Clears the stack by freeing all the nodes
 * @param top A pointer to the top of the stack
 * @return void
 */
void clearIt(StackNode *top) {
  while (top != NULL) {
    StackNode *temp = top;
    top = top->next;
    free(temp);
  }
}

/**
 * Displays usage information if the user inputs an incorrect number of command line arguments
 * @return void
 */
void usage(const char *filename) {
  if (filename != NULL) {
    printf("usage: ./match_braces %s\n", filename);
  } else {
    printf("usage: ./match_braces\n");
  }
}

/**
 * Checks whether the braces in the given file are properly matched
 * @param filename name of the file to check
 * @return void
 */
void matchBraces(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Cannot open file: %s\n", filename);
    exit(1);
  }

  StackNode *stack = NULL; //stores opening braces
  int line = 1, column = 1; //current line and column number
  char ch;

  while ((ch = fgetc(file)) != EOF) { //fgetc reads one char at a time, EOF is end of file
    if (ch == '{') {
      BraceLocation braceLoc = {line, column};
      stack = push(stack, braceLoc); //push the opening brace onto the stack
    } else if (ch == '}') {
      if (stack == NULL) {
        printf("Unmatched brace on Line %d and Column %d\n", line, column);
        fclose(file);
        return;
      }
      BraceLocation openingBrace;
      stack = pop(stack, &openingBrace); //pop the top brace from the stack
      printf("Found matching braces: (%d, %d) -> (%d, %d)\n",
          openingBrace.line, openingBrace.column, line, column);
    }

    if (ch == '\n') {
      line++;
      column = 1;
    } else {
      column++;
    }
  }

  while (stack != NULL) {
    BraceLocation openingBrace;
    stack = pop(stack, &openingBrace); //pop and report any unmatched
    printf("Unmatched brace on Line %d and Column %d\n", openingBrace.line, openingBrace.column);
  }

  fclose(file); 
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    usage(NULL);
    return 1;
  }
  matchBraces(argv[1]);
  return 0;
}

