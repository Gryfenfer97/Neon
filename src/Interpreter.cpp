#include <Interpreter.hpp>

namespace Ne{
    LiteralObject Interpreter::evaluateExpr(ExprVariant expr){
        switch(expr.index()){
        case 0: // Binary
            return evaluateBinary(std::move(std::get<BinaryExpr>(expr)));
        case 1: // Grouping
            return evaluateGrouping(std::move(std::get<GroupingExpr>(expr)));
        case 2: // Literal
            return evaluateLiteral(std::move(std::get<LiteralExpr>(expr)));
        case 3: // Unary
            return evaluateUnary(std::move(std::get<UnaryExpr>(expr)));
        default:
            return "";
        }
    }
    
    std::optional<LiteralObject> Interpreter::evaluateStmts(const std::vector<StmtVariant>& statements){
        for(const auto& stmt : statements){
            std::optional<LiteralObject> result;
            switch(stmt.index()){
            case 0: // Expression
                result = evaluateExprStmt(std::move(std::get<ExprStmt>(stmt)));
                break;
            case 1: // Print
                result = evaluatePrintStmt(std::move(std::get<PrintStmt>(stmt)));
                break;
            }
            return result;
        }
    }

    LiteralObject Interpreter::evaluateBinary(ExprVariant expr){
        BinaryExpr exprBinary = std::move(std::get<BinaryExpr>(expr));
        LiteralObject left = evaluateExpr(std::move(exprBinary->left));
        LiteralObject right = evaluateExpr(std::move(exprBinary->right));
        switch(exprBinary->op.getType()){
        case TokenType::PLUS:
            if(std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) + std::get<int>(right);
            if(std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
                return std::get<double>(left) + std::get<double>(right);
            if(std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right))
                return std::get<std::string>(left) + std::get<std::string>(right);

        case TokenType::MINUS:
            if(std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) - std::get<int>(right);
            if(std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
                return std::get<double>(left) - std::get<double>(right);

        case TokenType::STAR:
            if(std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) * std::get<int>(right);
            if(std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
                return std::get<double>(left) * std::get<double>(right);

        case TokenType::SLASH:
            if(std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) / std::get<int>(right);
            if(std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
                return std::get<double>(left) / std::get<double>(right);

        case TokenType::EQUAL_EQUAL:
            if(std::holds_alternative<bool>(left) && std::holds_alternative<bool>(right))
                return std::get<bool>(left) == std::get<bool>(right);
            if(std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) == std::get<int>(right);

        case TokenType::BANG_EQUAL:
            if(std::holds_alternative<bool>(left) && std::holds_alternative<bool>(right))
                return std::get<bool>(left) != std::get<bool>(right);
            if(std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) != std::get<int>(right);
        }
        return "";
    }

    LiteralObject Interpreter::evaluateGrouping(ExprVariant expr){
        return evaluateExpr(std::move(expr));
    }

    LiteralObject Interpreter::evaluateLiteral(ExprVariant expr){
        LiteralExpr exprLiteral = std::move(std::get<LiteralExpr>(expr));
        return exprLiteral->literal;
    }

    LiteralObject Interpreter::evaluateUnary(ExprVariant expr){
        UnaryExpr exprUnary = std::move(std::get<UnaryExpr>(expr));
        LiteralObject right = evaluateExpr(std::move(exprUnary->right));
        switch(right.index()){
        case 0: // string
            std::runtime_error("symbol minus before string");
        case 1: // INT
            switch(exprUnary->op.getType()){
            case TokenType::MINUS:
                return -1 * std::get<int>(right);
            }
        case 2: // DOUBLE
            switch(exprUnary->op.getType()){
            case TokenType::MINUS:
                return -1 * std::get<double>(right);
            }
        case 3: // BOOL
            switch(exprUnary->op.getType()){
            case TokenType::BANG:
                return !std::get<bool>(right);
            }
        }
        return right;
    }

    std::string Interpreter::stringify(LiteralObject obj){
        switch(obj.index()){
        case 0: //string
            return std::get<std::string>(obj);
        case 1: //int
            return std::to_string(std::get<int>(obj));
        case 2: // double
            return std::to_string(std::get<double>(obj));
        case 3: // bool 
            return std::get<bool>(obj) ? "True" : "False";
        }
        return "";
    }

    void Interpreter::evaluateExprStmt(ExprStmt stmt){
        ExprStmt exprStmt = std::move(stmt);
        evaluateExpr(exprStmt->expression);
    }

    void Interpreter::evaluatePrintStmt(PrintStmt stmt){
        ExprStmt printStmt = std::move(stmt);
        LiteralObject value = evaluateExpr(printStmt->expression);
        std::cout << stringify(value) << std::endl;
    }
}