#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO

  for(int m = 0; m < 9; m ++){ //m is for each column
    if (sudoku[i][m] == val){
      return 1;
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  
  for (int n = 0; n < 9; n ++){
    if (sudoku[n][j] == val){
      return 1;
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO

  int m = i/3;
  int n = j/3;

  for(int row = 0; row < 3; row++){
    for(int col = 0; col < 3; col++){
      if(sudoku[row+(m*3)][col+(n*3)] == val){
        return 1;
      }
    }

  }

  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if (is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku) == 1){
    return 0;
  }
  return 1;
  // END TODO
}

//Function: find_unassigned_location
//Return true if there is an unassigned cell.
int find_unassigned_location(int *i,int *j,const int sudoku[9][9]){
  for(int m = 0; m < 9; m++){
    for(int n = 0; n < 9; n++){
      if(sudoku[m][n] == 0){
        *i = m;
        *j = n;
        return 1;
      }
    }
  }
return 0;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.

  int i, j;
  if (find_unassigned_location(&i, &j, sudoku) == 0){
    return 1;
  }
  else {
    find_unassigned_location(&i, &j, sudoku);
  }

  for (int num = 1; num <= 9; num++){
    if (is_val_valid(num, i, j, sudoku) == 1){
      sudoku[i][j] = num;
      if (solve_sudoku(sudoku)){
        return 1;
      }
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
