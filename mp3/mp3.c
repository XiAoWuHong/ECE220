#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STOP 0

int main()
{
  int row;          //represents n in the pascal's triangle equation
  int i;            //represents i in the pascal's triangle equation given to us
  unsigned result;  //made to store the result of the pascal's triangle equation
  unsigned productloop;  
  unsigned numerator;
  unsigned denominator;

  printf("Enter a row index: ");
  scanf("%d", &row);

  // Write your code here
  
  //this loop gets us the correct amounnt of resultants for pascals triangle
for (i = 0; i <= row; i++)
{


//initializes the numerator and denominator so we don't explode during the math
  numerator = 1;
  denominator = 1;

//finds the numerator for the pascal's triangle equation given
  for (productloop = i; productloop > 0; productloop--) 
  {
    numerator = numerator * (row + 1 - productloop); //for every 
  }


//finds the denominator for the pascal's triangle equation given
  for (productloop = i; productloop > 0; productloop--)
  
  {
    denominator = denominator * productloop; 
  }

//calculates the result using the solved for numerator and denominator
  result = numerator/denominator;

  //prints out the result
   printf("%u ", result);
}
printf("\n");

  return 0;
}
