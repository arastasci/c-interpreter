#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "parser.h"
#include "hash.h"
int main(){
    char input [257];
    initializeHashMap();
    allocateArrayMemory(); // allocate token array mem
    while(fgets(input, 257, stdin) != NULL){
        tokenize(input);
        printTokens(); // for debug purposes
        parseStatement();
        freeArrayMemory();// free token array mem
        error = false;
    }
    deallocHashMap();
    return 0;
}
