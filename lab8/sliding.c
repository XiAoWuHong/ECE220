#include "sliding.h"
/*  Slide all values of array up
*/
void slide_up(int* my_array, int rows, int cols){
    int i; //for finding target rows
    int n;  //for column numbers
    int m;  //for row numbers
    for(n = 0; n < cols; n++){
        for (m = 0; m < rows; m++){
            if (my_array[m*cols+n] != -1){
            
            for (i = 0; i < m; i++){
                
                    if (my_array[(i)*cols+n] == -1){
                        my_array[(i)*cols+n] = my_array[(m)*cols+n];
                        my_array[(m)*cols+n] = -1;
                    }
                }
            }
        }
    }

    return;
}
