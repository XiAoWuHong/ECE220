#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STOP 0

int main()
{
  int row;                                   //represents n in the pascal's triangle equation
  printf("Enter a row index: ");
  scanf("%d", &row);

  // Write your code here
  /*
      This code calculates a row of pascals triangle after the user inputs a row index. The loop carries out all operations. 
  */


  int i;                                     //represents i in the pascal's triangle equation given to us
  long unsigned int result;                  //made to store the result of the pascal's triangle equation

  //this loop gets us the correct amounnt of resultants for pascals triangle
for (i = 0; i <= row; i++)
{
  if (i==0){                                  //this if statement prevents a divide by zero error
    result = 1;                               //the beginning of every pascal's triangle row is 1
  }
  else{                                       //this statement does the calculation for the coefficients in pascal's triangle
    result = (result * (row + 1 - i))/i;      //the pascal's triangle equation
  }
printf("%lu ", result);                       //prints out pascal's triangle
}
printf("\n");
  return 0;
}
