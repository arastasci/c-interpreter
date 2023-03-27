#include <stdio.h>
#include <stdbool.h>
#include "tokenizer.h"
#include "parser.h"
#include "hash.h"
int main(){
    char input [257];
    initializeHashMap();
    allocateArrayMemory(); // allocate token array mem
    while(fgets(input, 257, stdin) != NULL){
        has_error = false;
        tokenize(input);
       // printTokens(); // for debug purposes
        if(!has_error){
            parseStatement();
        }
        else{
            printf("Error!\n");
        }
        freeArrayMemory(); // free token array mem
    }
    deallocHashMap();
    return 0;
}
