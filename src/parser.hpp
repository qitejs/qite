#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"

struct ASTNode {
    TokenType type;
    std::string value;
    ASTNode* left = nullptr;
    ASTNode* right = nullptr;

    ~ASTNode() {
        delete left;
        delete right;
    }
};

class Parser {
public:
    explicit Parser(Lexer& lexer);
    ASTNode* parse();

private:
    Lexer& lexer;
    Token current_token;

    void eat(TokenType type);
    ASTNode* expression();
    ASTNode* term();
    ASTNode* factor();
};

#endif // PARSER_HPP