#include "qite.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>
#include <string>

void Qite::execute(const std::string& source) {
    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    auto statements = parser.parse();

    interpreter.interpret(statements);
}

void Qite::repl() {
    std::string line;
    std::cout << "Qite JavaScript Engine v0.1\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line) || line == "exit") {
            break;
        }

        try {
            execute(line);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}