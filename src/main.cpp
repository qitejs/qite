#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
#include "interpreter.hpp"

int main() {
    std::string input;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, input);

    Lexer lexer(input);
    Parser parser(lexer);
    ASTNode* root = parser.parse();

    Interpreter interpreter;
    double result = interpreter.interpret(root);
    std::cout << "Result: " << result << std::endl;

    delete root; // Clean up the AST
    return 0;
}