#include "head/cpp_dsa.h"

struct Array{
    int *A;
    int size;
    int length;

};

void append(struct Array *arr, int x) {
    if (arr->length < arr->size) {
        arr->A[arr->length] = x;
        arr->length++;
    } else {
        printf("Array is full. Cannot append %d.\n", x);
    }
}

void Insert(struct Array *arr, int index, int x){
    if(index >= 0 && index <= arr->length){
        for(int i=arr->length; i>index; i--){
            arr->A[i] = arr->A[i-1];
        
        arr->A[index]=x;
        arr->length++;
        }
    }
}

int main(){

    struct Array arr;
    printf("Enter the size of an Array: ");
    scanf("%d", &arr.size);
    arr.A = (int*) malloc(arr.size*sizeof(int));
    arr.length= 0;
    append(&arr, 30 );
    for(int i=0; i<arr.size; i++){
        printf(" \n%d ", arr.A[i]);
    }

    // Array initialized
    // Array created in Heap
}
