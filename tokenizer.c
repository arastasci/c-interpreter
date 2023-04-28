#include "tokenizer.h"
static int id_counter = 0;

bool has_error;
token current_token;

token* token_array;
int token_count;
const char* binary_operator_funcs[] = {"xor", "ls", "rs", "lr", "rr", };    // binary operators
const char* unary_operator = "not"; // unary operator


int token_index = 0;
token getNextToken(){   // to iterate between the tokens
    return token_array[++token_index];
}

void matchToken(token_type tokenType){
    // if the token_type matches with the expected type, continue, else raise error
    if(token_index <=token_count && current_token.type == tokenType){
        current_token = getNextToken();
    }
    else {
        raiseTokenError();
    }
}


token_type determineTokenTypeOfAlpha(const char* symbol){
    for(int i = 0; i < 5; i++){
        if(strcmp(symbol,binary_operator_funcs[i]) == 0) {
            return STR_OPERATOR_BINARY;
        }
    }
    if(strcmp(symbol, unary_operator) == 0){
        return STR_OPERATOR_UNARY;
    }
    return IDENTIFIER;
}


int getToken(char* input, token* t, bool* exit_early){

    t->id = id_counter++;

    int i = 0;
    int j = 0;

    char* symbol = malloc(MAX_TOKEN_LENGTH);

    while (isspace(input[i])) i++; // skip whitespaces

    if (input[i] == '\0' || input[i] == '\n') { // if the input is empty, return
        t->type = ERROR;
        *exit_early = true;
        return 0;
        i++;
    }

    else if (input[i] == '%') {
        *exit_early = true;
        return 0;

    }

    #pragma region operators

    else if (input[i] == '+') {
        t->type = OPERATOR_ADDITIVE;
        t->symbol = "+";
        i++;
    }

    else if (input[i] == '-') {
        t->type = OPERATOR_ADDITIVE;
        t->symbol = "-";
        i++;
    }
    else if (input[i] == '*') {
        t->type = OPERATOR_MULTIPLICATIVE;
        t->symbol = "*";
        i++;
    }
    else if (input[i] == '&') {
        t->type = OPERATOR_BITWISE;
        t->symbol = "&";
        i++;
    }
    else if (input[i] == '|') {
        t->type = OPERATOR_BITWISE;
        t->symbol = "|";
        i++;
    }
    #pragma endregion
    else if (input[i] == ','){
        t->type = SEPARATOR;
        t->symbol = ",";
        i++;
    }
    else if (input[i] == '(') {
        t->type = LEFT_PAREN;
        t->symbol = "(";
        i++;
    }
    else if (input[i] == ')') {
        t->type = RIGHT_PAREN;
        t->symbol = ")";
        i++;
    }
    else if (input[i] == '=') {
        t->type = ASSIGNMENT;
        t->symbol = "=";
        i++;
    }
    else if (isdigit(input[i])) {   // if the input is a digit, determine if it is an integer iterating and get the value
        t->type = INTEGER;
        while (isdigit(input[i])) {
            symbol[j] = input[i];
            i++;
            j++;
        }
        symbol[j] = '\0';   // null terminate the string
        t->symbol = symbol;
    }
    else if (isalpha(input[i])) {   // if the input is a letter, determine if it is an identifier or a keyword
        while (isalpha(input[i])) {
            symbol[j] = input[i];
            i++;
            j++;

        }
        symbol[j] = '\0';

        t->symbol = symbol;
        t->type = determineTokenTypeOfAlpha(symbol);
    }
    else{
        raiseTokenError();
    }

    token_array[t->id] = *t;
    return i;
}

void tokenize(char* input){
    token_index = 0;
    id_counter = 0;
    int i = 0;
    int cur_token_count = 0;
    bool exit_early = false;
    while (input[i] != '\0' && input[i] != '\n') {
        token t;

        int j = getToken(&input[i], &t, &exit_early);   // get the token
        if(exit_early) break;   // if the input is empty, break
        if(has_error) return;   // if there is an error, return
        cur_token_count++;
        i+= j;
    }
    token_count = cur_token_count;
    current_token = token_array[0];
}
void allocateArrayMemory(){ // allocate memory for the token array
    token_array = malloc(128 * sizeof(token));
}
void freeArrayMemory(){ // free the memory of the token array
    memset(token_array, 0, 128 * sizeof(token));
}
void printTokens(){ // created for debugging

    for(int i = 0; i < token_count; i++){
        printf("type: %d, symbol: %s\n",
         token_array[i].type, token_array[i].symbol);
    }
   // printf("done");
}

void raiseTokenError(){
    has_error = true;
}