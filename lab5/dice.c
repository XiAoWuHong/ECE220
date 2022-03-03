//Function for generating three d6 rolls
#include <stdio.h>
#include <stdlib.h>
#include "dice.h"

void roll_three(int* one, int* two, int* three)
{

*one = rand() % 6 + 1;
*two = rand() % 6 + 1;
*three = rand() % 6 + 1; 

printf ("%d %d %d ", *one, *two, *three);

}
