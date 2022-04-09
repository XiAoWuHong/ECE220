#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    FILE *reader = fopen(fileName, "r");
    // assert(reader != NULL);
    int width, height;

    fscanf(reader, "%d", &width);
    fscanf(reader, "%d", &height);

    maze_t * aMAZEing = malloc(sizeof(maze_t));
    aMAZEing->cells = (char**)malloc(height*sizeof(char *));
     
    int fillthatboy;
    for(fillthatboy = 0; fillthatboy < height; fillthatboy++){
        aMAZEing->cells[fillthatboy] = (char*)malloc(width*sizeof(char));
        int lmao;
        for(lmao = 0; lmao < width; lmao++){
            getc(reader, (*(*(aMAZEing->cells + fillthatboy) + lmao)));
        }
    }



    return aMAZEing;

    return NULL;
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
    free(maze->cells);
    free(maze);
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
    // Your code here.
    int i, j = 0;

    for (i = 0; i < maze->width; i++){
        for ( j = 0; j < maze->height; j++)
        {
            printf("%c", (*(*(maze->cells + i) + j)));
        }
        
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
    int bound_row = maze->width - 1;
    int bound_col = maze->height - 1;

    if ((col > bound_col) || (row > bound_row)){
        return 0;
    }
    if (maze->cells[col][row] != ' '){
        return 0;
    }
    if (maze->cells[col][row] == 'E'){
        return 1;
    }
    maze->cells[col][row] = '*';
    if (solveMazeDFS(maze, col-1, row) == 1){
        return 1;
    }
    if (solveMazeDFS(maze, col+1, row) == 1){
        return 1;
    }
    if (solveMazeDFS(maze, col, row-1) == 1){
        return 1;
    }
    if (solveMazeDFS(maze, col, row+1) == 1){
        return 1;
    }
    maze->cells[col][row] = ' ';
    return 0;
}
