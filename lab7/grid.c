#include <stdio.h>
#include "grid.h"
#include "grid_provided.h"


// Procedure: parse_grid: 
/* Pseudocode algorithm: 
	open the file for reading
	make sure the file is valid
	for each row and column
		scan the file to read the next int into grid at (row, column)
	close the file
*/
//
void parse_grid(const char fpath[], int grid[5][5]) {
FILE *grid_file;
grid_file = fopen("grid2.txt", "r");
if (grid_file == NULL){
	printf("not good");
}
for(int i = 1; i <= 5; i ++){
	for(int j = 1; j <= 5; j ++){
		grid[i][j] = fgetc(grid_file);
	}
}
fclose(grid_file);
}

// Procedure: solve_grid
// Solve the given grid instance. See wiki for algorithm.


int solve_grid(int grid[5][5]) {

	int i; 
	int j;

	if (FindUnassignedLocation(grid, &i, &j) == 0){
		return 1;
	}

//find a cell in the matrix that does not have a value in it
	FindUnassignedLocation(grid, &i, &j);

//run through each possible value
	for(int val = 0; val <= 5; val ++){
		if (is_val_valid(val, i, j, grid) == 1){
			grid[i][j] = val;

		}
	}
	return 0;
}


int is_val_valid(const int val, const int i, const int j, int grid[5][5]){
	//cell is at (i, j) i is the row and j is the column
	//n is a standin for the row and m is a standin for the column

	for(int m = 1; m <= j;  m++){
		if(val == grid[i][m]){
			return 0;
		}
	}
	for(int n = 1; n <= i; n++){
		if(val == grid[n][j]){
			return 0;
		}
	}
	return 1;
}


int FindUnassignedLocation(int grid[5][5], int*i, int*j){

	int n = *i; //standin for i
	int m = *j; //standing for j

	for(n = 1; n <= 5; n++){
		for(m = 1; m <= 5; m++){
			if(grid[n][m] == 0){
				*i = n;
				*j = m;
				return 1;
			}
		}
	}
	return 0; 
}