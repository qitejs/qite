#pragma once
#include <memory>
#include <vector>
#include <string>
#include "token.hpp"

struct Expression;
struct Statement;

struct BinaryExpr {
    std::shared_ptr<Expression> left;
    Token op;
    std::shared_ptr<Expression> right;
};

struct NumberExpr {
    double value;
};

struct IdentifierExpr {
    std::string name;
};

struct CallExpr {
    std::string callee;
    std::vector<std::shared_ptr<Expression>> arguments;
};

struct Expression {
    virtual ~Expression() = default;
};

struct FunctionDecl {
    std::string name;
    std::vector<std::string> parameters;
    std::vector<std::shared_ptr<Statement>> body;
};

struct IfStatement {
    std::shared_ptr<Expression> condition;
    std::vector<std::shared_ptr<Statement>> thenBranch;
    std::vector<std::shared_ptr<Statement>> elseBranch;
};

struct ExpressionStmt {
    std::shared_ptr<Expression> expression;
};

struct Statement {
    virtual ~Statement() = default;
};
