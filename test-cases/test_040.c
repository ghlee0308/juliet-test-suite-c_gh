/**
 * Test file: test_040
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

void test_040()
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
