#pragma once
#include <Lexer.hpp>
#include <variant>
#include <iostream>
#include <memory>

namespace Ne{
    namespace Expr{
        struct Binary;
        struct Grouping;
        struct Literal;
        struct Unary;
        struct Variable;
    }
    
    using BinaryExpr = std::unique_ptr<Expr::Binary>; 
    using GroupingExpr = std::unique_ptr<Expr::Grouping>; 
    using LiteralExpr = std::unique_ptr<Expr::Literal>; 
    using UnaryExpr = std::unique_ptr<Expr::Unary>; 
    using VariableExpr = std::unique_ptr<Expr::Variable>; 

    using ExprVariant = std::variant<BinaryExpr, GroupingExpr, LiteralExpr, UnaryExpr, VariableExpr>;

    using LiteralObject = std::variant<std::string, int, double, bool>;

    struct Expr::Binary{
        ExprVariant left;
        Token op;
        ExprVariant right;
        Binary(ExprVariant left, Token op, ExprVariant right);
    };

    struct Expr::Grouping{
        ExprVariant expression;
        Grouping(ExprVariant expression);
    };

    struct Expr::Literal{
        LiteralObject literal;
        Literal(const LiteralObject& literal);
        TokenType getType();
    };

    struct Expr::Unary{
        Token op;
        ExprVariant right;
        Unary(Token op, ExprVariant right);
    };

    struct Expr::Variable{
        Token name;
        Variable(Token name);
    };

    ExprVariant createBinaryEV(ExprVariant left, Token op, ExprVariant right);
    ExprVariant createGroupingEV(ExprVariant expression);
    ExprVariant createLiteralEV(const LiteralObject& literal);
    ExprVariant createUnaryEV(Token op, ExprVariant right);
    ExprVariant createVariableEV(Token name);

    // Statements
    namespace Stmt{
        struct Expr;
        struct Print;
        struct Var;
    }

    using ExprStmt = std::unique_ptr<Stmt::Expr>;
    using PrintStmt = std::unique_ptr<Stmt::Print>;
    using VarStmt = std::unique_ptr<Stmt::Var>;

    using StmtVariant = std::variant<ExprStmt, PrintStmt, VarStmt>;

    struct Stmt::Expr{
        ExprVariant expression;
        Expr(ExprVariant expr);
    };

    struct Stmt::Print{
        ExprVariant expression;
        Print(ExprVariant expr);
    };

     struct Stmt::Var{
        Token name;
        TokenType type;
        ExprVariant initializer;
        Var(Token name, TokenType type, ExprVariant initializer);
    };

    StmtVariant createExprSV(ExprVariant expr);
    StmtVariant createPrintSV(ExprVariant expr);
    StmtVariant createVarSV(Token name, TokenType type, ExprVariant initializer);

}