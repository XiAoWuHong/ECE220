#include "game.h"

//group members: V Verma, Peter Gianettos


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->score = 0;
    mygame->cols = cols;
    mygame->rows = rows;

    for(int fillx = 0; fillx < rows; fillx++){
        for(int filly = 0; filly < cols; filly++){
            mygame->cells[fillx*cols + filly] = -1;
        }
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct

    (*_cur_game_ptr)->cols = new_cols;
    (*_cur_game_ptr)->rows = new_rows;
    (*_cur_game_ptr)->score = 0;

    for(int fillx = 0; fillx < new_rows; fillx++){
        for(int filly = 0; filly < new_cols; filly++){
            (*_cur_game_ptr)->cells[fillx*new_cols+filly] = -1;
        }
    }

	return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if ((row < 0) || (col < 0)){
        if((row >= cur_game->rows) || (col >= cur_game->cols)){
        return NULL;
        }

    }
    int thicccness = cur_game->cols; //made this cuz it funny
    
return &(cur_game->cells[thicccness*row+col]);
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    
    int rows = cur_game->rows;
    int cols = cur_game->cols;
 
//sliding code
    int didmove = 0;    //flag for movement
    //goes through every cells
    for (int ncol = 0; ncol < cols; ncol++){
        for (int mrows = 0; mrows < rows; mrows++){
            //is the cell not empty?
            if (cur_game->cells[mrows*cols+ncol] != -1){
                //finding a target row
                if(mrows != 0){
                    for (int i_target = 0; i_target < mrows; i_target ++){
                        //if the cell in the correct column and target row is empty move it to said target cell
                        if(cur_game->cells[i_target*cols+ncol] == -1){
                            cur_game->cells[i_target*cols+ncol] = cur_game->cells[mrows*cols+ncol];
                            cur_game->cells[mrows*cols+ncol] = -1;
                            didmove = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

//merging code
    int didmerge = 0;   //flag for merging
    for(int currcol = 0; currcol < cols; currcol++){
        for(int currrow = 0; currrow < rows; currrow++){
            if (cur_game->cells[currrow*cols+currcol] != -1){
                for(int targ_merge = currrow + 1; targ_merge < rows; targ_merge++){
                    if(cur_game->cells[targ_merge*cols+currcol] != -1){
                        if(cur_game->cells[targ_merge*cols+currcol] != cur_game->cells[currrow*cols+currcol]){
                            break;
                        }
                        cur_game->cells[currrow*cols+currcol] = cur_game->cells[currrow*cols+currcol] * 2;
                        cur_game->cells[targ_merge*cols+currcol] = -1;
                        cur_game->score = cur_game->score + cur_game->cells[currrow*cols+currcol];
                        break;
                    }
                }
            }
        }
    }

    for (int ncol = 0; ncol < cols; ncol++){
        for (int mrows = 0; mrows < rows; mrows++){
            //is the cell not empty?
            if (cur_game->cells[mrows*cols+ncol] != -1){
                //finding a target row
                if(mrows != 0){
                    for (int i_target = 0; i_target < mrows; i_target ++){
                        //if the cell in the correct column and target row is empty move it to said target cell
                        if(cur_game->cells[i_target*cols+ncol] == -1){
                            cur_game->cells[i_target*cols+ncol] = cur_game->cells[mrows*cols+ncol];
                            cur_game->cells[mrows*cols+ncol] = -1;
                            break;
                        }
                    }
                }
            }
        }
    }

    if ((didmove || didmerge) == 1){
        return 1;
    }
        return 0;

};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int didmove = 0;

    //sliding code
    for(int ncol = 0; ncol < cols; ncol++){
        for (int mrow = rows -1; mrow >= 0; mrow--){
            if (cur_game->cells[mrow*cols+ncol] != -1){
                if(mrow != rows - 1){
                    for (int i_target = mrow; i_target >= 0; mrow--){
                            if(cur_game->cells[i_target*cols+ncol] == -1){
                                cur_game->cells[i_target*cols+ncol] = cur_game->cells[mrow*cols+ncol];
                                cur_game->cells[mrow*cols+ncol] = -1;
                                didmove = 1;
                                break;
                        }
                    }
                }
            }
            
        }
    }

    //merging code
    int didmerge = 0;   //flag for merging
    for(int currcol = 0; currcol < cols; currcol++){
        for(int currrow = rows - 1; currrow >= 0; currrow--){
            if (cur_game->cells[currrow*cols+currcol] != -1){
                for(int targ_merge = currrow - 1; targ_merge >= 0; targ_merge--){
                    if(cur_game->cells[targ_merge*cols+currcol] != -1){
                        if(cur_game->cells[targ_merge*cols+currcol] != cur_game->cells[currrow*cols+currcol]){
                            break;
                        }
                        cur_game->cells[currrow*cols+currcol] = cur_game->cells[currrow*cols+currcol] * 2;
                        cur_game->cells[targ_merge*cols+currcol] = -1;
                        cur_game->score = cur_game->score + cur_game->cells[currrow*cols+currcol];
                        break;
                    }
                }
            }
        }
    }

    for(int ncol = 0; ncol < cols; ncol++){
        for (int mrow = rows -1; mrow >= 0; mrow--){
            if (cur_game->cells[mrow*cols+ncol] != -1){
                if(mrow != rows - 1){
                    for (int i_target = mrow; i_target >= 0; mrow--){
                            if(cur_game->cells[i_target*cols+ncol] == -1){
                                cur_game->cells[i_target*cols+ncol] = cur_game->cells[mrow*cols+ncol];
                                cur_game->cells[mrow*cols+ncol] = -1;
                                break;
                        }
                    }
                }
            }
            
        }
    }

    if ((didmove || didmerge) == 1){
        return 1;
    }
        return 0;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int didmove = 0;
    //goes through every cell
    for(int mrow = 0; mrow < rows; mrow++){
        for (int ncol = 0; ncol < cols; ncol++){
            //if the cell empty?
            if (cur_game->cells[mrow*cols+ncol] != -1){
                //finding a target col as long it isn't in col0
                if (ncol != 0){
                    for (int j_target = 0; j_target < ncol; j_target++){
                        if (cur_game->cells[mrow*cols+j_target] == -1){
                            cur_game->cells[mrow*cols+j_target] = cur_game->cells[mrow*cols+ncol];
                            cur_game->cells[mrow*cols+ncol] = -1;
                            didmove = 1;
                        }
                    }
                }
            }
        }
    }

    int didmerge = 0;
    for (int currrow = 0; currrow < rows; currrow++){
        for (int currcol = 0; currcol < cols; currcol++){
            if(cur_game->cells[currrow*cols+currcol] != -1){
                for(int targ_merge = currcol + 1; targ_merge < cols; targ_merge++){
                    if(cur_game->cells[currrow*cols+targ_merge] != -1){
                        if(cur_game->cells[currrow*cols+targ_merge] != cur_game->cells[currrow*cols+currcol]){
                            break;
                        }
                        cur_game->cells[currrow*cols+currcol] = cur_game->cells[currrow*cols+currcol] * 2;
                        cur_game->cells[currrow*cols+targ_merge] = -1;
                        cur_game->score = cur_game->score + cur_game->cells[currrow*cols+currcol];
                        didmerge = 1;
                        break;
                    }
                }
            }
        }
    }

    for(int mrow = 0; mrow < rows; mrow++){
        for (int ncol = 0; ncol < cols; ncol++){
            //if the cell empty?
            if (cur_game->cells[mrow*cols+ncol] != -1){
                //finding a target col as long it isn't in col0
                if (ncol != 0){
                    for (int j_target = 0; j_target < ncol; j_target++){
                        if (cur_game->cells[mrow*cols+j_target] == -1){
                            cur_game->cells[mrow*cols+j_target] = cur_game->cells[mrow*cols+ncol];
                            cur_game->cells[mrow*cols+ncol] = -1;
                        }
                    }
                }
            }
        }
    }

    if ((didmove || didmerge) == 1){
        return 1;
    }
    return 0;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int didmove = 0;
    for(int mrow = 0; mrow < rows; mrow++){
        for (int ncol = cols - 1; ncol >= 0; ncol--){
            if (cur_game->cells[mrow*cols+ncol] != -1){
                if(ncol != cols -1){
                    for (int j_target = cols -1; j_target >= 0; j_target--){
                        if (cur_game->cells[mrow*cols+j_target] == -1){
                            cur_game->cells[mrow*cols+j_target] = cur_game->cells[mrow*cols+ncol];
                            cur_game->cells[mrow*cols+ncol] = -1;
                            didmove = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    int didmerge = 0;
    for (int currrow = 0; currrow < rows; currrow++){
        for (int currcol = rows - 1; currcol >= 0; currcol--){
            if(cur_game->cells[currrow*cols+currcol] != -1){
                for(int targ_merge = currcol - 1; targ_merge >= 0; targ_merge--){
                    if(cur_game->cells[currrow*cols+targ_merge] != -1){
                        if(cur_game->cells[currrow*cols+targ_merge] != cur_game->cells[currrow*cols+currcol]){
                            break;
                        }
                        cur_game->cells[currrow*cols+currcol] = cur_game->cells[currrow*cols+currcol] * 2;
                        cur_game->cells[currrow*cols+targ_merge] = -1;
                        cur_game->score = cur_game->score + cur_game->cells[currrow*cols+currcol];
                        didmerge = 1;
                        break;
                    }
                }
            }
        }
    }

    for(int mrow = 0; mrow < rows; mrow++){
        for (int ncol = cols - 1; ncol >= 0; ncol--){
            if (cur_game->cells[mrow*cols+ncol] != -1){
                if(ncol != cols -1){
                    for (int j_target = cols -1; j_target >= 0; j_target--){
                        if (cur_game->cells[mrow*cols+j_target] == -1){
                            cur_game->cells[mrow*cols+j_target] = cur_game->cells[mrow*cols+ncol];
                            cur_game->cells[mrow*cols+ncol] = -1;
                            break;
                        }
                    }
                }
            }
        }
    }


    if ((didmove || didmerge) == 1){
        return 1;
    }
    else{
        return 0;
    }
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    int rows = cur_game->rows;
    int cols = cur_game->cols;

    for(int therow = 0; therow < rows; therow++){
        for(int thecol = 0; thecol < cols; thecol++){
            if (cur_game->cells[therow*cols+thecol] == -1){
                return 1;
            }
            if (cur_game->cells[(therow+1)*cols+thecol] == cur_game->cells[therow*cols+thecol]){
                return 1;
            }
            if (cur_game->cells[therow*cols+thecol] == cur_game->cells[therow*cols+(thecol+1)]){
                return 1;
            }
        }
    }

    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
