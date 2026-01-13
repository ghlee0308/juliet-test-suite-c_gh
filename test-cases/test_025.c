/**
 * Test file: test_025
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

void test_025()
{
    {
        stdThread threadA = NULL;
        stdThread threadB = NULL;
        int valBadSink;
        valBadSink = 0;
        if (!stdThreadCreate(helperBad, (void*)&valBadSink, &threadA))
        {
            threadA = NULL;
        }
        if (!stdThreadCreate(helperBad, (void*)&valBadSink, &threadB))
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
        printIntLine(valBadSink);
    }
}
int main() {
    // Test execution
    return 0;
}
