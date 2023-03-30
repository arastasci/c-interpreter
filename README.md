# cmpe230p1

## BNF

```
program      ::= { statement }
statement    ::= expression | assignment
expression   ::= term { add_op term }
term         ::= factor { mul_op factor }
factor       ::= identifier | number | unary_op factor | binary_op ( expression ) | ( expression )
assignment   ::= identifier '=' expression
binary_op    ::= 'xor' | 'ls' | 'rs' | 'lr' | 'rr'
unary_op     ::= 'not'
add_op       ::= '+' | '-'
mul_op       ::= '*' | '/'
identifier   ::= letter { letter | digit }
number       ::= digit { digit }

```

DOCUMENTATION

Tokenizing 

We started the project by creating a BNF grammar for the language. As we were creating 
the BNF we decided to implement this project as a recursively descending interpreter. 
Then we determined our token types according to the BNF hierarchy to efficiently implement
our recursively descending interpreter and to create a tokenizer for the language. We created a 
token structure that contained the token type and the token value. Then we started to create the
tokenizer. We declared the functions in 'token.h' needed to determine the token type. Then we 
implemented the functions in 'token.c' and set the constraints to correctly tokenize variables, 
integers, and operators. We also defined an error function which helped us find errors efficiently 
and without repetition. 

Parsing/Interpreting

We then created a parser structure considering the BNF hierarchy. We defined functions that call 
each other recursively to parse the tokens. Our hierarchy is as follows:
parseStatement: parses statements as an assignment or a (bitwise or expression)
parseAssignment: parses an assignment as an identifier and a (bitwise or expression)
parseBitwiseOrExpression: parses a bitwise or expression as a (bitwise and expression) and a (bitwise or expression) if there is a bitwise or operator
parseBitwiseAndExpression: parses a bitwise and expression as an expression and a (bitwise and expression) if there is a bitwise and operator
parseExpression: parses an expression as a term and an expression if there is an additive operator
parseTerm: parses a term as a factor and a term if there is a multiplicative operator
parseFactor: parses a factor as an identifier, an integer, a unary function, a binary function or a (bitwise or expression) in parentheses
parseVariable: parses an identifier, checks if the variable is in the hashmap and inserts it returns 0 or returns the current value
parseUnaryFunction: parses a (bitwise or expression) in parentheses and takes its complement
parseBinaryFunction: parses two (bitwise or expression)s in parentheses with a separator and applies a binary function () to it

Hashing

Error Handling



===============================================================================================================
