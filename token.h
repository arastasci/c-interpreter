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
    int position;
    token_type type;
    char *symbol;
} token;


struct s_token token_array[256];
void tokenize(char* input);
struct s_token get_token(char* input, token* t);
void printTokens();

#endif