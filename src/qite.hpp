#pragma once
#include <string>
#include "interpreter.hpp"

class Qite {
public:
    void execute(const std::string& source);
    void repl();

private:
    Interpreter interpreter;
};