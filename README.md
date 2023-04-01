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

## DOCUMENTATION

### Introduction

This project aims to make an interpreter for an advanced calculator that can perform various operations. The program is capable of parsing complex mathematical expressions and assigning to and keeping track of arbitrarily named variables. The program follows the basic outline of an interpreter, the given input is put into lexical analysis, which outputs an array of tokens, which is then recursively parsed and evaluated.
This documentation hopes to be both a user guideline and a technical explanation of this interpreter.
It might be beneficial for the reader to know the meanings of the following terms in order to make full use of the documentation:

-   Lexical analysis is the process of converting a sequence of characters into a series of tokens.
-   Lexer, also called tokenizer is a program that performs lexical analysis.
-   Parser is a program that parses the provided series of tokens according to a specific syntax.

### Program Interface

The program is written in C and that requires the user who has the source code to first compile the program. For that there is a Makefile ready for use in the folder, so opening a new terminal in the root directory and running `make` will suffice. Compilation outputs the executable file `advCalc.exe` which can be run by the command `./advCalc.exe` and that starts the program. In order to stop the program, you can either `Ctrl+C` or `Ctrl+D` your way out.

### Program Execution

### Tokenizing

We started the project by creating a BNF grammar for the language. As we were creating
the BNF we decided to implement this project as a recursively descending interpreter.
Then we determined our token types according to the BNF hierarchy to efficiently implement
our recursively descending interpreter and to create a tokenizer for the language. We created a
token structure that contained the token type and the token value. Then we started to create the
tokenizer. We declared the functions in 'token.h' needed to determine the token type. Then we
implemented the functions in 'token.c' and set the constraints to correctly tokenize variables,
integers, and operators. We also defined an error function which helped us find errors efficiently
and without repetition.

### Parsing/Interpreting

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

### Hashing

Since this project is an interpreter, we needed to store the variables and their values.
We decided to use a hashmap to store the variables and their values.
We created a hashmap structure that contained the key and the value. We defined a function to initialize and allocate
memory for the hashmap. We also defined a function to free the memory of the hashmap.
Our hash function is a simple hash function that implements the djb2 algorithm. We defined the insert
function to get the hash value find out if it is empty or not. If it is empty, we insert the key and the value.
Else we do linear probing and get a proper index to insert the key and the value. We defined a find function to
get the value of the mentioned variable. If the variable is not in the hashmap, it returns 0.
We created a function that takes a key and a value and inserts it into the hashmap. We also created a function that takes a key and returns the value of the key. If the key is not in the hashmap, it returns 0.

### Error Handling

We defined the matchToken function to check if the current token is the expected token. If it is not, it returns an error.
This works because the expected token is the only choice for the grammar to according to the BNF and the recursive hierarchy.
We also defined a raiseTokenError function to raise error if the token is not one of the expected types in parseFactor.
This way also ensured our hierarchy worked properly.

===============================================================================================================
