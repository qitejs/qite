#include "parser.hpp"
#include <stdexcept>

Parser::Parser(Lexer& lexer) : lexer(lexer), current_token(lexer.next_token()) {}

ASTNode* Parser::parse() {
    return expression();
}

void Parser::eat(TokenType type) {
    if (current_token.type == type) {
        current_token = lexer.next_token();
    } else {
        throw std::runtime_error("Unexpected token");
    }
}

ASTNode* Parser::expression() {
    ASTNode* node = term();
    while (current_token.type == TokenType::Plus || current_token.type == TokenType::Minus) {
        Token op = current_token;
        eat(op.type);
        node = new ASTNode{op.type, op.value, node, term()};
    }
    return node;
}

ASTNode* Parser::term() {
    ASTNode* node = factor();
    while (current_token.type == TokenType::Multiply || current_token.type == TokenType::Divide) {
        Token op = current_token;
        eat(op.type);
        node = new ASTNode{op.type, op.value, node, factor()};
    }
    return node;
}

ASTNode* Parser::factor() {
    if (current_token.type == TokenType::Number) {
        ASTNode* node = new ASTNode{TokenType::Number, current_token.value};
        eat(TokenType::Number);
        return node;
    }
    throw std::runtime_error("Expected a number");
}