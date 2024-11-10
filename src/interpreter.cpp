#include "interpreter.hpp"
#include <iostream>
#include <vector>
#include <any>
#include <stdexcept>
#include <string>
#include <memory>
#include <unordered_map>

// Interpreter class implementation
void Interpreter::interpret(const std::vector<std::shared_ptr<Statement>>& statements) {
    try {
        for (const auto& statement : statements) {
            execute(statement);
        }
    } catch (const std::runtime_error& error) {
        std::cerr << "Runtime Error: " << error.what() << std::endl;
    }
}

std::any Interpreter::evaluate(std::shared_ptr<Expression> expr) {
    if (auto* binary = dynamic_cast<BinaryExpr*>(expr.get())) {
        return visitBinaryExpr(*binary);
    } else if (auto* number = dynamic_cast<NumberExpr*>(expr.get())) {
        return visitNumberExpr(*number);
    } else if (auto* identifier = dynamic_cast<IdentifierExpr*>(expr.get())) {
        return visitIdentifierExpr(*identifier);
    } else if (auto* call = dynamic_cast<CallExpr*>(expr.get())) {
        return visitCallExpr(*call);
    }
    throw std::runtime_error("Unknown expression type");
}

std::any Interpreter::visitBinaryExpr(const BinaryExpr& expr) {
    std::any left = evaluate(expr.left);
    std::any right = evaluate(expr.right);

    if (expr.op.type == TokenType::OPERATOR) {
        double leftNum = std::any_cast<double>(left);
        double rightNum = std::any_cast<double>(right);

        switch (expr.op.value[0]) {
            case '+': return leftNum + rightNum;
            case '-': return leftNum - rightNum;
            case '*': return leftNum * rightNum;
            case '/':
                if (rightNum == 0) throw std::runtime_error("Division by zero");
                return leftNum / rightNum;
        }
    }

    throw std::runtime_error("Invalid operator");
}

// Environment class implementation
void Environment::define(const std::string& name, std::any value) {
    values[name] = std::move(value);
}

std::any Environment::get(const std::string& name) {
    auto it = values.find(name);
    if (it != values.end()) {
        return it->second;
    }
    throw std::runtime_error("Undefined variable '" + name + "'");
}

// Console implementation
void setupConsole(Environment& env) {
    env.define("console.log", [](const std::vector<std::any>& args) {
        for (const auto& arg : args) {
            if (arg.type() == typeid(double)) {
                std::cout << std::any_cast<double>(arg) << " ";
            } else if (arg.type() == typeid(std::string)) {
                std::cout << std::any_cast<std::string>(arg) << " ";
            } else {
                std::cout << "Unsupported type ";
            }
        }
        std::cout << std::endl;
    });

    env.define("console.warn", [](const std::vector<std::any>& args) {
        std::cout << "Warning: ";
        for (const auto& arg : args) {
            if (arg.type() == typeid(double)) {
                std::cout << std::any_cast<double>(arg) << " ";
            } else if (arg.type() == typeid(std::string)) {
                std::cout << std::any_cast<std::string>(arg) << " ";
            } else {
                std::cout << "Unsupported type ";
            }
        }
        std::cout << std::endl;
    });

    env.define("console.error", [](const std::vector<std::any>& args) {
        std::cerr << "Error: ";
        for (const auto& arg : args) {
            if (arg.type() == typeid(double)) {
                std::cerr << std::any_cast<double>(arg) << " ";
            } else if (arg.type() == typeid(std::string)) {
                std::cerr << std::any_cast<std::string>(arg) << " ";
            } else {
                std::cerr << "Unsupported type ";
            }
        }
        std::cerr << std::endl;
    });
}