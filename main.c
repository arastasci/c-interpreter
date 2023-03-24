#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "parser.h"
#include "hash.h"
int main(){
    char input [257];
    initializeHashMap();

    while(fgets(input, 257, stdin) != NULL){
        allocateArrayMemory(); // allocate token array mem
        tokenize(input);
        printTokens(); // for debug purposes
        parseStatement();
        freeArrayMemory(); // free token array mem
    }
    deallocHashMap();
    return 0;
}
