/*----------------------------------------------
 * magic_square.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 12, 2025
 * Implements a program that tests whether a given matrix is a magic square
 * A magic square is an N by N matrix where each row, column, and diagonal has the same sum, called the magic constant
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

int magicConstant; //global

/**
* Determine whether a matrix is a magic square
* @param matrix magic square from file input
* @param a number of rows and cols
* @return int indicate success or failure of magic square
*/
int isMagic(int ** matrix, int a) {
  //because it's a square, just use a (rows)
  int sum = 0;

  //sum of the first row, grab what the sum should be
  for (int j = 0; j < a; j++) {
    sum += matrix[0][j];
  }

  //sum of all rows, checking against sum
  for (int i = 1; i < a; i++) {
    int rowSum = 0;
    for (int j = 0; j < a; j++) {
      rowSum += matrix[i][j];
    }
    if (rowSum != sum) {
      return 0; //fail
    }
  }

  //sum of all columns, checking against sum
  for (int j = 0; j < a; j++) {
    int colSum = 0;
    for (int i = 0; i < a; i++) {
      colSum += matrix[i][j];
    }
    if (colSum != sum) {
      return 0;  //fail
    }
  }

  //sum of diagonals, checking against sum
  int diag1Sum = 0, diag2Sum = 0;
  for (int i = 0; i < a; i++) {
    diag1Sum += matrix[i][i];
    diag2Sum += matrix[i][a - 1 - i]; //should get index on a diagonal
  }

  //comparing all sums to what sum should be
  if (diag1Sum != sum || diag2Sum != sum) {
    return 0; //fail
  }

  magicConstant = sum;
  return 1;  //success
}

int main() {
  //managing the file
  FILE * file = fopen("magic4.txt", "r");
  if (!file) {
    printf("Cannot open file\n");
    exit(1);
  }

  //grabbing info to make matrix
  int rows, cols; //getting cols because it won't read correctly?
  fscanf(file, "%d %d", &rows, &rows);
  int ** magic_sq = malloc(rows * sizeof(int *));
  if (magic_sq == NULL) {
    printf("memory allocation fail\n");
    return 1;
  }

  //dynamic memory allocation for rows and columns
  for (int i = 0; i < rows; i++) {
    magic_sq[i] = malloc(rows * sizeof(int));
    if (magic_sq[i] == NULL) {
      printf("Memory allocation failed for row %d!\n", i);
      return 1;
    }
  }

  // finally can read the values from the file into the matrix
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      fscanf(file, "%d", &magic_sq[i][j]);
    }
  }

  //done using the file, closed
  fclose(file);

  //print the input
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      printf("%d ", magic_sq[i][j]);
    }
    printf("\n");
  }

  //print if magic cube or not
  if(isMagic(magic_sq, rows) == 1) {
    printf("M is a magic square (magic constant = %d)\n", magicConstant);
  } else {
    printf("M is NOT a magic square!\n");
  }

  //freeing rows and cols
  for (int i = 0; i < rows; i++) {
    free(magic_sq[i]);
  }
  free(magic_sq);
  return 0;
}
