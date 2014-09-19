#include <stdio.h>
#include "morse_code.h"

#define BUFFSIZE 5

int main(){
    char array[BUFFSIZE] = {'-','.','-'};
    printf("Test case: %s\n", array);
    int c = translate(array);
    printf("Output: %c\n", c);

    return 0;
}

