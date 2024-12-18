#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[10]={0};
    int n;
    printf("Enter the number: ");
    scanf("%d", &n);

    while(n>0){
        int rem = n%10;
        if(arr[rem] == 1)
            break;
        arr[rem] = 1;
        n = n/10;
    }
    if(n > 0)  // If the loop broke early, n is non-zero, meaning repeated digit found
        printf("Yes\n");
    else       // If the loop completed, no repeated digits
        printf("No\n");

    return 0;
}