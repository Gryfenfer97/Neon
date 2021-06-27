#pragma once
#include <Lexer.hpp>
#include <variant>
#include <iostream>
#include <memory>
#include <optional>

namespace Ne{
    namespace Expr{
        struct Binary;
        struct Grouping;
        struct Literal;
        struct Unary;
        struct Variable;
        struct Assign;
        struct Logical;
    }
    
    using BinaryExpr = std::unique_ptr<Expr::Binary>; 
    using GroupingExpr = std::unique_ptr<Expr::Grouping>; 
    using LiteralExpr = std::unique_ptr<Expr::Literal>; 
    using UnaryExpr = std::unique_ptr<Expr::Unary>; 
    using VariableExpr = std::unique_ptr<Expr::Variable>;
    using AssignExpr = std::unique_ptr<Expr::Assign>; 
    using LogicalExpr = std::unique_ptr<Expr::Logical>;

    using ExprVariant = std::variant<BinaryExpr, GroupingExpr, LiteralExpr, UnaryExpr, VariableExpr, AssignExpr, LogicalExpr>;

    using LiteralObject = std::variant<std::string, int, double, bool, nullptr_t>;

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

    struct Expr::Assign{
        Token name;
        ExprVariant value;
        Assign(Token name, ExprVariant value);
    };

    struct Expr::Logical{
        ExprVariant left;
        Token op;
        ExprVariant right;
        Logical(ExprVariant left, Token op, ExprVariant right);
    };

    ExprVariant createBinaryEV(ExprVariant left, Token op, ExprVariant right);
    ExprVariant createGroupingEV(ExprVariant expression);
    ExprVariant createLiteralEV(const LiteralObject& literal);
    ExprVariant createUnaryEV(Token op, ExprVariant right);
    ExprVariant createVariableEV(Token name);
    ExprVariant createAssignEV(Token name, ExprVariant value);
    ExprVariant createLogicalEV(ExprVariant left, Token op, ExprVariant right);

    // Statements
    namespace Stmt{
        struct Expr;
        struct Print;
        struct Var;
        struct Block;
        struct If;
        struct While;
    }

    using ExprStmt = std::unique_ptr<Stmt::Expr>;
    using PrintStmt = std::unique_ptr<Stmt::Print>;
    using VarStmt = std::unique_ptr<Stmt::Var>;
    using BlockStmt = std::unique_ptr<Stmt::Block>;
    using IfStmt = std::unique_ptr<Stmt::If>;
    using WhileStmt = std::unique_ptr<Stmt::While>;

    using StmtVariant = std::variant<ExprStmt, PrintStmt, VarStmt, BlockStmt, IfStmt, WhileStmt>;

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

    struct Stmt::Block{
        std::vector<StmtVariant> statements;
        Block(std::vector<StmtVariant> statements);
    };

    struct Stmt::If{
        ExprVariant condition;
        StmtVariant thenBranch;
        std::optional<StmtVariant> elseBranch;
        If(ExprVariant condition, StmtVariant thenBranch, std::optional<StmtVariant> elseBranch);
    };

    struct Stmt::While{
        ExprVariant condition;
        StmtVariant body;
        While(ExprVariant condition, StmtVariant body);
    };

    StmtVariant createExprSV(ExprVariant expr);
    StmtVariant createPrintSV(ExprVariant expr);
    StmtVariant createVarSV(Token name, TokenType type, ExprVariant initializer);
    StmtVariant createBlockSV(std::vector<StmtVariant> statements);
    StmtVariant createIfSV(ExprVariant condition, StmtVariant thenBranch, std::optional<StmtVariant> elseBranch);
    StmtVariant createWhileSV(ExprVariant condition, StmtVariant body);

}