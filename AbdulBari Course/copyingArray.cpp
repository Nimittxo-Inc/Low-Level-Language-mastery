#include "head/cpp_dsa.h"

int main(){

    int *p = new int[5]; // We need to increase the size of this array now !
    p[0] = 1;
    p[1] = 2;
    p[2] = 3;
    p[3] = 4;
    p[4] = 5;
    int *q = new int[10]; // Now we create a new array with desires size !

    for(int i=0; i<=10; i++){
        q[i] = p[i];
    }
    for(int i=0; i<=10; i++){
        std::cout<<*p<<std::endl;
    }
    p=q;
    q= NULL;
    free(q);
// freed up the array 
}