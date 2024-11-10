#include "lexer.hpp"
#include <cctype>

Lexer::Lexer(const std::string& source) : source(source), index(0) {}

Token Lexer::next_token() {
    while (index < source.size() && std::isspace(source[index])) {
        index++;
    }

    if (index >= source.size()) {
        return {TokenType::End, ""};
    }

    char current = source[index];

    if (std::isdigit(current)) {
        std::string number;
        while (index < source.size() && std::isdigit(source[index])) {
            number += source[index++];
        }
        return {TokenType::Number, number};
    }

    if (current == '+') {
        index++;
        return {TokenType::Plus, "+"};
    }
    if (current == '-') {
        index++;
        return {TokenType::Minus, "-"};
    }
    if (current == '*') {
        index++;
        return {TokenType::Multiply, "*"};
    }
    if (current == '/') {
        index++;
        return {TokenType::Divide, "/"};
    }

    return {TokenType::Invalid, std::string(1, current)};
}