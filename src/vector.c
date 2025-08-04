#include "vector.h"

struct int_vector {
    int* array; 
    int size;
    int capacity;
};

struct int_vector_iterator{
    int* current;
    int* end;
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

int_vector_iterator* iterator(struct int_vector* vec){
    return create_iterator(vec); 
}

void reserve(struct int_vector* vec, int new_capacity){
    int* ptr = realloc(vec->array, sizeof(int) * new_capacity);

    if (ptr == NULL){
        fprintf(stderr, "Reallocation failed\n");
        return;
    }
    
    vec->capacity = new_capacity;
    vec->array = ptr;
    
}

int size(struct int_vector* vec){
    return vec->size;
}

void push_back(struct int_vector* vec, int num){
    // if the array is full then double its capacity  
    if (size(vec) == vec->capacity){
        reserve(vec, vec->capacity * 2);
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
        reserve(vec, (int)(vec->capacity / 2));
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

void insert(struct int_vector* vec, int element, int index){
    //if the vector is full then reserve double its capacity
    if (size(vec) + 1 > vec->capacity){
        reserve(vec, vec->capacity * 2);
    }

    //shift everything over one
    for (int i = size(vec) + 1; i >= index; i--){
        vec->array[i] = vec->array[i - 1]; 
    }
    
    //set the element at index to the given element
    vec->array[index] = element;
    vec->size++;

}

void erase(struct int_vector* vec, int index){
    if (index >= size(vec)){
        fprintf(stderr, "index given is outside the bounds of the vector\n");
        return;
    }
    
    //we're removing the last element
    if (index == size(vec) - 1){
        vec->size--;
    } else {
        for (int i = index; i < size(vec) - 1; i++){
            vec->array[i] = vec->array[i + 1];
        }

        vec->size--;
    }
    
    if (size(vec) * 4 <= vec->capacity){
        reserve(vec, (int)(vec->capacity / 2));
    }

    
}

void swap(struct int_vector* vec, struct int_vector* other_vec){
    //array 
    int* tmp = vec->array; 
    vec->array = other_vec->array;
    other_vec->array = tmp;
    
    //size
    int temp = vec->size;
    vec->size = other_vec->size;
    other_vec->size = temp;

    //capcaity
    temp = vec->capacity;
    vec->capacity = other_vec->capacity;
    other_vec->capacity = temp;

}

void clear(struct int_vector* vec){
    vec->size = 0;
    reserve(vec, 10);
}

void assign(struct int_vector* vec, int num, int num_copies){
    if (num_copies > vec->capacity){
        reserve(vec, num_copies * 2);
    }

    vec->size = num_copies;

    for (int i = 0; i < size(vec); i++){
        vec->array[i] = num;
    }
}

int capacity(struct int_vector* vec){
    return vec->capacity;
}

void downsize(struct int_vector* vec, int new_size){
    if (new_size > size(vec)){
        fprintf(stderr, "given size is larger than size of the vector\n");
        return;
    } 
     
    vec->size = new_size;

    if (size(vec) > capacity(vec)){
        reserve(vec, 2 * size(vec));
    }
}

void upsize(struct int_vector* vec, int new_size, int element){
    if (new_size < size(vec)){
        fprintf(stderr, "given size is smaller than size of the vector\n");
        return;
    } 
    
    int old_size = vec->size; 
    vec->size = new_size;

    if (size(vec) > capacity(vec)){
        reserve(vec, 2 * size(vec));
    }

    for (int i = old_size; i < new_size; i++){
        vec->array[i] = element;
    }
}

void shrink_to_fit(struct int_vector* vec){
    vec->capacity = vec->size;
}

int* data(struct int_vector* vec){
    return vec->array;
}



int_vector_iterator* create_iterator(int_vector* vec){
    int_vector_iterator* itr = malloc(sizeof(*itr));
    itr->current = vec->array;
    itr->end = vec->array + size(vec);
    return itr;
}

int has_next(int_vector_iterator* itr){
    return itr->current != itr->end;
}


int next(int_vector_iterator* itr){
    if (has_next(itr)){
        int element = *(itr->current);
        itr->current++;

        return element;
    } else {
        fprintf(stderr, "vector has no more elements\n");
        return -1;
    }
}
int main(){
    return 0;
}
