#pragma once
#include <vector>
#include "token.hpp"
#include "ast.hpp"

class Parser {
public:
    explicit Parser(std::vector<Token> tokens);
    std::vector<std::shared_ptr<Statement>> parse();

private:
    std::vector<Token> tokens;
    size_t current = 0;

    std::shared_ptr<Statement> statement();
    std::shared_ptr<Statement> ifStatement();
    std::shared_ptr<Statement> functionDeclaration();
    std::shared_ptr<Expression> expression();
    std::shared_ptr<Expression> equality();
    std::shared_ptr<Expression> comparison();
    std::shared_ptr<Expression> term();
    std::shared_ptr<Expression> factor();
    std::shared_ptr<Expression> primary();

    Token peek();
    Token previous();
    Token advance();
    bool isAtEnd();
    bool match(TokenType type);
    bool check(TokenType type);
    Token consume(TokenType type, const std::string& message);
};