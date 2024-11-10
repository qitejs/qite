#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>

enum class TokenType {
    Number,
    Plus,
    Minus,
    Multiply,
    Divide,
    End,
    Invalid
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    explicit Lexer(const std::string& source);
    Token next_token();

private:
    std::string source;
    size_t index;
};

#endif // LEXER_HPP