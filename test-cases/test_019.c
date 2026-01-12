/**
 * Test file: test_019
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

void test_019()
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
