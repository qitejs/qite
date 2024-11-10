#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "parser.hpp"

class Interpreter {
public:
    double interpret(ASTNode* node);
};

#endif // INTERPRETER_HPP