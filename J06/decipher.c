#include <stdio.h>
#include <stdlib.h>

int main() {
  //edit this program to read encrypted text from a file
  //the encrypted text uses a left shift to hide each character, go thru each character and shift to right to decode
  FILE* fp = fopen("message", "r");
  char c = fgetc(fp);
  while (c != EOF) {
    //shift to right!
    //need most significant bit to know how to shift
    int msb = (c & 0x80) >> 7;

    if (msb == 1) {
      printf("%c", c + 1);
    } else {
      printf("%c", c);
    }
    c = fgetc(fp);
  }
  fclose(fp);
  return 0;
}
