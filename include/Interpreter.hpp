#pragma once
#include <Node.hpp>
#include <optional>
#include <Environment.hpp>

namespace Ne{
    class Interpreter{
    public:
        LiteralObject evaluateBinary(BinaryExpr& expr);
        LiteralObject evaluateGrouping(GroupingExpr& expr);
        LiteralObject evaluateLiteral(LiteralExpr& expr);
        LiteralObject evaluateUnary(UnaryExpr& expr);
        LiteralObject evaluateVariable(VariableExpr& expr);
        LiteralObject evaluateAssign(AssignExpr& expr);
        LiteralObject evaluateLogical(LogicalExpr& expr);
        std::string stringify(LiteralObject obj);
        LiteralObject evaluateExpr(ExprVariant& expr);
        void evaluateStmts(std::vector<StmtVariant>& statements);
        void evaluateStmt(StmtVariant& statement);
        void evaluateExprStmt(ExprStmt& stmt);
        void evaluatePrintStmt(PrintStmt& stmt);
        void evaluateVarStmt(VarStmt& stmt);
        void evaluateBlockStmt(BlockStmt& stmt);
        void evaluateIfStmt(IfStmt& stmt);
        void evaluateWhileStmt(WhileStmt& stmt);

        void executeBlock(std::vector<StmtVariant>& statements, std::shared_ptr<Environment> environment);

    private:
        Environment environment;
    };
}