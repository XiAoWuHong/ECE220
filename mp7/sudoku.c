#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

/* INTRO PARAGRAPH
For this mp I implemented six functions. Five of the functions were declared for me and I declared one
helper function myself to make the code simpler. The first function I implemented was is_val_in_row which
checks if the values that we are trying to put into the sudoku puzzle in the the row of the cell we are
trying to solve for. The second function I implemented was is_val_in_col which checks whether the value
we are trying to put into the sudoku puzzle is in the column of the cell we are checking. The third function
that I implemented was is_val_in_3x3_zone which checks if the value we are trying to put into the sudoku 
puzzle in the 3x3 zone of the puzzle board that the cell we are checking is in. Those three functions are
basically checking whether the value we want to put into the cell is valid. If the each function returns 0
(which means that the value would work in that particular cell) then in the fourth function is_val_valid we 
would return 1 meaing that the value can be put into the cell we are looking at. The fifth function is a helper
function that I declared to assist with the solve_sudoku function called find_unassigned_location. The
find_unassigned_location function finds cells that do not have a value assigned to them yet. The final function 
that I had to implement was solve_sudoku, this function is a backtracking alogrithm that made to solve the sudoku 
puzzle. Goes onto itself until it produces a valid and full puzzle board where it will then end the program.
*/

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO

  //m is for each column in the row starting from column 0 going to column 8
  //goes through each column of the row from 0 to 8
  for(int m = 0; m < 9; m ++){

    //if a cell in the row i contains the value val then return 1
    if (sudoku[i][m] == val){ 

      return 1;
    }
  }
  //if the value is not found in the row return 0
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO

  //n is for each row in the columnns starting from row 0 to row 8
  //goes through every row from 0 t0 8 for the given columnn
  for (int n = 0; n < 9; n ++){

    //if any cell in the column contains the value val then return 1
    if (sudoku[n][j] == val){

      return 1;
    }
  }
  //if the value cal is not found in the column return 0
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO

/*
the 3x3 zones of the sudoku board 
0,0|0,1|0,2
------------
1,0|1,1|1,2
------------
2,0|2,1|2,2
*/


  int m = i/3;  //m represents which row the cell is in with regard to the 3x3 board
  int n = j/3;  //n represents which col the cell is in with regard to the 3x3 board

  //goes through the three rows in the 3x3 zone of the sudoku board
  for(int row = 0; row < 3; row++){ 

    //goes through the three columns in the 3x3 zone of the sudoku board
    for(int col = 0; col < 3; col++){

      //if the any cell in the 3x3 zone contains the value val return 1
      if(sudoku[row+(m*3)][col+(n*3)] == val){

        return 1;
      }
    }

  }
  //if the value val is not found then return 0
  return 0; 
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO

  //if the value val is in the row, column, or 3x3 zone then it is not valid and the function will return 0
  if (is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku) == 1){
    return 0;
  }
  //if the value val is valid return 1
  return 1;
  // END TODO
}

//Function: find_unassigned_location
//Return true if there is an unassigned cell.
int find_unassigned_location(int *i,int *j,const int sudoku[9][9]){

  //goes through every cell in the board
  for(int m = 0; m < 9; m++){
    for(int n = 0; n < 9; n++){

      //if the cell does not contain a number 1-9 then it is unassigned/empty 
      if(sudoku[m][n] == 0){

        //we send the location of the empty cell to the solve_sudoku function through pointers
        *i = m;
        *j = n;

        //since the cell is empty and found return 1
        return 1;
      }
    }
  }

//if there is not empty cell then return 0
return 0;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.


  int i, j; //these variables will be used to locate the cell we are solving for 

  //check if the board is full, if the board is full return 1
  if (find_unassigned_location(&i, &j, sudoku) == 0){
    return 1;
  }

  //find an empty cell to fill since the board is not full
  else {
    find_unassigned_location(&i, &j, sudoku);
  }

  //go through each possible value 
  for (int num = 1; num <= 9; num++){

    //is the value that we are looking at valid for the cell we are checking according to the sudoku rules
    //if the value is valid then put fill the cell at location i,j with the value num
    if (is_val_valid(num, i, j, sudoku) == 1){
      sudoku[i][j] = num;

      //continue solving the sudoku board with the value we just inputed
      //if the board is full and valid return 1
      if (solve_sudoku(sudoku)){
        return 1;
      }
      //if the value does not work then zero out the cell
      sudoku[i][j] = 0;
    }
  }
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
