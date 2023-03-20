#include <stdio.h>
#include <stdbool.h>
#include "token.h"
int main(){
    char input [257];
    while(fgets(input, 257, stdin) != NULL){
        tokenize(input);
        printTokens();


    }
    return 0;
}
