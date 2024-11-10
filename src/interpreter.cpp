#include "interpreter.hpp"
#include <stdexcept>

double Interpreter::interpret(ASTNode* node) {
    if (!node) return 0;

    if (node->type == TokenType ::Number) {
        return std::stod(node->value);
    }

    double left = interpret(node->left);
    double right = interpret(node->right);

    switch (node->type) {
        case TokenType::Plus:
            return left + right;
        case TokenType::Minus:
            return left - right;
        case TokenType::Multiply:
            return left * right;
        case TokenType::Divide:
            if (right == 0) throw std::runtime_error("Division by zero");
            return left / right;
        default:
            throw std::runtime_error("Invalid AST node type");
    }
}