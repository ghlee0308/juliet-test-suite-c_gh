/**
 * Test file: test_020
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

static void good1()
{
    
    if(helperGood() == NULL) /* this will sometimes be true (depending on the rand() in helperGood) */
    {
        printLine("Got a NULL");
    }
}
int main() {
    // Test execution
    return 0;
}
