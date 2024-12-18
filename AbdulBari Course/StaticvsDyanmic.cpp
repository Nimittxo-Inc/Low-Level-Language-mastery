#include "head/cpp_dsa.h"

int main(){
    int A[5] = {0};
    printf("Array %d created in stack", A);
    int *p = (int*) malloc(5*sizeof(int));
    // Stack created in Heap
    int *q = new int[5]; // Method to allocate in Cpp
    std::cout << "\nArray created in Heap " << *p <<std::endl;
    delete []p; //Method to free Heap in C++
    free(q);    //Method to free in C
}