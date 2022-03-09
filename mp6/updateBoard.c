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
    int a;  //how many living cells are there around the cell we are checking
    int currRow = row;
    int checkRow;   //the row in the array we are checking
    int currCol = col;
    int checkCol;   //the column in the array we are checking
    for (checkRow = currRow - 1;checkRow <= currRow + 1; checkRow++){
        if (checkRow >= 0 && checkRow <= boardRowSize){
            for (checkCol = currCol - 1; checkCol <= currCol + 1; checkCol++){
                if (checkCol >= 0 && checkCol <= boardColSize){
                    if (checkCol != currCol && checkRow != currRow){
                        if (board[checkRow * boardRowSize + checkCol] == 1){
                            a++;
                        }
                    }
                }
            }
        }
    }
    return a;
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
    int row = 0;
    int col = 0;
    int cell;

    for (cell = 0; cell <= boardRowSize * boardColSize; cell++){
        if (col == boardColSize){
            row = row + 1;
            col = 0;
        }
        if (row == boardRowSize && col == boardColSize){
            break;
        }
        if (countLiveNeighbor(board, boardRowSize, boardColSize, row, col) == (2 || 3)){
            board[row * boardRowSize + col] = 1;
        }
        col++;
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
    int board_copy[boardRowSize * boardColSize];
    int b = 0;
    int counter;
    for (counter = 0; counter <= boardRowSize * boardColSize; counter++){
        if (board_copy[counter] == board[counter]){
            b++;
        }
        else{
            break;
        }
    }
    if (b == boardColSize * boardRowSize){
        return 1;
    }
    else{
        return 0;
    }
}

				
				
			

