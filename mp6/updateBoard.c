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
int living = 0;
int CheckRow;
int CheckCol;
int currentCell = row*boardColSize + col;
    for (CheckRow = row - 1; CheckRow <= row + 1; CheckRow++){
        if (CheckRow >= 0 && CheckRow < boardRowSize){
            for (CheckCol = col - 1; CheckCol <= col + 1; CheckCol++){
                if (CheckCol >= 0 && CheckCol < boardColSize){
                    int n = CheckRow*boardColSize + CheckCol;
                    if (n != currentCell){
                        if (board[n] == 1){
                            living++;
                        }
                    }
                }
            }
        }
    }
    return living;
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
int updated_row = 0;
int updated_col = 0;
int dummy_board[boardRowSize*boardColSize];
    for (updated_row = 0; updated_row < boardRowSize; updated_row++){
        for (updated_col = 0; updated_col < boardColSize; updated_col++){
            int n = updated_row*boardColSize + updated_col;
            int living_neighbors = countLiveNeighbor(board, boardRowSize, boardColSize, updated_row, updated_col);
            int status = board[n];
            if (status == 1){
                if (living_neighbors == 2 || living_neighbors == 3){
                    dummy_board[n] = 1;
                }
                else {
                    dummy_board[n] = 0;
                }
            }
            else if (status == 0){
                if (living_neighbors == 3){
                    dummy_board[n] = 1;
                }
                else{
                    dummy_board[n] = 0;
                }
            }
        }
    }
    int copy;
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
for (int row = 0; row < boardRowSize; row++){
        for (int col = 0; col < boardColSize; col++){
                int n = row*boardColSize + col;
                int alive_neighbors = countLiveNeighbor(board, boardRowSize, boardColSize, row, col);
                int status = board[n];
                if (status == 1 && alive_neighbors != 2 && alive_neighbors != 3){
                    return 0;
                }
                if (status == 0 && alive_neighbors == 3){
                    return 0;
                }
            }
        }
return 1;
}