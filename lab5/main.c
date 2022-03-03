/* Code to simulate rolling three six-sided dice (D6)
 * User first types in seed value
 * Use seed value as argument to srand()
 * Call roll_three to generate three integers, 1-6
 * Print result "%d %d %d "
 * If triple, print "Triple!\n"
 * If it is not a triple but it is a dobule, print "Double!\n"
 * Otherwise print "\n"
 */

#include <stdio.h>
#include <stdlib.h>
#include "dice.h"

int one, two, three;

int main()
{
    int seed;
    printf ("Enter Seed: \n");

    scanf("%d", &seed);

    srand(seed);

    roll_three(&one, &two, &three);

    if ((one == two) && (two == three))
    {
        printf("triple! \n");
    }
    else if (one == two || two == three || three == one)
    {
        printf("double! \n");
    }
    else 
    {
        printf ("\n");
    }
return 0;
}