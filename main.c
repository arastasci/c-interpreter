#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "parser.h"
int main(){
    char input [257];
    while(fgets(input, 257, stdin) != NULL){

        tokenize(input);
        printTokens();
        printf("%d\n",parseExpression());
        free(token_array);
    }
    return 0;
}
