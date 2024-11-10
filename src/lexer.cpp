#include "lexer.hpp"
#include <cctype>

Lexer::Lexer(std::string source) : source(std::move(source)) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        skipWhitespace();
        if (isAtEnd()) break;

        char c = peek();
        if (isDigit(c)) {
            tokens.push_back(number());
        } else if (isAlpha(c)) {
            tokens.push_back(identifier());
        } else {
            switch (c) {
                case '+':
                case '-':
                case '*':
                case '/':
                    tokens.push_back(Token(TokenType::OPERATOR, std::string(1, advance()), line, column));
                    break;
                case '(':
                case ')':
                case '{':
                case '}':
                case ';':
                case ',':
                    tokens.push_back(Token(TokenType::PUNCTUATION, std::string(1, advance()), line, column));
                    break;
                default:
                    // Handle error
                    advance();
                    break;
            }
        }
    }

    tokens.push_back(Token(TokenType::EOF_TOKEN, "", line, column));
    return tokens;
}

Token Lexer::number() {
    std::string num;
    while (isDigit(peek())) {
        num += advance();
    }

    if (peek() == '.' && isDigit(source[position + 1])) {
        num += advance();
        while (isDigit(peek())) {
            num += advance();
        }
    }

    return Token(TokenType::NUMBER, num, line, column);
}

Token Lexer::identifier() {
    std::string identifier;
    while (isAlphaNumeric(peek())) {
        identifier += advance();
    }

    // Check if it's a keyword
    static const std::vector<std::string> keywords = {
        "function", "if", "else", "return", "console"
    };

    for (const auto& keyword : keywords) {
        if (identifier == keyword) {
            return Token(TokenType::KEYWORD, identifier, line, column);
        }
    }

    return Token(TokenType::IDENTIFIER, identifier, line, column);
}