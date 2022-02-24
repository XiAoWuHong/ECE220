#include <stdlib.h>
#include <stdio.h>


/*    INTRO PARAGRAPGH EXPLAINING THE ERRORS
The errors in the routine semiprime.c are threefold. There is one error in the is_prime function 
which was having the wrong return values for the function where line 29 should have a return value of 1 
not a return value of 0. The second error was in line 49 where instead of k=i%j, this caused our code to not print any values.
It had to be replaced with k = i/j since we have to find the number by which j is multplied by to get our integer i. 
We then check if that is prime.The third error was that we had repeating values (though they were correct). This was solved by using a break for the loop
after the print statement. This is because since we have already found that i is a semiprime then we can move to the 
next i value rather than finding that i is semiprime a second time. 
*/

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */


int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <= b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
                        break;
                    }
                }
            }
        }
    }
    printf("\n");
    return ret;
}