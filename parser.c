#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include "token.h"


int xorFunction(int operand1, int operand2){
    return operand1 ^ operand2;
}
int lsFunction(int operand, int shift_amount){
    return operand << shift_amount;
}
int rsFunction(int operand, int shift_amount){
    return operand >> shift_amount;
}
int lrFunction(int operand, int rotate_amount){
    return (operand << rotate_amount)|(operand >> (64 - rotate_amount));

}
int rrFunction(int operand, int rotate_amount){
    return (operand >> rotate_amount)|(operand << (64 - rotate_amount));
}

int parseBinaryFunction(const char* operand_symbol){
    matchToken(LEFT_PAREN);
    int operand1 = parseExpression();
    matchToken(SEPARATOR);
    int operand2 = parseExpression();
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
    // only option left is rr
    return rrFunction(operand1, operand2);

}

int parseUnaryFunction(){ // not function
    matchToken(LEFT_PAREN);

    int res = parseExpression(); 
    res = res ^ -1;
    matchToken(RIGHT_PAREN);
    return res;
}
int parseFactor(){ 
    token t = current_token;
    if(t.type == INTEGER){
        matchToken(INTEGER);
        return atoi(t.symbol);
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
        if(strncmp(t.symbol,"*", 1) == 0){
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
    while(token_index < token_count && current_token.type == OPERATOR_ADDITIVE){
        token t = current_token;
        matchToken(OPERATOR_ADDITIVE);
        if(strncmp(t.symbol,"+", 1) == 0){
            result += parseTerm();
        }
        else{
            result -= parseTerm();
        }
    }
    return result;
}
variable* parseVariable(){
    token t = current_token;
    matchToken(IDENTIFIER);
    variable *var = find(t.symbol);
    if(var == NULL){
        return insert(t.symbol);
    }
    else{
        return var;
    }
}
void parseAssignment(){
    variable* var = parseVariable();
    matchToken(ASSIGNMENT);
    var->value = parseExpression();
}

void parseStatement(){
    if(token_array[1].type == ASSIGNMENT){
        parseAssignment(); // assigns the rhs expr to lhs variable
    }
    else{
        printf("%d\n",parseExpression());
    }
    // TODO: how do i even handle the comments lol yasin kocum sende
}
