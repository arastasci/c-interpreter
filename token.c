#include "token.h"
static int id_counter = 0;



token get_token(char* input, token* t){
   
    t->id = id_counter++;

    int i = 0;
    int j = 0;

    char* symbol = malloc(MAX_TOKEN_LENGTH);

    while (isspace(input[i])) i++; // skip whitespaces

    #pragma region operators
    if (input[i] == '\0') {
        t->type = ERROR;
        return *t;
    }

    if (input[i] == '%') {
        t->type = COMMENT;
        return *t;
    }

    if (input[i] == '+') {
        t->type = OPERATOR;
        t->symbol = "+";
        return *t;
    }

    if (input[i] == '-') {
        t->type = OPERATOR;
        t->symbol = "-";
        return *t;
    }
    if (input[i] == '*') {
        t->type = OPERATOR;
        t->symbol = "*";
        return *t;
    }
    if (input[i] == '/') {
        t->type = OPERATOR;
        t->symbol = "/";
        return *t;
    }

    #pragma endregion

    if (input[i] == '(') {
        t->type = LEFT_PAREN;
        t->symbol = "(";
        return *t;
    }
    if (input[i] == ')') {
        t->type = RIGHT_PAREN;
        t->symbol = ")";
        return *t;
    }
    if (input[i] == '=') {
        t->type = ASSIGNMENT;
        t->symbol = "=";
        return *t;
    }
    if (isdigit(input[i])) {
        t->type = INTEGER;
        while (isdigit(input[i])) {
            symbol[j] = input[i];
            i++;
            j++;
        }
        t->symbol = symbol;
        return *t;
    }
    if (isalpha(input[i])) {
        t->type = IDENTIFIER;
        while (isalpha(input[i])) {
            symbol[j] = input[i];
            i++;
            j++;
        }
        t->symbol = symbol;
        return *t;
    }
    t->type = ERROR;
    return *t;


    
}

void tokenize(char* input){
    
    int i = 0;
    while (input[i] != '\0') {
        token t;
        t = get_token(&input[i], &t);
        token_array[i] = t;
        i++;
    }
}

void printTokens(){
    for(int i = 0; i < 256; i++){
        printf("id: %d, position: %d, type: %d, symbol: %s, ", 
        token_array[i].id, token_array[i].position, token_array[i].type, token_array[i].symbol);
        }
}