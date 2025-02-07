#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   printf("Enter digits: ");
   char chars[32];
   scanf("%s", chars);

   int digits[32];
   //this loop takes all digits only from input
   int y = 0;
   for(int i = 0; i < strlen(chars); i++) {
     if(chars[i] < 58 && chars[i] > 47) {
      int num = chars[i] - '0';
      digits[y] = num;
      y++;
     }
   }

   //this loop counts the number of each number's occurance
   int count[10];
   for(int i = 0; i < 32; i++) {
      //if seen before increment its count, new count
      if(digits[i] == 0) {count[0]++;}
      if(digits[i] == 1) {count[1]++};
      if(digits[i] == 2) {count[2]++};
      if(digits[i] == 3) {count[3]++};
      if(digits[i] == 4) {count[4]++};
      if(digits[i] == 5) {count[5]++};
      if(digits[i] == 6) {count[6]++};
      if(digits[i] == 7) {count[7]++};
      if(digits[i] == 8) {count[8]++};
      if(digits[i] == 9) {count[9]++};
   }

   //print using the counts
   
   return 0;
}
