#include "head/cpp_dsa.h"

struct Array{
    int A;

};
int BinarySearch(struct Array arr, int key){
    int low, mid, high;
    low = 0;
    high = arr.length-1;

    while(low <= high){
        if(key == arr.A[mid]){
            printf("%d Element found", key);
            return mid;
        }
        else if(key < arr.A[mid]){
            high = mid-1;
        }
        else high = mid+1;
    }
}

int main(){
    struct Array arr = {{2, 3, 4, 5, 6}, 10, 5};    
}