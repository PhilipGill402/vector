#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct int_vector int_vector; 

int_vector create_vector();
int size(struct int_vector* vec);
void push_back(struct int_vector* vec, int num);
int pop_back(struct int_vector* vec);
void print_vector(struct int_vector* vec);
