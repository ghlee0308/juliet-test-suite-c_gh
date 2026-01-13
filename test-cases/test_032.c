/**
 * Test file: test_032
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

void test_032()
{
    int * data;
    data = NULL;
    
    data = (int *)malloc(100*sizeof(int));
    if (data == NULL) {exit(-1);}
    /* Initialize and make use of data */
    data[0] = 5;
    printIntLine(data[0]);
    
    ; /* empty statement needed for some flow variants */
}
int main() {
    // Test execution
    return 0;
}
