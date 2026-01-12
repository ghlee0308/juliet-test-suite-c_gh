/**
 * Test file: test_040
 * Type: bad
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printLine(const char* str) {
    if (str != NULL) printf("%s\n", str);
}

void printIntLine(int val) {
    printf("%d\n", val);
}

void printHexCharLine(char c) {
    printf("%02x\n", (unsigned char)c);
}

void CWE476_NULL_Pointer_Dereference__null_check_after_deref_01_bad()
{
    {
        int *intPointer = NULL;
        intPointer = (int *)malloc(sizeof(int));
        *intPointer = 5;
        printIntLine(*intPointer);
        
        if (intPointer != NULL)
        {
            *intPointer = 10;
        }
        printIntLine(*intPointer);
    }
}
int main() {
    // Test execution
    return 0;
}
