#include <stdio.h>
#include <stdbool.h>
#include "tokenizer.h"
#include "parser.h"
#include "hash.h"
int main(){
    char input [258];
    initializeHashMap();
    allocateArrayMemory(); // allocate token array mem
    printf("> ");
    while(fgets(input, 258, stdin) != NULL){
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
        printf("> ");
    }
    deallocHashMap();
    return 0;
}
