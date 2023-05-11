<br> </br>
<br> </br>

<br> </br>

## <p style="text-align: center;"> Systems Programming CMPE230</p>

<br> </br>

## <p style="text-align: center;"> AdvCalc</p>

## <p style="text-align: center;"> Project Documentation</p>

<br> </br>
<br> </br>

### <p style="text-align: center;"> Aras Taşçı 2020400162</p>

### <p style="text-align: center;">Osman Yasin Baştuğ 2021400021</p>

<br> </br>
<br> </br>
<br> </br>

### <p style="text-align: center;">Submitted to: Can Özturan</p>

<br> </br>

## 1 Introduction

This project aims to make an interpreter for an advanced calculator that can perform various operations. The program is capable of parsing complex mathematical expressions and assigning to and keeping track of arbitrarily named variables. The program follows the basic outline of an interpreter, the given input is put into lexical analysis, which outputs an array of tokens, which is then recursively parsed and evaluated.
This documentation hopes to be both a user guideline and a technical explanation of this interpreter.
It might be beneficial for the reader to know the meanings of the following terms in order to make full use of the documentation:

-   Lexical analysis is the process of converting a sequence of characters into a series of tokens.
-   Lexer, also called tokenizer is a program that performs lexical analysis.
-   Parser is a program that parses the provided series of tokens according to a specific syntax.

## 2 Program Interface

The program is written in C and that requires the user who has the source code to first compile the program. For that there is a Makefile ready for use in the folder, so opening a new terminal in the root directory and running `make` will suffice. Compilation outputs the executable file `advcalc` which can be run by the command `./advcalc` and that starts the program. In order to stop the program, you can either `Ctrl+C` or `Ctrl+D` your way out. To clear the compiled program, you can run `make clean`

## 3 Program Execution

This program aims to be a basic calculator which can interpret basic mathematical operations like addition, subtraction, multiplication, bitwise operations like or and and, function-like binary operations like left-right shift, left-right rotate, xor and a function unary operation, not. The examples using these operations are given in the `Examples` section.
User is prompted with `> ` to enter a statement. Statements can be either an assignment operation, or an expression. If it is solely an expression, the program interprets and outputs the value of it.

### 3.1 Validity of statements

The assignment operation's right hand side can be any valid expression of the user's like while the LHS ought to be an identifier. If there is an error in this syntax, the statement is not invalidated and `"Error!"` is printed.
As to the validity of the expressions, the precedence of the operations determine the expression's next expected token. If the token is not of the expected type, the expression becomes invalid and `"Error!"` is printed on the screen. Parantheses must abide by the stacking rule. For the precedence of the operations, you can take [C's operation precedence table](https://en.cppreference.com/w/c/language/operator_precedence) as reference:

## 4 Implementation details

### 4.1 Tokenizing

We started the project by creating a BNF grammar for the language. As we were creating
the BNF we decided to implement this project as a recursively descending interpreter.
Then we determined our token types according to the BNF hierarchy to efficiently implement
our recursively descending interpreter and to create a tokenizer for the language. We created a
token structure that contained the token type and the token value. Then we started to create the
tokenizer. We declared the functions in `tokenizer.h` needed to determine the token type. Then we
implemented the functions in `tokenizer.c` and set the constraints to correctly tokenize variables,
integers, and operators. We also defined an error function which helped us find errors efficiently
and without repetition.

### 4.2 Parsing/Interpreting

We then created a parser structure considering the BNF hierarchy.
We defined functions that call
each other recursively to parse the tokens. Our hierarchy is as follows:

`parseStatement`: parses statements as an assignment or a `bitwise or expression`

`parseAssignment`: parses an assignment as an identifier and a `bitwise or expression`

`parseBitwiseOrExpression`: iteratively parses the current `bitwise or expression`, splitting it into parts of `bitwise and expression`s so long as there is a `bitwise or operator`.

`parseBitwiseAndExpression`: iteratively parses the current `bitwise and expression`, splitting it into parts of `expression`s so long as there is a `bitwise and operator`.

`parseExpression`: iteratively parses the current `expression`, splitting it into parts of `term`s so long as there is an `additive operator`.

`parseTerm`: iteratively parses the current `term`, splitting it into parts of `factor`s so long as there is a `multiplicative operator`.

`parseFactor`: parses a factor as an identifier, an integer, a unary function, a binary function or a `bitwise or expression` in parentheses

`parseVariable`: parses an identifier, checks if the variable is in the hashmap and inserts it returns 0 or returns the current value

`parseUnaryFunction`: parses a `bitwise or expression` in parentheses and takes its complement

`parseBinaryFunction`: parses two `bitwise or expression`s in parentheses with a separator and applies a binary function () to it

### 4.3 Hashing

Since this project is an interpreter, we needed to store the variables and their values.
We decided to use a hashmap to store the variables and their values.
We created a hashmap structure that contained the key and the value. We defined a function to initialize and allocate
memory for the hashmap. We also defined a function to free the memory of the hashmap.
Our hash function is a simple hash function that implements the djb2 algorithm. We defined the insert
function to get the hash value find out if it is empty or not. If it is empty, we insert the key and the value.
Else we do linear probing and get a proper index to insert the key and the value. We defined a find function to
get the value of the mentioned variable. If the variable is not in the hashmap, it returns 0.
We created a function that takes a key and a value and inserts it into the hashmap. We also created a function that takes a key and returns the value of the key. If the key is not in the hashmap, it returns 0.

### 4.4 Error Handling

We defined the `matchToken` function to check if the current token is the expected token. If it is not, it returns an error.
This works because the expected token is the only choice for the grammar according to the BNF and the recursive hierarchy.
We also defined a `raiseTokenError` function to raise error if the token is not one of the expected types in `parseFactor`.
This way also ensured our hierarchy worked properly.

## 5 Examples

Below are some examples regarding the usage of the program.

You can assign variables values like this:

```
> a = 5
> a
5
> a + 31 * 5
160
> a = a + 31 * 5
> a
160
```

Function-like binary and unary operations are also supported:

```
> ls(a,3)
1280
> rs( a , 3)
20
> lr(a,2) % you also have rr and xor
640
> not(39)
-40
```

```
> a = 5 % you may also comment a line like this!
> a a = 5 % this is an invalid statement
Error!
> a
5
> a + 5 - 2 % https://youtu.be/Tt7bzxurJ1I
8
```

## 6 Problems Encountered and Conclusion

In the beginning of the project, the biggest problem was designing the hierarchy and main logic of the parser. So we first
implemented the tokenizer. Then we started to think about the logic of the parser. We first wrote the BNF
according to the grammar, and then we worked on some ideas like creating an AST or using a recursive hierarchy. After a few
tries on AST method, we decided not to use an AST and directly interpret the expressions while we iterated through the functions
recursively. We had different opinions on implementing the hashmap like storing the values in one array and the keys in another but
then we decided to implement a variable struct and create the hashmap as a variable array. We also tried some different hash algorithms
but finally decided on djb2. The biggest problem was handling the errors. We had issues like printing multiple error messages or
not printing the error messages at all. We finally figured out where we had to put the token checks for error after carefully
analyzing the hierarchy, and we defined an error flag to prevent multiple error messages. After all we've been through, we are better coders if not better friends.
<br> </br>
<br> </br>
<br> </br>
<br> </br>
<br> </br>
<br> </br>
<br> </br>

## 7 Appendix

### BNF

Below is the BNF we created for the interpreter.

```
<Statement> ::= <Assignment> | <BitwiseOrExpression>
<Assignment> ::= <Variable> "=" <BitwiseOrExpression>
<BitwiseOrExpression> ::= <BitwiseAndExpression> ("|" <BitwiseAndExpression>)*
<BitwiseAndExpression> ::= <Expression> ("&" <Expression>)*
<Expression> ::= <Term> (("+"|"-") <Term>)*
<Term> ::= <Factor> (("*") <Factor>)
<Factor> ::= <Variable> | <integer> | <UnaryFunction> | <BinaryFunction> | "(" <BitwiseOrExpression> ")"
<Variable> ::= <identifier>
<UnaryFunction> ::= "not" "(" <BitwiseOrExpression> ")"
<BinaryFunction> ::= <BinaryFunctionOperator>  "(" <BitwiseOrExpression> "," <BitwiseOrExpression> ")"
<BinaryFunctionOperator> ::= "xor" | "lr" | "rr" | "ls" | "rs"
<integer> ::= <digit>+
<identifier> ::= <letter> (<letter>)*
```
