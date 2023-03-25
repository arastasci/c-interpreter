#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include "token.h"

int xorFunction(int operand1, int operand2){ // xor function
    return operand1 ^ operand2;
}
int lsFunction(int operand, int shift_amount){ // ls function
    return operand << shift_amount;
}
int rsFunction(int operand, int shift_amount){ // rs function
    return operand >> shift_amount;
}
int lrFunction(int operand, int rotate_amount){ // lr function
    return (operand << rotate_amount)|(operand >> (64 - rotate_amount));
}
int rrFunction(int operand, int rotate_amount){ // rr function
    return (operand >> rotate_amount)|(operand << (64 - rotate_amount));
}

int_64 parseBinaryFunction(const char* operand_symbol){ // binary functions
    int_64 result;
    matchToken(LEFT_PAREN);
    int_64 operand1 = parseBitwiseOrExpression();
    matchToken(SEPARATOR);
    int_64 operand2 = parseBitwiseOrExpression();
    matchToken(RIGHT_PAREN);

    if(strncmp(operand_symbol,"xor",3) == 0){
         return xorFunction(operand1, operand2);

    }
    if(strncmp(operand_symbol,"ls",3) == 0){
         return lsFunction(operand1, operand2);
    }
    if(strncmp(operand_symbol,"rs", 2) == 0){
        return rsFunction(operand1, operand2);
    }
    if(strncmp(operand_symbol,"lr", 2) == 0){
        return lrFunction(operand1, operand2);
    }
    if (strncmp(operand_symbol,"rr", 2) == 0){
        return rrFunction(operand1, operand2);
    }
    // raise error // impossible
    return 0; // impossible

}

int_64 parseUnaryFunction(){ // not function
    matchToken(LEFT_PAREN);

    int_64 res = parseBitwiseOrExpression();
    res = res ^ -1;
    matchToken(RIGHT_PAREN);
    return res;
}
int_64 parseFactor(){
    token t = current_token;
    if(t.type == INTEGER){ //
        matchToken(INTEGER);
        return atoll(t.symbol);
    }
    else if(t.type == IDENTIFIER){
        matchToken(IDENTIFIER);
        variable* var = find(t.symbol);
        return var!=NULL ? var->value : 0;
        // if var is not in hashmap (not assigned previously), return 0, else return the value of var
    }
    else if(t.type == STR_OPERATOR_BINARY){
        const char* symbol = t.symbol;
        matchToken(STR_OPERATOR_BINARY);
        return parseBinaryFunction(symbol);
    }
    else if(t.type == STR_OPERATOR_UNARY){
        matchToken(STR_OPERATOR_UNARY);
        return parseUnaryFunction(); // it's only not(<var>) though :D // lovely views also :D anani sikeyim aras
    }
    else if (t.type == LEFT_PAREN){
        matchToken(LEFT_PAREN);
        int_64 res = parseBitwiseOrExpression();
        matchToken(RIGHT_PAREN);
        return res;
    }
    // raise error from token.c
    raiseTokenError();
    return 1; // as terms have multiplicative tokens, this value evades division by zero errors5
}
int_64 parseTerm(){
    int_64 result = parseFactor();

    while(current_token.type == OPERATOR_MULTIPLICATIVE){
        token t = current_token;
        matchToken(OPERATOR_MULTIPLICATIVE);
        if(strncmp(t.symbol,"*", 1) == 0){
            result *= parseFactor();
        }
        else{
            result /= parseFactor();
        }

    }
    return result;
}

int_64 parseExpression(){
    int_64 result = parseTerm();
    while(token_index < token_count && current_token.type == OPERATOR_ADDITIVE){    // add or subtract (lowest precedency in the grammar)
        token t = current_token;
        matchToken(OPERATOR_ADDITIVE);
        if(strncmp(t.symbol,"+", 1) == 0){
            result += parseTerm() ;
        }
        else{
            result -= parseTerm();
        }
    }
    return result;
}
variable* parseVariable(){  // returns the variable pointer
    token t = current_token;
    matchToken(IDENTIFIER);
    variable *var = find(t.symbol); // check if the variable is in the hashmap
    if(var == NULL){
        return insert(t.symbol); // if not, insert it and return the pointer
    }
    else{
        return var; // if it is, return the pointer
    }
}

int_64 parseBitwiseAndExpression(){
    int_64 result = parseExpression();
    while (token_index < token_count && strcmp(current_token.symbol, "&")==0){    // bitwise 'or' and 'and' (second lowest precedency in the grammar)
        token t = current_token;
        matchToken(OPERATOR_BITWISE);
        result &= parseExpression();
    }
    return result;
};
int_64 parseBitwiseOrExpression(){
    int_64 result = parseBitwiseAndExpression();

    while (token_index < token_count && strcmp(current_token.symbol, "|")==0){    // bitwise 'or' and 'and' (second lowest precedency in the grammar)
        token t = current_token;
        matchToken(OPERATOR_BITWISE);
        result |= parseBitwiseAndExpression();
    }
    return result;
};
void parseAssignment(){
    variable* var = parseVariable(); // TODO: mustnt initialize var if there is error
    matchToken(ASSIGNMENT);
    int_64 response = parseBitwiseOrExpression();
    if(!has_error && token_index == token_count){
        var->value = response;
    }
    else{
        printf("Error!\n");
    }
}

void parseStatement(){  // two types of statements: assignment and expression
    if(token_array[1].type == ASSIGNMENT){
        parseAssignment(); // assigns the rhs expr to lhs variable
    }
    else{
        int_64 result = parseBitwiseOrExpression();
        if(!has_error && token_index == token_count){
            printf("%lld\n", result);
        }
        else{
            printf("Error!\n");
        }
    }
    // TODO: how do i even handle the comments lol yasin kocum sende
}
