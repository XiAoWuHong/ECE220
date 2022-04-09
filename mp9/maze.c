#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* INTRO PARAGRAPH
In this MP we implemented a maze solver that takes a text file with maze and then gives a solution using a 
depth-first seach (DFS) algorithm. We first create the maze in our program by opening the text file 
containing the maze and copying the dimensions as well the maze itself using a combination of fscanf and fgetc. 
The createMaze function memory is allocated for the struct, the array of pointer, and the arrays containing 
each row of the maze. We then return the maze struct to use in our DFS algorithm and print function. Our print 
function consists of a two for loops that go through each possible cooridinate for the array then prints each 
cell individully. Thisfunction is called twice, once before the maze is solved and once after the maze is solved. 
The solveMazeDFS function is the depth-first search alogrithm that solves the maze. It goes through each possible
permutation of solutions starting from START until it reachs a valid solution at END. It's a recursive/backtrakcing
algorithm. That's MP9 completed.
*/


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    FILE *reader = fopen(fileName, "r");    //open file given in read mode
    maze_t * aMAZEing = malloc(sizeof(maze_t)); //allocate memory for the maze struct and give it a funny name

    fscanf(reader, "%d %d", &aMAZEing->width, &aMAZEing->height);   //get the two integers from the opened file and designate those as our height and width

    aMAZEing->cells = malloc(aMAZEing->height*sizeof(char *));  //allocate memory to create an array of pointers the size of height so we can store each row individually

    int god;    //var for the for loop with funny name
    //this loop allocates memory for each row of the maze that is pointed to by the array of pointers. Each row is stored seperately
    for (god = 0; god < aMAZEing->height; god++){
        aMAZEing->cells[god] = malloc(aMAZEing->width * sizeof(char));
    }
    fgetc(reader); //skips new line
    int filler, fillim; //funny loop var names
    //this loop fills the array with the contents of the maze file
    for (filler = 0; filler < aMAZEing->height; filler++){  //for each row
        for (fillim = 0; fillim < aMAZEing->width; fillim++){   //for each col
            char pp = fgetc(reader);    //gets next character to put into the array
            aMAZEing->cells[filler][fillim] = pp;   //puts next character into the array
            if(pp == START){    //if the next character in the maze file is the START of the maze then set the start col and row values equal to its coordinates
                aMAZEing->startColumn = fillim;
                aMAZEing->startRow = filler;
            }
            if(pp == END){  //if the next character in the maze file is the END of the maze then set the end col and row values equal to its coordinates
                aMAZEing->endColumn = fillim;
                aMAZEing->endRow = filler;
            }
        }
        fgetc(reader); //skips new line
    }

    fclose(reader); //closes the reader 
    return aMAZEing;    //returns the completed maze struct

    return NULL;    //lmao
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    int god;    //used for the loop 

    //for loop goes through each row of the array to free them independently since they are pointed to at different parts of the memory
    for (god = 0; god < maze->height; god++){
        free(maze->cells[god]); //frees a row of the array 
    }
    free(maze->cells);  //frees the array of pointers
    free(maze); //frees the rest of the struct
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int i, j = 0;   //vars for each for loop so that we can go through every row and col

    //these two for loops go through every cell of the maze
    for (i = 0; i < maze->width; i++){ 
        for ( j = 0; j < maze->height; j++)
        {
            printf("%c", maze->cells[i][j]);    //prints each cell
        }
        printf("\n");   //prints new line
        
    }
      
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    //check if the cell is within the bounds of the maze
    if (row < 0 || row >= maze->height || col < 0 || col >=maze->width){
        return 0;
    }
    //check if the cell is not a path, visited, or wall cell
    if(maze->cells[row][col] != EMPTY && maze->cells[row][col] != START && maze->cells[row][col] != END){
        return 0;
    }
    //once you reach the end restore the START cell and return 1
    if(maze->cells[row][col] == END){
        maze->cells[maze->startRow][maze->startColumn] = START;
        return 1;
    }

    //set the cell as a part of the path
    maze->cells[row][col] = PATH;

    //check each direction for a possible solution path
    if (solveMazeDFS(maze, col-1, row)){
        return 1;
    }
    if (solveMazeDFS(maze, col+1, row)){
        return 1;
    }
    if (solveMazeDFS(maze, col, row-1)){
        return 1;
    }
    if (solveMazeDFS(maze, col, row+1)){
        return 1;
    }


    //since none of the cells next to our current cell are valid moves then we mark the cell as visited and return 0
    maze->cells[row][col] = VISITED;
    return 0;
}
