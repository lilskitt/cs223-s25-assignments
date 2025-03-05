//Authors: Lola & Bii

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char* input = argv[1];
  int decimalValue = 0;
    
  //check for 0x or 0b
  if (strncmp(input, "0x", 2) == 0) {
    //for hex input
    for (int i = 2; input[i] != '\0'; i++) {
      //shift left by 4 bits
      decimalValue = decimalValue << 4;
      if (input[i] >= '0' && input[i] <= '9') {
        //for 0-9
        decimalValue |= (input[i] - '0');
      } else if (input[i] >= 'A' && input[i] <= 'F') {
        //for A-f
        decimalValue |= (input[i] - 'A' + 10);
      }
    }
  } else if (strncmp(input, "0b", 2) == 0) {
    //for binary input
    for (int i = 2; input[i] != '\0'; i++) {
      decimalValue = decimalValue << 1;
      if (input[i] == '1') {
        decimalValue = decimalValue | 1;
      }
    }
  } else {
    return 1;
  }

  printf("%d\n", decimalValue);
  return 0;
}
