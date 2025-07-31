#include "vector.h"

struct int_vector {
    int* array; 
    int size; 
};

int_vector create_vector(){
    //start with 10 elements
    struct int_vector vec = {
        .array = (int*)malloc(10 * sizeof(int)),
        .size = 0
    };
    return vec;
}



int size(struct int_vector* vec){
    return vec->size;
}

void push_back(struct int_vector* vec, int num){
    vec->array[size(vec)] = num;
    vec->size++;

}

int pop_back(struct int_vector* vec){
    vec->array 
}

void print_vector(struct int_vector* vec){
    printf("<")
    for (int i = 0; i < size(vec) - 2; i++){
        printf("%d, ", vec->array[i]);
    }
    printf("%d>\n", vec->array[size(vec) - 1]);
}

int main(){
    struct int_vector arr = create_vector();
    struct int_vector* ptr = &arr;
    
    for (int i = 0; i < 10; i++){
        push_back(ptr, i);
    }

    print_vector(ptr);
    return 0;
}
