#include <Node.hpp>

using namespace Ne;

Expr::Binary::Binary(ExprVariant left, Token op, ExprVariant right) : 
    left(std::move(left)), op(op), right(std::move(right))
{}

Expr::Grouping::Grouping(ExprVariant expression) : expression(std::move(expression))
{}

Expr::Literal::Literal(const LiteralObject& literal) : literal(literal)
{}

Expr::Unary::Unary(Token op, ExprVariant right) : 
    op(op), right(std::move(right))
{}

ExprVariant Ne::createBinaryEV(ExprVariant left, Token op, ExprVariant right){
    return std::make_unique<Expr::Binary>(std::move(left), op, std::move(right));
}

ExprVariant Ne::createGroupingEV(ExprVariant expression){
    return std::make_unique<Expr::Grouping>(std::move(expression));
}

ExprVariant Ne::createLiteralEV(const LiteralObject& literal){
    return std::make_unique<Expr::Literal>(literal);
}

ExprVariant Ne::createUnaryEV(Token op, ExprVariant right){
    return std::make_unique<Expr::Unary>(op, std::move(right));
}