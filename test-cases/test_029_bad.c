/**
 * Test file: test_029
 * Type: bad
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

void CWE416_Use_After_Free__return_freed_ptr_01_bad()
{
    {
        /* Call the bad helper function */
        char * reversedString = helperBad("BadSink");
        printLine(reversedString);
        /* free(reversedString);
         * This call to free() was removed because we want the tool to detect the use after free,
         * but we don't want that function to be free(). Essentially we want to avoid a double free
         */
    }
}
int main() {
    // Test execution
    return 0;
}
