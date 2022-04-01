#include "vector.h"
#include <stdlib.h>


vector_t * createVector(int initialSize)
{
    vector_t * new_struct = malloc(sizeof(vector_t));
    new_struct->maxSize = initialSize;
    new_struct->size = 0;
    new_struct->array = malloc(new_struct->maxSize * sizeof(int *));

    return new_struct;
}

void destroyVector(vector_t * vector)
{
    free(vector->array);
    free(vector);
}

void resize(vector_t * vector)
{
    vector->maxSize = vector->maxSize * 2;
    vector->array = realloc(vector->array, vector->maxSize * sizeof(int *));
}

void push_back(vector_t * vector, int element)
{
    if (vector->size == vector->maxSize){
        resize(vector);
    }
    vector->array[vector->size + 1] = element;
    vector->size = vector->size + 1;
}

int pop_back(vector_t * vector)
{
    if(vector->size == 0){
        return 0;
    }
    int ret_val = vector->array[vector->size];
    vector->size = vector->size - 1;
    return ret_val;
}

int access(vector_t * vector, int index)
{
    if (index > vector->size - 1){
        return 0;
    }
    int ret_value = vector->array[index + 1];
    return ret_value;
}

