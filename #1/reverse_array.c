#include <stdio.h>
#include <stdlib.h>


int main(){
    int original_array[9] = {36, 56, 54, 32, 67, 89, 90, 32, 21};

    printf("Original array: ");
    for(int i=0; i<9; ++i){
        printf("%d ", original_array[i]);
    }

    printf("\nReversed array: ");
    for(int i=8; i>=0; --i){
        printf("%d ", original_array[i]);
    }
    free(original_array);
    return 0;
}