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
        // maybe a goto statement?
    }
}
int parseExpression(); // ?
int parseBinaryFunction(const char* operand_symbol){
    matchToken(LEFT_PAREN);
    int operand1 = parseExpression();
    matchToken(SEPARATOR);
    int operand2 = parseExpression();
    matchToken(RIGHT_PAREN);
    int result;
    if(strcmp(operand_symbol,"xor") == 0){

    }
    else if(strcmp(operand_symbol,"ls") == 0){

    }
    else if(strcmp(operand_symbol,"rs") == 0){

    }
    else if(strcmp(operand_symbol,"lr") == 0){

    }
    else if(strcmp(operand_symbol,"rr") == 0){

    }
    return result;
}

int parseUnaryFunction(){
    matchToken(LEFT_PAREN);
    // not 
    matchToken(RIGHT_PAREN);
}
int parseFactor(){
    token t = current_token;
    if(t.type == INTEGER){
        matchToken(INTEGER);
        return atoi(t.symbol);
    }
    else if(t.type == IDENTIFIER){

        matchToken(IDENTIFIER);
        // return the val of identifier from hashmap
    }
    else if(t.type == STR_OPERATOR_BINARY){
        const char* symbol = t.symbol;
        matchToken(STR_OPERATOR_BINARY);
        return parseBinaryFunction(symbol);
    }
    else if(t.type == STR_OPERATOR_UNARY){
        matchToken(STR_OPERATOR_UNARY);
        return parseUnaryFunction(); // it's only not() though :D
    }
    else if (t.type == LEFT_PAREN){
        matchToken(LEFT_PAREN);
        int res = parseExpression();
        matchToken(RIGHT_PAREN);
        return res;
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

char* convertDecimalToBinary(const char* decimal){
    int decimal_integer = atoi(decimal);
    char* binary = malloc(64 * sizeof(char));
    int cur_len = 0;
    for(int i = 0; decimal_integer > 0; i++){
        binary[i] = decimal_integer % 2;
        decimal_integer /= 2;
        cur_len = i;
    }
    return binary;
}
int pow(int base, int power){
    int res = 1;
    for(int i = 0 ; i < power; i++){
        res *= base;
    }
    return res;
}
int convertBinaryToDecimal(const char* binary){
    int res = 0;
    for(int i = 0; i < 64; i++){
        if(binary[i] == '1'){
            res += pow(2, i);
        }
    }
    return res;
}