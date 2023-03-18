#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 256

typedef enum {
    TOK_OP_PLUS,  // '+'
    TOK_OP_MINUS, // '-'
    TOK_OP_MUL,   // '*'
    TOK_OP_AND,   // '&'
    TOK_OP_OR,    // '|'
    
    TOK_STROP_XOR,   // 'xor'
    TOK_STROP_LS,    // 'ls'
    TOK_STROP_RS,    // 'rs'
    TOK_STROP_LR,    // 'lr'
    TOK_STROP_RR,    // 'rr'
    TOK_STROP_NOT,   // 'not'

    TOK_COMMMENT, // 'comment'
    TOK_LPAREN,   // '('
    TOK_RPAREN,   // ')'

    TOK_ASSIGN,   // '='
    TOK_IDENTIFIER, // variable name
    TOK_CONSTANT, // constant value
    
    TOK_ERROR     // invalid token
} token_type;