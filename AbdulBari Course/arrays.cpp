#include "head/cpp_dsa.h"

using namespace std;

int main(){
    /*
    int  n;
    cout << "Enter size" << endl;
    cin >> n;
    A[] = {2, 4, 6, 8, 10, 12, 14} // This is an Error in many compilers
    // Expected Error: Variable Sized Obejct May Not be defined
*/
    int A[] = {2, 4, 6 ,8, 10, 12, 14, 16, 18};
    printf("%d\n", sizeof(A));
    printf("%d\n", A[2]);

    // If values of A not assigned
   /* for(int x: A){
        cout << x <<endl; // Printing Garbage Value
*/

    
}