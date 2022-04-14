#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>

//GROUP MEMBERS:
// V Verma, Peter Giannettos, Ben Olaivar



//self made helper function to sort the nodes as they are being made
void sorting_hat (sp_tuples * tuples, sp_tuples_node * newnode){

    sp_tuples_node * comparison_node = malloc(sizeof(sp_tuples_node));
    comparison_node = tuples->tuples_head;  //the first node we will compare the new node to is 
    int j = 1;

    //if it is less than or equal to the tuple_head
    if((comparison_node->row > newnode->row) && (comparison_node->col > newnode->col)){
        j = 0;
        newnode->next = comparison_node;
        tuples->tuples_head = newnode;
    }
      if((comparison_node->row == newnode->row) && (comparison_node->col == newnode->col)){
        j = 0;
        comparison_node->value = newnode->value;
        tuples->nz = tuples->nz - 1;
    }


    //the while loop will not stop until I tell it to stop >:)
    while (j == 1){
        
        comparison_node = comparison_node->next;    //go to next node in the linked list

        //if the newnode has the same row as the comparison node
        if (comparison_node->row == newnode->row){

            //if the newnode has the exact same coordinates as the comparison node then replace the comparison with the newnode
            if(comparison_node->col == newnode->col){
                comparison_node->next = newnode->next;  //set the next pointer of the comparison node to that of the newnode
                comparison_node = newnode;              //completely replace the comparision node with the newnode
                tuples->nz = tuples->nz - 1;
                free(newnode);
                break;
            }

            //if the newnode is in a later col than the comparison node then insert it after the comparison
            if (comparison_node->col < newnode->col){
                newnode->next = comparison_node;
                comparison_node->next = newnode;
                break;
            }
        }
        //if the newnode row is greater than the comparison node row
        if(comparison_node->row < newnode->row){

            //if the newnode col is greater than the 
            if (comparison_node->col < newnode->col){
                newnode->next = comparison_node;
                comparison_node->next = newnode;
                break; 
            }
        }
    }
    free(comparison_node);
}


sp_tuples * load_tuples(char* input_file)
{
    FILE *input = fopen(input_file, "r");           //open the given input file for reading

    sp_tuples * tuples = malloc(sizeof(sp_tuples)); //allocate memory for the tuples list thing

    fscanf(input, "%d %d", &tuples->m, &tuples->n); //dimensions of the array

    tuples->nz = 0;                                 //number of non-zero items in the array

    sp_tuples_node * temp = malloc(sizeof(sp_tuples_node));     //create temp node for ez maths
    sp_tuples_node * newnode = malloc(sizeof(sp_tuples_node));  //create the first newnode/head

    tuples->tuples_head = newnode;          //head pointer
    newnode->next = NULL;                   //set the tail 

    int youdiewhenIsayso = 0;
    while(youdiewhenIsayso == 0){           //until we reach the end of our linked list
        temp = newnode;                     //have temp = the node we are about to replace
        int readvalues = fscanf(input, "%d %d %lf", &newnode->row, &newnode->col, &newnode->value); //put the next values of the sp_array into a newnode

        //if we correctly read three values then go on
        if (readvalues == 3){
                newnode = malloc(sizeof(sp_tuples_node));   //allocate memory for the newnode
                tuples->nz = tuples->nz + 1;                //increment the non-sero items counter
                sorting_hat(tuples, newnode);               //go to helper function to sort the nodes
        }
        if(readvalues != 3){        //if we did not read three values the we have reached the end of the input file
            youdiewhenIsayso = 1;   //end the while loop
        }
    }
    free(temp);     //deallocate memory for temp node
    fclose(input);  //close the given input file for reading 
    return tuples;  //return the tuples list thing
    return NULL;    //lmao
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{

    sp_tuples_node * checknode = malloc(sizeof(sp_tuples_node));

    checknode = mat_t->tuples_head;

    for (int i = 0; i <= mat_t->nz; i++ ){
        if ((checknode->col == col) && (checknode->row == row)){
            double retval = checknode->value;
            free(checknode);
            return retval;
        }
        checknode = checknode->next;
    }


    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{

	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){


    return matB;
	// return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return matB;
    // return retmat;

}


	
void destroy_tuples(sp_tuples * mat_t){
	
    return;
}  






