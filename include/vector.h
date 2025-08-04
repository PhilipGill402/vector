#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct int_vector int_vector; 

int_vector* create_vector();
int size(struct int_vector* vec);
void push_back(struct int_vector* vec, int num);
int pop_back(struct int_vector* vec);
void print_vector(struct int_vector* vec);
int* resize(struct int_vector* vec, int new_capacity);
void destroy_vector(struct int_vector* vec);
bool empty(struct int_vector* vec);
int get(struct int_vector* vec, int index);
int front(struct int_vector* vec);
int back(struct int_vector* vec);
