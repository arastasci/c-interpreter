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

response parseBinaryFunction(const char* operand_symbol){ // binary functions
    response response;
    matchToken(LEFT_PAREN);
    int operand1 = parseBitwiseOrExpression().value;
    matchToken(SEPARATOR);
    int operand2 = parseBitwiseOrExpression().value;
    matchToken(RIGHT_PAREN);

    if(strncmp(operand_symbol,"xor",3) == 0){
        response.value = xorFunction(operand1, operand2);
        return response;
    }
    if(strncmp(operand_symbol,"ls",3) == 0){
        response.value = lsFunction(operand1, operand2);
        return response;
    }
    if(strncmp(operand_symbol,"rs", 2) == 0){
        response.value = rsFunction(operand1, operand2);
        return response;
    }
    if(strncmp(operand_symbol,"lr", 2) == 0){
        response.value = lrFunction(operand1, operand2);
        return response;
    }
    if (strncmp(operand_symbol,"lr", 2) == 0){
        response.value = rrFunction(operand1, operand2);
        return response;
    }
    else{ // if none of the above, return error
        response.error = 1;
        return response;
    }
    // only option left is rr
    return response;

}

response parseUnaryFunction(){ // not function
    matchToken(LEFT_PAREN);
    response response;
    int res = parseBitwiseOrExpression().value;
    res = res ^ -1;
    matchToken(RIGHT_PAREN);
    response.value = res;
    return response;
}
response parseFactor(){
    token t = current_token;
    response response;
    if(t.type == INTEGER){ //
        matchToken(INTEGER);
        response.value = atoi(t.symbol);
        return response;
    }
    else if(t.type == IDENTIFIER){

        matchToken(IDENTIFIER);
        variable* var = find(t.symbol);
        response.value = var!=NULL ? var->value : insert(t.symbol)->value;
        return response;
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
        int res = parseBitwiseOrExpression().value;
        matchToken(RIGHT_PAREN);
        response.value = res;
        return response;
    }
    else{
        response.error = 1;
        return response;
    }
}
response parseTerm(){
    response response = parseFactor();
    if (response.error == 1) return response; // if there is an error, return the error (no need to continue)
    int result = response.value; // first factor
    while(current_token.type == OPERATOR_MULTIPLICATIVE){
        token t = current_token;
        matchToken(OPERATOR_MULTIPLICATIVE);
        if(strncmp(t.symbol,"*", 1) == 0){
            result *= parseFactor().value;
        }
        else{
            result /= parseFactor().value;
        }

    }
    response.value = result;
    return response;
}

response parseExpression(){
    response response = parseTerm();
    if (response.error == 1) return response; // if there is an error, return the error (no need to continue)
    int result = response.value;
    while(token_index < token_count && current_token.type == OPERATOR_ADDITIVE){    // add or subtract (lowest precedency in the grammar)
        token t = current_token;
        matchToken(OPERATOR_ADDITIVE);
        response = parseTerm();
        if (response.error == 1) return response; // if there is an error, return the error (no need to continue)
        if(strncmp(t.symbol,"+", 1) == 0){
            result += response.value;
        }
        else{
            result -= response.value;
        }
    }
    printTokens();
    printf("type: %d, symbol: %s\n",
           current_token.type, current_token.symbol);
    response.value = result;
    return response;
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

response parseBitwiseAndExpression(){
    response response = parseExpression();
    if (response.error == 1) return response; // if there is an error, return the error (no need to continue)
    int result = response.value;
    while (token_index < token_count && strcmp(current_token.symbol, "&")==0){    // bitwise 'or' and 'and' (second lowest precedency in the grammar)
        token t = current_token;
        matchToken(OPERATOR_BITWISE);
        response = parseExpression();
        if (response.error == 1) return response; // if there is an error, return the error (no need to continue)
        result &= response.value;
    }
    response.value = result;
    return response;
};
response parseBitwiseOrExpression(){
    response response = parseBitwiseAndExpression();
    if (response.error == 1) return response; // if there is an error, return the error (no need to continue)
    int result = response.value;
    while (token_index < token_count && strcmp(current_token.symbol, "|")==0){    // bitwise 'or' and 'and' (second lowest precedency in the grammar)
        token t = current_token;
        matchToken(OPERATOR_BITWISE);
        response = parseBitwiseAndExpression();
        if (response.error == 1) return response; // if there is an error, return the error (no need to continue)
        result |= response.value;
    }
    if(current_token.symbol != NULL){
        response.error = 1;
        return response;
    }
    response.value = result;
    return response;
};
void parseAssignment(){
    variable* var = parseVariable();
    matchToken(ASSIGNMENT);
    response response = parseBitwiseOrExpression();
    if (response.error != 1){
        var->value = response.value;
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
        response response = parseBitwiseOrExpression();
        if (response.error != 1){
            printf("%d\n",response.value);
        }
        else{
            printf("Error!\n");
        }
    }
    // TODO: how do i even handle the comments lol yasin kocum sende
}
