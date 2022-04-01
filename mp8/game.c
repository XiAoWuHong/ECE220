#include "game.h"

//group members: V Verma, Peter Gianettos


/* INTRO PARAGRAPH
For this MP we implemented 8 functions. Four of the functions are made for
movement and merging of the tiles on the game board and the other 4
are for keeping the game running or to start the game. The four functions 
that are not movement based are make_game, remake_game, get_cell, and 
legal_move_check. The funciton make_game was already half completed for us
so all we had to do was intialize the rest of the game struct to start the 
game. We initialized the score to 0, and the row/column variable to what the
user inputed in main. Remake_game is remarkably similar to the make_game
except in the fact that we destruct our current game and create a new struct
for the remade game. We set score back to 0 and input our new row/columns,
the board is then cleared and all the cells are set to empty (-1). The 
get_cell function returns a pointer to a cell on the game board, we had to
ensure that the cell we wanted to return was within the bounds of the game 
board. If the cell that we want is out of bound then we returned NULL. The
get_cell function is used often by the given rand_new_tile. For each 
movement function we implemented very similar algorithms for each with
slight differences for direction. The move_w function's slide functionality 
is achieved by running through the board in column major order and moving 
tiles into empty cells. Though the method we use for finding our tile/cell is 
still in row-major order the way we find these cells is like column-major
order searching. The merging is done in a similar way where like tiles are
found and merged together. The same goes for move_s though in reverse with 
the same conceptual functinality behind it. For the move_a function we searched
for empty cells using row-major order like searching and merging. The move_s 
function is pretty much alike except it goes in reverse compared to move_a 
starting and moving from the opposite direction. The final function is 
legal_move_check which checks if there are any possible moves left on the
board, if there aren't it triggers the game over otherwise the game continues. 
We achieve this by running through every cell and checking if it either has a 
like tile in it's row/column or if there are empty cells. 
*/

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

    //score starts at 0
    mygame->score = 0;

    //cols and rows are given by user input 
    mygame->cols = cols;
    mygame->rows = rows;

    //make sure every cell on the game board is empty (=-1)
    for(int fillx = 0; fillx < rows; fillx++){
        for(int filly = 0; filly < cols; filly++){
            mygame->cells[fillx*cols + filly] = -1;
        }
    }
    //return the completed struct
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

    //set new values for the cur_game struct and replace the old one
    (*_cur_game_ptr)->cols = new_cols;
    (*_cur_game_ptr)->rows = new_rows;

    //score is reset to 0
    (*_cur_game_ptr)->score = 0;


    //empty the entire game_board with the new game bounds (all cells = -1)
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

    //if the given row/col are out of the game bounds then return NULL
    if ((row < 0) || (col < 0)){
        if((row >= cur_game->rows) || (col >= cur_game->cols)){
        return NULL;
        }

    }
    int thicccness = cur_game->cols; //made this cuz it funny
    //return the location of the cell in the struct
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

    //flag for movement, will equal 1 if movement occurs
    int didmove = 0;

    //goes through every cell in column-major order
    for (int ncol = 0; ncol < cols; ncol++){
        for (int mrows = 0; mrows < rows; mrows++){

            //is the cell not empty?
            if (cur_game->cells[mrows*cols+ncol] != -1){

                //finding a target row but not if mrows is 0 since it's not able to slide
                if(mrows != 0){
                    for (int i_target = 0; i_target < mrows; i_target ++){

                        //if the cell in the correct column and target row is empty move it to said target cell
                        if(cur_game->cells[i_target*cols+ncol] == -1){
                            cur_game->cells[i_target*cols+ncol] = cur_game->cells[mrows*cols+ncol];
                            cur_game->cells[mrows*cols+ncol] = -1;

                            //set the didmove flag to 1
                            didmove = 1;

                            //break so it don't double slide
                            break;
                        }
                    }
                }
            }
        }
    }

//merging code

    //flag for merging, will equal 1 if merging occurs
    int didmerge = 0;

    //goes through every cell in column major order
    for(int currcol = 0; currcol < cols; currcol++){
        for(int currrow = 0; currrow < rows; currrow++){

            //if the cell is empty start checking for like tiles
            if (cur_game->cells[currrow*cols+currcol] != -1){

                //move through potential target cells to merge with starting from our current cell and moving through the rows
                for(int targ_merge = currrow + 1; targ_merge < rows; targ_merge++){

                    //if a tile is encountered
                    if(cur_game->cells[targ_merge*cols+currcol] != -1){

                        //if the tile doesn't match then no merging occurs for said cell
                        if(cur_game->cells[targ_merge*cols+currcol] != cur_game->cells[currrow*cols+currcol]){
                            break;
                        }
                        //merge those boys
                        cur_game->cells[currrow*cols+currcol] = cur_game->cells[currrow*cols+currcol] * 2;
                        cur_game->cells[targ_merge*cols+currcol] = -1;

                        //add to the score
                        cur_game->score = cur_game->score + cur_game->cells[currrow*cols+currcol];
                        didmerge = 1;
                        //move onto the next possible cells
                        break;
                    }
                }
            }
        }
    }

    //same as above sliding code minus the flag
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
    //if either flag was set then return 1 otherwise invalid move
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

    //flag for movement, will equal 1 if movement occurs
    int didmove = 0;

    //sliding code

    //goes through every cell is column-major order but starting from the bottom 
    for(int ncol = 0; ncol < cols; ncol++){
        for (int mrow = rows -1; mrow >= 0; mrow--){

            //if the cell is not empty
            if (cur_game->cells[mrow*cols+ncol] != -1){

                //if the cell isn't on a border 
                if(mrow != rows - 1){

                    //search for the first possible empty cell on the game board
                    for (int i_target = mrow; i_target >= 0; mrow--){

                            //if an empty cell is found move the tile to said cell
                            if(cur_game->cells[i_target*cols+ncol] == -1){
                                cur_game->cells[i_target*cols+ncol] = cur_game->cells[mrow*cols+ncol];
                                cur_game->cells[mrow*cols+ncol] = -1;

                                //set the flag to 1 since movement occured
                                didmove = 1;
                                break;
                        }
                    }
                }
            }
            
        }
    }

    //merging code

    ////flag for merging, will equal 1 if merging occurs
    int didmerge = 0;

    //goes through eveyr cell in column-major order but starting from the bottom 
    for(int currcol = 0; currcol < cols; currcol++){
        for(int currrow = rows - 1; currrow >= 0; currrow--){

            //if the cell is not empty
            if (cur_game->cells[currrow*cols+currcol] != -1){

                //find possible tiles for merge
                for(int targ_merge = currrow - 1; targ_merge >= 0; targ_merge--){

                    //if the cell is not empty
                    if(cur_game->cells[targ_merge*cols+currcol] != -1){

                        //if the closest possible cell does not match our current cell then merging is not possible
                        if(cur_game->cells[targ_merge*cols+currcol] != cur_game->cells[currrow*cols+currcol]){
                            break;
                        }
                        //if the closest possible cell does match then merge those boys/girls/cells
                        cur_game->cells[currrow*cols+currcol] = cur_game->cells[currrow*cols+currcol] * 2;
                        cur_game->cells[targ_merge*cols+currcol] = -1;

                        //update the score
                        cur_game->score = cur_game->score + cur_game->cells[currrow*cols+currcol];

                        //didmerge flag is set to 1 since merging occured
                        didmerge = 1;

                        //to the next cell to check for merge possiblities
                        break;
                    }
                }
            }
        }
    }
    //same as above sliding code without the flag 
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


    //if either flag is set then return 1
    if ((didmove || didmerge) == 1){
        return 1;
    }
    //if neither flag is set then it is an invalid move, return 0
        return 0;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE

    int rows = cur_game->rows;
    int cols = cur_game->cols;

//sliding code

    // flag for monement, will equal 1 if movement happens
    int didmove = 0;

    //goes through every cell in row-major order
    for(int mrow = 0; mrow < rows; mrow++){
        for (int ncol = 0; ncol < cols; ncol++){

            //if the cell empty?
            if (cur_game->cells[mrow*cols+ncol] != -1){

                //find a target col as long it isn't in col0
                if (ncol != 0){

                    //finding the first possible empty cell to move the tile into
                    for (int j_target = 0; j_target < ncol; j_target++){

                        //if an empty cell is found then slide that boy/girl/cell
                        if (cur_game->cells[mrow*cols+j_target] == -1){
                            cur_game->cells[mrow*cols+j_target] = cur_game->cells[mrow*cols+ncol];
                            cur_game->cells[mrow*cols+ncol] = -1;

                            //set off the movement flag
                            didmove = 1;
                            
                            //continue sliding other cells
                            break;
                        }
                    }
                }
            }
        }
    }

//merging code

    //flag for merging, will equal 1 when merging occurs
    int didmerge = 0;

    //goes through every cell in row-major order
    for (int currrow = 0; currrow < rows; currrow++){
        for (int currcol = 0; currcol < cols; currcol++){

            //if the cell isn't empty 
            if(cur_game->cells[currrow*cols+currcol] != -1){

                //find a possible target cell for merging
                for(int targ_merge = currcol + 1; targ_merge < cols; targ_merge++){

                    //if a tile is found
                    if(cur_game->cells[currrow*cols+targ_merge] != -1){

                        //if the tile does not match the tile we are trying to merge then break and move to another cell
                        if(cur_game->cells[currrow*cols+targ_merge] != cur_game->cells[currrow*cols+currcol]){
                            break;
                        }
                        //if the tiles match the merge the cells
                        cur_game->cells[currrow*cols+currcol] = cur_game->cells[currrow*cols+currcol] * 2;
                        cur_game->cells[currrow*cols+targ_merge] = -1;

                        //update the score
                        cur_game->score = cur_game->score + cur_game->cells[currrow*cols+currcol];

                        //set off the merge flag
                        didmerge = 1;

                        //move onto more merging, be free my code
                        break;
                    }
                }
            }
        }
    }

//same as above sliding code minus the flag
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

    //if either flag is set then there was a valid move so return 1
    if ((didmove || didmerge) == 1){
        return 1;
    }
    //if neither flag is set then invalid move and return 0
    return 0;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE

    int rows = cur_game->rows;
    int cols = cur_game->cols;

//sliding code

    //flag for movement, if movement occurs then it will equal 1
    int didmove = 0;

    //goes through every cell in row-major order but starting from the right edge 
    for(int mrow = 0; mrow < rows; mrow++){
        for (int ncol = cols - 1; ncol >= 0; ncol--){

            //if the cell is not empty and has lived a fulfilling life
            if (cur_game->cells[mrow*cols+ncol] != -1){

                //it's not a border cell
                if(ncol != cols -1){

                    //find a cell for it to slide into (what a smooth cell ;) )
                    for (int j_target = cols -1; j_target >= 0; j_target--){

                        //if an empty cell is found then slide it into there
                        if (cur_game->cells[mrow*cols+j_target] == -1){
                            cur_game->cells[mrow*cols+j_target] = cur_game->cells[mrow*cols+ncol];
                            cur_game->cells[mrow*cols+ncol] = -1;

                            //set off the movement flag since movement happened
                            didmove = 1;

                            //move onto better cells to slide into
                            break;
                        }
                    }
                }
            }
        }
    }

//merging code

    //flag for merging, will equal 1 if merging occurs
    int didmerge = 0;

    //goes through every cell in row major order
    for (int currrow = 0; currrow < rows; currrow++){
        for (int currcol = rows - 1; currcol >= 0; currcol--){

            //if the cell isn't empty 
            if(cur_game->cells[currrow*cols+currcol] != -1){

                //finding a like tile for the cell to merge with ;) (basically 2048 tinder)
                for(int targ_merge = currcol - 1; targ_merge >= 0; targ_merge--){

                    //a tile has been found
                    if(cur_game->cells[currrow*cols+targ_merge] != -1){

                        //if it is not equal to the cell we are trying to merge the code will move onto better things like merging other cells
                        if(cur_game->cells[currrow*cols+targ_merge] != cur_game->cells[currrow*cols+currcol]){
                            break;
                        }

                        //it's a match! merge those baddies
                        cur_game->cells[currrow*cols+currcol] = cur_game->cells[currrow*cols+currcol] * 2;
                        cur_game->cells[currrow*cols+targ_merge] = -1;
                        cur_game->score = cur_game->score + cur_game->cells[currrow*cols+currcol];

                        //set off the merge flag 
                        didmerge = 1;

                        //continue merging
                        break;
                    }
                }
            }
        }
    }

//same as above sliding code without the flag
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

    //if either flag is set then it was a valid move and return 1
    if ((didmove || didmerge) == 1){
        return 1;
    }
    
    //if neither flag was set then the move was invalid and return 0    
    return 0;
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

    //goes through every cell
    for(int therow = 0; therow < rows; therow++){
        for(int thecol = 0; thecol < cols; thecol++){

            //if any cell is empty there are still possible moves, return 1
            if (cur_game->cells[therow*cols+thecol] == -1){
                return 1;
            }
            //if any cell has a like neighbor then there are still possible moves, return 1
            if (cur_game->cells[(therow+1)*cols+thecol] == cur_game->cells[therow*cols+thecol]){
                return 1;
            }
            if (cur_game->cells[therow*cols+thecol] == cur_game->cells[therow*cols+(thecol+1)]){
                return 1;
            }
        }
    }
    //if there are no more possible moves then return 0, game over
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
