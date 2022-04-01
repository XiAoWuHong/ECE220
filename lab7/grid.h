#ifndef GRID_H_
#define GRID_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>


// Function: solve_grid
int solve_grid(int grid[5][5]);

// Procedure: parse_grid
void parse_grid(const char fpath[], int grid[5][5]);

//Procedure: is_val_valid
int is_val_valid(const int val, const int i, const int j, int grid[5][5]);

// Procedure: FindUnassignedLocation
int FindUnassignedLocation(int grid[5][5], int*i, int*j);

#endif
