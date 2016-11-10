#include <string>

enum TokenType {
    CONST, LET, PURE,
    IDENTIFIER,
    NUMBER,
    TRUE, FALSE,
    MAIN,
    OPERATOR, PARENTESIS, BRACES, BRACKETS
};

struct Token {
    TokenType type;
    std::string value;
    int lineNumber;
    int columnNumber;
};

