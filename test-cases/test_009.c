/**
 * Test file: test_009
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

void test_009()
{
    {
        int intRand = rand();
        
        if(intRand = 5)
        {
            printLine("i was 5");
        }
    }
}
int main() {
    // Test execution
    return 0;
}
