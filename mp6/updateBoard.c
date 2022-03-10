
/*
INTRODUCTORY PARAGRAPH

For this MP I implemented three functions: countLiveNeighbor, updateBoard, and alive stable, for a program that simulates
Conway's Game of Life. The countLiveNeighbor function runs through the entire board and checks how many living neighbors each 
cell has and returns that value into the updateBoard function. The updateBoard function updates the entire board to the next
generation based on the rules of Conway's Game of Life. This is done by running through the entire board and getting the 
number of living neighbors from the countLiveNeighbor function, using the status of the cell (alive or dead) and the 
number of living neighbors we can determine the cell will be alive or dead for the next generation. The aliveStable
function checks whether the board will be 'stable' (meaning that there is no change in the board for the next generation)
by running a simplified version of countLiveNeighbor and updateBoard within itself to check for any changes in the next 
generation. If there are no changes in the board for the next generation then aliveStable will return 1 and end the game,
if it is not stable then the function will return 0 and continues playing the game. 
*/


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
int living = 0; //the count for the number of living neighbors the cell we are checking has
int CheckRow;   //the row of the neighboring cells we are checking
int CheckCol;   //the column of the neighboring cells we are checking
int currentCell = row*boardColSize + col;   //the loctaion of the cell who's neighbors we are checking in the array

    //check the row above, below, as well as the row that contains the currentCell
    for (CheckRow = row - 1; CheckRow <= row + 1; CheckRow++){   

        //is the row we are checking within the bounds of the array?
        if (CheckRow >= 0 && CheckRow < boardRowSize){      

            //check the column left, right, and the column that contains the currentCell
            for (CheckCol = col - 1; CheckCol <= col + 1; CheckCol++){  

                //is the column we are checking within the bounds of the array?
                if (CheckCol >= 0 && CheckCol < boardColSize){
                    int n = CheckRow*boardColSize + CheckCol;   //n is the location of the item we are trying to access in the array

                    //are we checking the cell who's neighbor's we are counting? if so ignore its status
                    if (n != currentCell){               

                        //is the status of the neighboring cell dead or alive? If it's alive increment the living counter. 
                        if (board[n] == 1){
                            living++;
                        }
                    }
                }
            }
        }
    }
    return living;  //return the value counted for the amount of living neighboring cells
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
int updated_row = 0;    //the row in which we are updating the cell
int updated_col = 0;    //the column in which we are updating the cell
int dummy_board[boardRowSize*boardColSize]; //a shallow copy of the board so we are not actively changing the board and messing with our living_neighbor value

    //this loop increments through every row in the board array
    for (updated_row = 0; updated_row < boardRowSize; updated_row++){

        //this loop increments through every column for every row in the board array
        for (updated_col = 0; updated_col < boardColSize; updated_col++){
            int n = updated_row*boardColSize + updated_col; //n is equal to the location of the cell we are updating in the board array
            int living_neighbors = countLiveNeighbor(board, boardRowSize, boardColSize, updated_row, updated_col);  //the amount of living neighbors based on the return value of the countLieNeighbor function
            int status = board[n];  //the status (dead or alive) of the cell we are updating

            //if the cell is living check the below scenarios to determine whether it lives or dies in the next generation
            if (status == 1){

                //if the cell has two or three living neighbors it will survive to the next generation. Otherwise is will die.
                if (living_neighbors == 2 || living_neighbors == 3){
                    dummy_board[n] = 1;
                }
                else {
                    dummy_board[n] = 0;
                }
            }

            //if the cell is dead check the below scenarios to determine whether it lives or dies in the next generation
            else if (status == 0){

                //if the cell has exactly three living neighbors it will become alive for the next generation. Otherwise it will stay dead
                if (living_neighbors == 3){
                    dummy_board[n] = 1;
                }
                else{
                    dummy_board[n] = 0;
                }
            }
        }
    }
    int copy;   //counter or the next loop

    //copy the updated dummy board (that holds the next generation) into the main board to print to screen
    for (copy = 0; copy <= boardColSize*boardRowSize; copy++){
        board[copy] = dummy_board[copy];
    }
}
/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
//this loop increments through every row in the array
for (int row = 0; row < boardRowSize; row++){
    //this loop increments through every column for every row in the array
    for (int col = 0; col < boardColSize; col++){
            int n = row*boardColSize + col; //n equals the cell we are checking
            int alive_neighbors = countLiveNeighbor(board, boardRowSize, boardColSize, row, col);   //the amount of live neighbors that the cell we are checking has
            int status = board[n];  //whether the board is 1 (alive) or 0 (dead)

            //if this statement is true that means that the board would change for the next generation and is therefore not stable. It will return 0. 
            if (status == 1 && alive_neighbors != 2 && alive_neighbors != 3){
                return 0;
            }
            //if this statement is true that means that the board would change for the next generation and is therefore not stable. It will return 0.
            if (status == 0 && alive_neighbors == 3){
                return 0;
            }
        }
    }
    //if none of the above if statements are true then the board has/will not undergo any changes for the next generation and is therefore stable.
return 1;
}