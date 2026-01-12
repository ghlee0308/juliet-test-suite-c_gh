/**
 * Test file: test_039
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

static void goodB2G()
{
    int * data;
    /* Initialize data */
    data = NULL;
    data = (int *)malloc(100*sizeof(int));
    if (data == NULL) {exit(-1);}
    
    free(data);
    /* do nothing */
    
    ; /* empty statement needed for some flow variants */
}
int main() {
    // Test execution
    return 0;
}
