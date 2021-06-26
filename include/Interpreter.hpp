#pragma once
#include <Node.hpp>
#include <optional>
#include <Environment.hpp>

namespace Ne{
    class Interpreter{
    public:
        LiteralObject evaluateBinary(ExprVariant expr);
        LiteralObject evaluateGrouping(ExprVariant expr);
        LiteralObject evaluateLiteral(ExprVariant expr);
        LiteralObject evaluateUnary(ExprVariant expr);
        LiteralObject evaluateVariable(VariableExpr expr);
        LiteralObject evaluateAssign(AssignExpr expr);
        std::string stringify(LiteralObject obj);
        LiteralObject evaluateExpr(ExprVariant expr);
        void evaluateStmts(std::vector<StmtVariant>& statements);
        void evaluateExprStmt(ExprStmt stmt);
        void evaluatePrintStmt(PrintStmt stmt);
        void evaluateVarStmt(VarStmt stmt);
        void evaluateBlockStmt(BlockStmt stmt);

        void executeBlock(std::vector<StmtVariant> statements, std::shared_ptr<Environment> environment);

    private:
        Environment environment;
    };
}