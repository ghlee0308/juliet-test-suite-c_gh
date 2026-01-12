/**
 * Test file: test_008
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

void CWE480_Use_of_Incorrect_Operator__basic_01_bad()
{
    
    if(helperBad == NULL)
    {
        printLine("Got a NULL");
    }
}
int main() {
    // Test execution
    return 0;
}
