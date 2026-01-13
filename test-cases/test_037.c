/**
 * Test file: test_037
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

void test_037()
{
    long * data;
    
    data = NULL;
    
    printLongLine(*data);
}
int main() {
    // Test execution
    return 0;
}
