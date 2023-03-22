#ifndef TOKEN 
#define TOKEN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 256

typedef enum e_token_type {
    OPERATOR,   // +, -, *, /
    LEFT_PAREN, // (
    RIGHT_PAREN, // )
    STR_OPERATOR_UNARY, //  'not'
    STR_OPERATOR_BINARY, // 'ls', 'rs', 'lr', 'rr', 'xor'
    IDENTIFIER, // a, b, c, ...
    ASSIGNMENT, // =
    INTEGER,   // 1, 2, 3, ...
    COMMENT,  // % ...
    ERROR     // invalid token
} token_type;

typedef struct s_token
{
    int id;
    token_type type;
    char *symbol;
} token;
extern token token_array[MAX_TOKEN_LENGTH];
extern int token_count;

void tokenize(char* input);
int get_token(char* input, token* t);
void printTokens();

#endif