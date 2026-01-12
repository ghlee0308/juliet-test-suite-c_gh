/**
 * Test file: test_016
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
        char * data = (char *)malloc(100*sizeof(char));
        if (data == NULL) {exit(-1);}
        char * tmpData;
        /* Initialize and make use of data */
        strcpy(data, "A String");
        printLine(data);
        tmpData = (char *)realloc(data, (130000)*sizeof(char));
        
        if (tmpData != NULL)
        {
            data = tmpData;
            /* Reinitialize and make use of data */
            strcpy(data, "New String");
            printLine(data);
        }
        free(data);
    }
}
int main() {
    // Test execution
    return 0;
}
