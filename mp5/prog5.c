/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number = 1;
static int solution1;
static int solution2;
static int solution3;
static int solution4;

/*
The set_seed function intializes the psuedo random number generator that is later used in the program. It takes a 
valid user input and makes it the seed of this random number generator. 

The start_game function sets the values for the solutions to the game. The psuedo random number generator is used to do this. 

The make_guess function takes a user guess (that is valid) and checks how many inputs are perfect matches and how many inputs are 
misplaced matches. This is done by pairing together two variables so that they do not repeat. 
*/


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
   
    int seed;               //seed :)
    char post[2];           //post
    int rv;                 //number of items in the string from sscanf

    rv = sscanf (seed_str, "%d%1s", &seed, post);
    if (rv == 1)        //if there is more than one value in rv then it will return 0. Anything being in post makes the value of rv greater than 1
    {
        srand(seed);
        return 1;
    }
    else
    {
        printf ("set_seed: invalid seed\n");     //error 
        return 0;
    }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
    //gives us our random numbers
    *one = rand() % 8 + 1;
    *two = rand() % 8 + 1;
    *three = rand() % 8 + 1;
    *four = rand() % 8 + 1; 

    //this makes sure that the values we randomly generated are available in both prog5.c and main.c
    solution1 = *one;      
    solution2 = *two;
    solution3 = *three;
    solution4 = *four;

}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

    int w, x, y, z;     //our input variables
    char post[2];       
    int rv;             //number of items in the string
    rv = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);  

    if (rv != 4 || ((w || x || y || z) <= 0 ))  //if there are any items in post then return 0 and the guess is invalid
    {
        printf ("make_guess: invalid guess\n");
        return 0;
    }
    else if ((rv = 4) && (w <= 8 && w > 0) && (x <= 8 && x > 0) && (y <= 8 && y > 0) && (z <= 8 && z > 0))  //if all guesses are valid and 
    {
        int perfect = 0;        //counts the number of perfect matches
        int misplaced = 0;      //counts the number of misplaced matches
        //these values serve to match a solution and input
        int a = 1;
        int b = 2;
        int c = 3;
        int d = 4;
        int solone;
        int soltwo;
        int solthree;
        int solfour;
        //variables used for pairing the guess and solution together in the case that they are a match (in any way)
        //a is for *one or w, b is for *two or x, and so on

        //this checks for perfect matches between the solutions and inputs w, x, y and z
        if (w == solution1) 
        {
        perfect = perfect + 1;
        solone = a;
        }
        if (x == solution2)
        {
        perfect = perfect + 1;
        soltwo = b;
        }
        if (y == solution3)
        {
        perfect = perfect + 1;
        solthree = c;
        }
        if (z == solution4)
        {
        perfect = perfect + 1;
        solfour = d;
        }

        if (solone != a)    //checks for misplaced matches if there is no perfect match for solution one
        {
           if (solution1 == x && (solone != b || a || c || d) && (soltwo != b) && (solthree != b) && (solfour != b)) //is solution 1 equal to x if not already matched
           {
                solone = b;
                misplaced = misplaced + 1;
           }
           if (solution1 == y && (solone != c || a ||b || d) && (soltwo != c) && (solthree != c) && (solfour != c)) //is solution 1 equal to y if not already matched
           {
                solone = c;
                misplaced = misplaced + 1;
           }
           if (solution1 == z && (solone != d || a || b || c) &&(soltwo != d) && (solthree != d) && (solfour != d)) //is solution 1 equal to z if not already matched
           {
               solone = d;
               misplaced = misplaced + 1;
           }
        }

        if (soltwo != b)    //checks for misplaced matches if there is no perfect match for solution two
        {
            if (solution2 == w && (solone != a) && (soltwo != a || b || c || d) && (solthree != a) && (solfour != a)) //is solution 2 equal to w if not already matched
            {
                soltwo = a;
                misplaced = misplaced + 1;
            }
            if (solution2 == y && (solone != c) && (soltwo != c || a || b || d) && (solthree != c) && (solfour != c)) //is solution 2 equal to y if not already matched
            {
                soltwo = c;
                misplaced = misplaced + 1;
            }
            if (solution2 == z && (solone != d) && (soltwo != d || a || b || c) && (solthree != d) && (solfour != d)) //is solution 2 equal to z if not already matched
            {
                soltwo = d;
                misplaced = misplaced + 1;
            }
        }
        if (solthree != c)  //checks for misplaced matches if there is no perfect match for solution three
        {
            if (solution3 == w && (solone != a) && (soltwo != a) && (solthree != a || b || c || d) && (solfour != a)) //is solution 3 equal to w if not already matched
            {
                solthree = a;
                misplaced = misplaced + 1;
            }
            if (solution3 == x && (solone != b) && (soltwo != b) && (solthree != b || a || c || d) && (solfour != b)) //is solution 3 equal to x if not already matched
            {
                solthree = b;
                misplaced = misplaced + 1;
            }
            if (solution3 == z && (solone != d) && (soltwo != d) && (solthree != d || a || b || c)  && (solfour != d)) //is solution 3 equal to z if not already matched
            {
                solthree = d;
                misplaced = misplaced + 1;
            }
        }

        if (solfour != d)   //checks for misplaced matches if there is no perfect match for solution four
        {
            if (solution4 == w && (solone != a) && (soltwo != a) && (solthree != a) && (solfour != a || b || c || d)) //is solution 4 equal to w if not already matched
            {
                solfour = a;
                misplaced = misplaced + 1;
            }
            if (solution4 == x && (solone != b) && (soltwo != b) && (solthree != b) && (solfour != b || a || c || d)) //is solution 4 equal to x if not already matched
            {
                solfour = b;
                misplaced = misplaced + 1;
            }
            if (solution4 == y && (solone != c) && (soltwo != c) && (solthree != c) && (solfour != c || a || b || d)) //is solution 4 equal to y if not already matched
            {
                solfour = c;
                misplaced = misplaced + 1;
            }
        }

        printf ("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
        guess_number = guess_number + 1;
        //this updates the guesses in main.c 
        *one = w;
        *two = x;
        *three = y;
        *four = z;

        return 1;
    }
    else //if there is an invaild input the return 0
    {
        printf ("make_guess: invalid guess\n");
        return 0;
    }
}


