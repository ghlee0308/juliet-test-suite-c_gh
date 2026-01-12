/**
 * Test file: test_031
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

void CWE476_NULL_Pointer_Dereference__deref_after_check_01_bad()
{
    {
        
        int *intPointer = NULL;
        if (intPointer == NULL)
        {
            printIntLine(*intPointer);
        }
    }
}
int main() {
    // Test execution
    return 0;
}
