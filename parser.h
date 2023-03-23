#ifndef PARSE_H
#define PARSE_H
#include "token.h"
#include "hash.h"
void parseStatement();
int parseExpression();
int parseTerm();
int parseFactor();


#endif
