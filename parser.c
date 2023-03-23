#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include "token.h"
token current_token;
int tokenIndex = 0;

token getNextToken(){
    return token_array[tokenIndex++];
}

void matchToken(token_type tokenType){
    // if the token_type matches with the expected type, continue, else raise err
    if(current_token.type == tokenType){
        current_token = getNextToken();
    }
    else {
        // raise error
        printf("Error!");
    }
}
int parseExpression(); // ?
int parseFactor(){
    token t = current_token;
    if(t.type == INTEGER){
        matchToken(INTEGER);
        return atoi(t.symbol);
    }
    else if (t.type == LEFT_PAREN){
        matchToken(LEFT_PAREN);
        return parseExpression();
    }
}
int parseTerm(){
    int result = parseFactor();
    while(current_token.type == OPERATOR_MULTIPLICATIVE){
        token t = current_token;
        matchToken(OPERATOR_MULTIPLICATIVE);
        if(strcmp(t.symbol,"*")){
            result *= parseFactor();
        }
        else{
            result /= parseFactor();
        }

    }
    return result;
}

int parseExpression(){
    int result = parseTerm();
    while(current_token.type == OPERATOR_ADDITIVE){
        token t = current_token;
        matchToken(OPERATOR_ADDITIVE);
        if(strcmp(t.symbol,"+")){
            result += parseTerm();
        }
        else{
            result -= parseTerm();
        }
    }
    return result;
}
