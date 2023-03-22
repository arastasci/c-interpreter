#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "token.c"

typedef struct s_parse_node {
    token_type op;
    int value;
    struct s_parse_node* left;
    struct s_parse_node* right;
} parse_node;

parse_node* parse_stmnt(token* tokens, int* pos) {
    parse_node* node = parse_term(tokens, pos);
    while (tokens[*pos].type == OPERATOR && (tokens[*pos].symbol[0] == '+' || tokens[*pos].symbol[0] == '-')) {
        token_type op = tokens[*pos].type;
        (*pos)++;
        parse_node* right = parse_term(tokens, pos);
        node = create_parse_node(op, node, right);
    }
    return node;
}
int parse_stmnt(){}



}