enum token_type{
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    DELIMITER,
    CONSTANT,
    STRING_LITERAL,
    COMMENT,
    PREPROCESSOR,
    UNKNOWN
};
struct token
{
    int id;
    int position;
    enum token_type type;
    char *symbol;
    
};
