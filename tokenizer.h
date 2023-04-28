#ifndef TOKEN 
#define TOKEN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_TOKEN_LENGTH 256
#define MAX_TOKEN_COUNT 128
typedef enum e_token_type {
    OPERATOR_ADDITIVE,   // +, -
    OPERATOR_MULTIPLICATIVE,  // *
    OPERATOR_BITWISE, // &, |
    LEFT_PAREN, // (
    RIGHT_PAREN, // )
    STR_OPERATOR_UNARY, //  'not'
    STR_OPERATOR_BINARY, // 'ls', 'rs', 'lr', 'rr', 'xor'
    IDENTIFIER, // a, b, c, ...
    ASSIGNMENT, // =
    INTEGER,   // 1, 2, 3, ...
    COMMENT,  // % ...
    SEPARATOR, // `,`
    ERROR     // invalid token
} token_type;

typedef struct s_token  // token struct
{
    int id;
    token_type type;
    char *symbol;
} token;
extern token* token_array;

token getNextToken();
void allocateArrayMemory();
void freeArrayMemory();
void matchToken(token_type tokenType);
extern bool has_error;
extern int token_count;
extern int token_index;
extern token current_token;
void raiseTokenError();
void tokenize(char* input);
int getToken(char* input, token* t, bool* exit_early);
void printTokens();

#endif