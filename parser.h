#ifndef PARSE_H
#define PARSE_H
#include "tokenizer.h"
#include "hash.h"
#define int_64 long long int
void parseStatement();
int_64 parseExpression();
int_64 parseTerm();
int_64 parseFactor();
int_64 parseBitwiseOrExpression();
int_64 parseBitwiseAndExpression();

#endif
