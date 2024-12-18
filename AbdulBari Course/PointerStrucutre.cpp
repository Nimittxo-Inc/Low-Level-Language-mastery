#include "head/cpp_dsa.h"


struct Rectangle{
    int height;
    int length;
}r1;

int main(){
    r1 = {10, 5};
    struct Rectangle *p=&r1;

    r1.length = 15;
    // *p.length = 20; // This is gives syntax error due to precedence Value error as . has higher presedence to *
    // so we use 
    (*p).length = 20;
    // Or C provides simpler syntax
    p->length = 10;
    
    //Creating the Instance in the Heap {using malloc}
    struct Rectangle *another_pointer;
    another_pointer=(struct Rectangle*)malloc(sizeof(struct Rectangle));
                // Used for Typecasting   // Used for assigning memeory


    printf("the value to the pointer is: %d", *p); 
    std::cout << "This was an example of structure to pointer" << std::endl;
}