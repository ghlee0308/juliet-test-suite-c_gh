/**
 * Test file: test_018
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

void CWE476_NULL_Pointer_Dereference__struct_01_bad()
{
    twoIntsStruct * data;
    
    data = NULL;
    
    printIntLine(data->intOne);
}
int main() {
    // Test execution
    return 0;
}
