#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "token.c"

typedef struct s_parse_node {
    token token;
    struct s_parse_node* left;
    struct s_parse_node* right;
} parse_node;

parse_node* parse_expr(token* tokens, int* pos) {
    if (tokens[*pos].type == INTEGER) {
        parse_node* node = s_parse_node(tokens[*pos], NULL, NULL);
        *pos++;
        return node;
    }
    else if (tokens[*pos].type == IDENTIFIER) {
        parse_node* node = s_parse_node(tokens[*pos], NULL, NULL);
        *pos++;
        return node;
    }
    else if (tokens[*pos].type == LEFT_PAREN) {
        *pos++;
        parse_node* node = parse_expr(tokens, pos);
        if (tokens[*pos].type == RIGHT_PAREN) {
            *pos++;
            return node;
        }
        else {
            printf("Error: Expected ')'.\n");
            return NULL;
        }
    }
    else if (tokens[*pos].type == STR_OPERATOR_UNARY) {
        *pos++;
        parse_node* node = s_parse_node(tokens[*pos], NULL, NULL);
        *pos++;
        return node;
    }
    else if (tokens[*pos].type == STR_OPERATOR_BINARY) {
        *pos++;
        parse_node* node = s_parse_node(tokens[*pos], NULL, NULL);
        *pos++;
        return node;
    }
    else {
        printf("Error: Expected expression.\n");
        return NULL;
    }
    parse_node* node = s_parse_node(tokens[*pos], NULL, NULL);

}
int parse_stmnt(){}



}