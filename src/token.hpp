#pragma once
#include <string>

enum class TokenType {
    NUMBER,
    STRING,
    IDENTIFIER,
    KEYWORD,
    OPERATOR,
    PUNCTUATION,
    EOF_TOKEN
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;

    Token(TokenType t, std::string v, int l, int c)
        : type(t), value(std::move(v)), line(l), column(c) {}
};