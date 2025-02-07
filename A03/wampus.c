/*----------------------------------------------
 * wampus.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 6, 2025
 * Implements program that randomly places Wampus into NxM grid
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  printf("Number of rows: ");
  int rows;
  scanf("%d", &rows);
  printf("Number of columns: ");
  int cols;
  scanf("%d", &cols);

  //allocating memory first by rows
  char ** matrix = malloc(rows * sizeof(char *));
  for (int i = 0; i < rows; i++) {
    matrix[i] = malloc(cols * sizeof(char));  // make room for the columns of row i
  }

  //generate rand cell for W
  int randR = rand() % rows;
  int randC = rand() % cols;

  //generate remaining boxes accordingly
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      if(i == randR && j == randC) {
        matrix[randR][randC] = 'W';
      } else {
        int differenceR = abs(i - randR);
        int differenceC = abs(j - randC);
        matrix[i][j] = differenceR + differenceC + '0';
      }
    }
  }

  printf("\n");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%c ", matrix[i][j]);
    }
    printf("\n");
  }

  // free whole 2d array
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);

  return 0;
}
