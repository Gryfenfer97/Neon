#include <Neon/AstPrinter.hpp>

namespace Ne{
    std::string toString(const ExprVariant& expr){
        std::string text;
        switch(expr.index()){
            case 0: // BinaryExpr
            {
                const BinaryExpr& binaryExpr = std::get<BinaryExpr>(expr);
                text = parenthesize(binaryExpr->op.toString(), binaryExpr->left, binaryExpr->right);
                break;
            }
            case 1: // Grouping
            {
                const GroupingExpr& groupingExpr = std::get<GroupingExpr>(expr);
                text = parenthesize("group", groupingExpr->expression);
                break;
            }
            case 2: // Literal
            {
                const LiteralExpr& literalExpr = std::get<LiteralExpr>(expr);
                switch(literalExpr->literal.index()){
                case 0: // string
                    text = std::get<std::string>(literalExpr->literal);
                    break;
                case 1: // int
                    text = std::to_string(std::get<int>(literalExpr->literal));
                    break;
                case 2: // double
                    text = std::to_string(std::get<double>(literalExpr->literal));
                    break;
                case 3: // bool
                    text = std::get<bool>(literalExpr->literal) ? "True" : "False";
                    break;
                case 4: // nullptr_t
                    text = "Nil";
                    break;
                }
                break;
            }
            case 3: // Unary
            {
                const UnaryExpr& unaryExpr = std::get<UnaryExpr>(expr);
                text = parenthesize(unaryExpr->op.toString(), unaryExpr->right);
                break;
            }
        }
        return text;
    }

    std::string parenthesize(const std::string& name, const ExprVariant& arg1 ){
        std::string text = "(" + name;
        text += " " + toString(arg1);
        text += ")";
        return text;
    }

    std::string parenthesize(const std::string& name, const ExprVariant& arg1, const ExprVariant& arg2){
        std::string text = "(" + name;
            text += " " + toString(arg1) + " " + toString(arg2);
        text += ")";
        return text;
    }
} // Ne