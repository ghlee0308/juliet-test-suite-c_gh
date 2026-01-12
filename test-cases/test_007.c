/**
 * Test file: test_007
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

void CWE401_Memory_Leak__malloc_realloc_char_01_bad()
{
    {
        char * data = (char *)malloc(100*sizeof(char));
        if (data == NULL) {exit(-1);}
        /* Initialize and make use of data */
        strcpy(data, "A String");
        printLine(data);
        
        data = (char *)realloc(data, (130000)*sizeof(char));
        if (data != NULL)
        {
            /* Reinitialize and make use of data */
            strcpy(data, "New String");
            printLine(data);
            free(data);
        }
    }
}
int main() {
    // Test execution
    return 0;
}
