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
        std::string literal;
        Literal(const std::string& literal);
    };

    struct Expr::Unary{
        Token op;
        ExprVariant right;
        Unary(Token op, ExprVariant right);
    };

    ExprVariant createBinaryEV(ExprVariant left, Token op, ExprVariant right);
    ExprVariant createGroupingEV(ExprVariant expression);
    ExprVariant createLiteralEV(const std::string& literal);
    ExprVariant createUnaryEV(Token op, ExprVariant right);
}