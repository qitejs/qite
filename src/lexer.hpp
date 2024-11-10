#pragma once
#include <string>
#include <vector>
#include "token.hpp"

class Lexer {
public:
    explicit Lexer(std::string source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t position = 0;
    int line = 1;
    int column = 1;

    char peek();
    char advance();
    bool isAtEnd();
    Token number();
    Token identifier();
    void skipWhitespace();
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
};