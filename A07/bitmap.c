/*----------------------------------------------
 * bitmap.c
 * Author: Lola Peyrouse-Bremer
 * Date: March 7 2025
 * Implements a program to read an unsigned integer and output it as an 8x8 1bpp sprite
 ---------------------------------------------*/
#include <stdio.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);

  // todo: your code here

  //loop thru all 8 rows
  for (int row = 0; row < 8; row++) {
    //and al 8 columns
    for (int col = 0; col < 8; col++) {
      //the position of the current bit
      int pos = 63 - (row * 8 + col);

      //check if the bit is 1 or 0
      if (img & (0x1ul << pos)) {
        printf("@");
      } else {
        printf(" ");
      }
    }
    // Print a new line after each row
    printf("\n");
  }

  return 0;
}
