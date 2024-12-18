#include <stdio.h>

#define PRAGMA_MACRO _Pragma("GCC diagnostic push")

int main() {
    PRAGMA_MACRO
    printf("Test of _Pragma macro\n");
    return 0;
}
