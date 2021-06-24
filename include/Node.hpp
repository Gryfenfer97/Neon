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
    }
    
    using BinaryExpr = std::unique_ptr<Expr::Binary>; 
    using GroupingExpr = std::unique_ptr<Expr::Grouping>; 
    using LiteralExpr = std::unique_ptr<Expr::Literal>; 
    using UnaryExpr = std::unique_ptr<Expr::Unary>; 

    using ExprVariant = std::variant<BinaryExpr, GroupingExpr, LiteralExpr, UnaryExpr>;

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
    };

    struct Expr::Unary{
        Token op;
        ExprVariant right;
        Unary(Token op, ExprVariant right);
    };

    ExprVariant createBinaryEV(ExprVariant left, Token op, ExprVariant right);
    ExprVariant createGroupingEV(ExprVariant expression);
    ExprVariant createLiteralEV(const LiteralObject& literal);
    ExprVariant createUnaryEV(Token op, ExprVariant right);

    // Statements
    namespace Stmt{
        struct Expr;
        struct Print;
    }

    using ExprStmt = std::unique_ptr<Stmt::Expr>;
    using PrintStmt = std::unique_ptr<Stmt::Print>;

    using StmtVariant = std::variant<ExprStmt, PrintStmt>;

    struct Stmt::Expr{
        ExprVariant expression;
        Expr(ExprVariant expr);
    };

    struct Stmt::Print{
        ExprVariant expression;
        Print(ExprVariant expr);
    };

    StmtVariant createExprSV(ExprVariant expr);
    StmtVariant createPrintSV(ExprVariant expr);

}