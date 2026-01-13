/**
 * Test file: test_031
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

void test_031()
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
