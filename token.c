#include "token.h"
static int id_counter = 0;

token token_array[256];
int token_count;
int get_token(char* input, token* t){

    t->id = id_counter++;

    int i = 0;
    int j = 0;

    char* symbol = malloc(MAX_TOKEN_LENGTH);

    while (isspace(input[i])) i++; // skip whitespaces

    if (input[i] == '\0' || input[i] == '\n') {
        t->type = ERROR;
        i++;
    }

    else if (input[i] == '%') {
        t->type = COMMENT;
        i++;
    }

    #pragma region operators

    else if (input[i] == '+') {
        t->type = OPERATOR;
        t->symbol = "+";
        i++;
    }

    else if (input[i] == '-') {
        t->type = OPERATOR;
        t->symbol = "-";
        i++;
    }
    else if (input[i] == '*') {
        t->type = OPERATOR;
        t->symbol = "*";
        i++;
    }
    else if (input[i] == '/') {
        t->type = OPERATOR;
        t->symbol = "/";
        i++;
    }

    #pragma endregion

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
    else if (isdigit(input[i])) {
        t->type = INTEGER;
        while (isdigit(input[i])) {
            symbol[j] = input[i];
            i++;
            j++;
        }
        symbol[j] = '\0';
        t->symbol = symbol;
    }
    else if (isalpha(input[i])) {
        t->type = IDENTIFIER;
        while (isalpha(input[i])) {
            symbol[j] = input[i];
            i++;
            j++;
        }
        symbol[j] = '\0';
        t->symbol = symbol;
    }
    t->type = ERROR;
    token_array[t->id] = *t;
    return i;
}

void tokenize(char* input){
    
    int i = 0;
    int cur_token_count = 0;
    while (input[i] != '\0' && input[i] != '\n') {
        token t;
        int j = get_token(&input[i], &t);
        cur_token_count++;
        i+= j;
    }
    token_count = cur_token_count;

}

void printTokens(){
    for(int i = 0; i < token_count; i++){
        printf("symbol: %s, ",
         token_array[i].symbol);
    }
}