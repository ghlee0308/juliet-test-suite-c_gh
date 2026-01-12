/**
 * Test file: test_034
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

void CWE369_Divide_by_Zero__int_rand_divide_01_bad()
{
    int data;
    /* Initialize data */
    data = -1;
    
    data = RAND32();
    
    printIntLine(100 / data);
}
int main() {
    // Test execution
    return 0;
}
