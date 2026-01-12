/**
 * Test file: test_019
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

void CWE369_Divide_by_Zero__int_fscanf_divide_01_bad()
{
    int data;
    /* Initialize data */
    data = -1;
    
    fscanf(stdin, "%d", &data);
    
    printIntLine(100 / data);
}
int main() {
    // Test execution
    return 0;
}
