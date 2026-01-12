/**
 * Test file: test_024
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

void CWE476_NULL_Pointer_Dereference__binary_if_01_bad()
{
    {
        twoIntsStruct *twoIntsStructPointer = NULL;
        
        if ((twoIntsStructPointer != NULL) & (twoIntsStructPointer->intOne == 5))
        {
            printLine("intOne == 5");
        }
    }
}
int main() {
    // Test execution
    return 0;
}
