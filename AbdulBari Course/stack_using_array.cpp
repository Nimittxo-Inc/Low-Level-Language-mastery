#include "head/cpp_dsa.h"
using namespace std;

struct Stack{

    int size; //size
    int Top_Ptr; // Top pointer
    int *S;// Pointer to hold stack
};

int main(){
    struct Stack st;
    st.size = 10;
    st.S = (int *)malloc(st.size * sizeof(int));
    if(st.S == NULL){
        printf("Memory allocation failed !\n");
    }
    st.Top_Ptr = -1;

}

