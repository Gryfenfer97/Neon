#pragma once
#include <initializer_list>
#include <Node.hpp>

namespace Ne{
    class Parser{
    public:
        Parser(const std::vector<Token>& tokens);
        std::vector<StmtVariant> parse();

    private:
        std::vector<Token> tokens;
        std::vector<Token>::iterator current;
        ExprVariant expression();
        ExprVariant assignment();
        ExprVariant orExpr();
        ExprVariant andExpr();
        ExprVariant equality();
        bool match(const std::initializer_list<TokenType>& types);
        [[nodiscard]] StmtVariant declaration();
        [[nodiscard]] StmtVariant varDeclaration();
        [[nodiscard]] StmtVariant statement();
        [[nodiscard]] StmtVariant ifStatement();
        [[nodiscard]] StmtVariant printStatement();
        [[nodiscard]] StmtVariant whileStatement();
        [[nodiscard]] StmtVariant forStatement();
        [[nodiscard]] std::vector<StmtVariant> block();
        [[nodiscard]] StmtVariant expressionStatement();
        [[nodiscard]] Token previous();
        [[nodiscard]] Token advance();
        [[nodiscard]] bool check(TokenType type);
        [[nodiscard]] bool isAtEnd();
        [[nodiscard]] ExprVariant comparison();
        [[nodiscard]] ExprVariant term();
        [[nodiscard]] ExprVariant factor();
        [[nodiscard]] ExprVariant unary();
        [[nodiscard]] ExprVariant primary();
        Token consume(TokenType type, const std::string& message);

    };
}