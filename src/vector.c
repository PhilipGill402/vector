#include "vector.h"

struct int_vector {
    int* array; 
    int size;
    int capacity;
};

int_vector* create_vector(){
    //start with 10 elements
    struct int_vector* vec = malloc(sizeof(*vec));
    if (!vec){
        fprintf(stderr, "Failed to allocat memory for the vector\n");
        return NULL;
    }
    
    vec->array = malloc(10 * sizeof(int));

    if (!vec->array){
        fprintf(stderr, "Failed to allocate memory for the array\n");
        free(vec);
        return NULL;
    }

    vec->size = 0;
    vec->capacity = 10;

    return vec;
}

int* resize(struct int_vector* vec, int new_capacity){
    int* ptr = realloc(vec->array, sizeof(int) * new_capacity);

    if (ptr == NULL){
        fprintf(stderr, "Reallocation failed\n");
        return NULL;
    }
    
    vec->capacity = new_capacity;
    vec->array = ptr;
    
    return ptr;
}

int size(struct int_vector* vec){
    return vec->size;
}

void push_back(struct int_vector* vec, int num){
    // if the array is full then double its capacity  
    if (size(vec) == vec->capacity){
        resize(vec, vec->capacity * 2);
    } 

    vec->array[size(vec)] = num;
    vec->size++;

}

int pop_back(struct int_vector* vec){
    if (size(vec) == 0){
        fprintf(stderr, "pop_back() called on empty vector\n");
        return 0;
    } 

    int element = vec->array[size(vec)-1];
    vec->size--;
    
    //if the size of the vector drops to 25% of its capacity then halve its capacity
    if (size(vec) * 4 <= vec->capacity){
        resize(vec, (int)(vec->capacity / 2));
    }


    return element;
}

void print_vector(struct int_vector* vec){
    printf("<");
    for (int i = 0; i < size(vec) - 1; i++){
        printf("%d, ", vec->array[i]);
    }
    if (!empty(vec)){
        printf("%d>\n", vec->array[size(vec) - 1]);
    } else {
        printf(">\n");
    }
}

void destroy_vector(struct int_vector* vec){
    free(vec->array);
    vec->array = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

bool empty(struct int_vector* vec){
    if (vec == NULL) {
        fprintf(stderr, "empty() called on NULL vector\n");
        return true;
    }
    
    return size(vec) == 0;
}

int get(struct int_vector* vec, int index){
    if (index > size(vec)){
        fprintf(stderr, "'index' is out of the range of the vector");
        return -1;
    }
    return vec->array[index];
}

int front(struct int_vector* vec){
    if (empty(vec)){
        fprintf(stderr, "cannot get first element of empty vector\n");
        return -1;
    }

    return vec->array[0];
}

int back(struct int_vector* vec){
    if (empty(vec)){
        fprintf(stderr, "cannot get last element of empty vector\n");
        return -1;
    }

    return vec->array[size(vec) - 1];
}

int main(){
    struct int_vector* ptr = create_vector();
    for (int i = 0; i < 15; i++){
        push_back(ptr, i);
    }
   
    print_vector(ptr);
    
    printf("%d\n", back(ptr)); 
    destroy_vector(ptr);
    return 0;
}
