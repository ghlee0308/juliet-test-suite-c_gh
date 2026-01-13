/**
 * Test file: test_033
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

void test_033()
{
    int * data;
    int tmpData = 5;
    
    {
        data = &tmpData;
    }
    
    printIntLine(*data);
}
int main() {
    // Test execution
    return 0;
}
