/**
 * Test file: test_014
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

void test_014()
{
    {
        stdThread threadA = NULL;
        stdThread threadB = NULL;
        gBadInt = 0;
        if (!stdThreadCreate(helperBad, NULL, &threadA))
        {
            threadA = NULL;
        }
        if (!stdThreadCreate(helperBad, NULL, &threadB))
        {
            threadB = NULL;
        }
        if (threadA && stdThreadJoin(threadA))
        {
            stdThreadDestroy(threadA);
        }
        if (threadB && stdThreadJoin(threadB))
        {
            stdThreadDestroy(threadB);
        }
        printIntLine(gBadInt);
    }
}
int main() {
    // Test execution
    return 0;
}
