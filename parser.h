#ifndef PARSE_H
#define PARSE_H
#include "token.h"
#include "hash.h"
typedef struct s_response{
    bool error;
    int value;
} response;
void parseStatement();
response parseExpression();
response parseTerm();
response parseFactor();
response parseBitwiseAndExpression();
response parseBitwiseOrExpression();


#endif
