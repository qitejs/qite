#pragma once
#include <unordered_map>
#include <any>
#include "ast.hpp"

class Environment {
public:
    void define(const std::string& name, std::any value);
    std::any get(const std::string& name);
    void assign(const std::string& name, std::any value);

private:
    std::unordered_map<std::string, std::any> values;
};

class Interpreter {
public:
    void interpret(const std::vector<std::shared_ptr<Statement>>& statements);
    std::any evaluate(std::shared_ptr<Expression> expr);
    void executeBlock(const std::vector<std::shared_ptr<Statement>>& statements);

private:
    Environment environment;

    void execute(std::shared_ptr<Statement> stmt);
    std::any visitBinaryExpr(const BinaryExpr& expr);
    std::any visitNumberExpr(const NumberExpr& expr);
    std::any visitIdentifierExpr(const IdentifierExpr& expr);
    std::any visitCallExpr(const CallExpr& expr);
};
