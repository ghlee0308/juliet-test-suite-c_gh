/**
 * Test file: test_026
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
    {
        stdThread threadA = NULL;
        stdThread threadB = NULL;
        if (!stdThreadLockCreate(&gGoodLock))
        {
            return;
        }
        if (!stdThreadCreate(helperGood, NULL, &threadA))
        {
            threadA = NULL;
        }
        if (!stdThreadCreate(helperGood, NULL, &threadB))
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
        stdThreadLockDestroy(gGoodLock);
        printIntLine(gGoodInt);
    }
}
int main() {
    // Test execution
    return 0;
}
