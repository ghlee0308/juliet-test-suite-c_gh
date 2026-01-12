/**
 * Test file: test_036
 * Type: good
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

static void goodG2B()
{
    char * data;
    /* Initialize data */
    data = NULL;
    data = new char;
    *data = 'A';

    printHexCharLine(*data);
    
}
int main() {
    // Test execution
    return 0;
}
