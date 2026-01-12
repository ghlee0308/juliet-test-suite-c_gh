/**
 * Test file: test_001
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

void CWE476_NULL_Pointer_Dereference__char_01_bad()
{
    char * data;
    
    data = NULL;
    
    /* printLine() checks for NULL, so we cannot use it here */
    printHexCharLine(data[0]);
}
int main() {
    // Test execution
    return 0;
}
