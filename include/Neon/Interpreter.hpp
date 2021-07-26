#pragma once
#include <Neon/Node.hpp>
#include <memory>
#include <optional>
#include <Neon/Environment.hpp>

namespace Ne{
    class Interpreter{
    public:
        Interpreter();

        LiteralObject evaluateBinary(BinaryExpr& expr);
        LiteralObject evaluateGrouping(GroupingExpr& expr);
        LiteralObject evaluateLiteral(LiteralExpr& expr);
        LiteralObject evaluateUnary(UnaryExpr& expr);
        LiteralObject evaluateVariable(VariableExpr& expr);
        LiteralObject evaluateAssign(AssignExpr& expr);
        LiteralObject evaluateLogical(LogicalExpr& expr);
        LiteralObject evaluateCall(CallExpr& expr);
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
        void evaluateFunctionStmt(FunctionStmt& stmt);

        void executeBlock(std::vector<StmtVariant>& statements, std::shared_ptr<Environment> environment);
        
        Environment getGlobalEnv(){std::cout << "hey" << std::endl; return globals;}
        std::shared_ptr<Environment> getEnv(){std::cout << "bonne fonction appelée" << std::endl; return environment; }

    private:
        Environment globals;
        std::shared_ptr<Environment> environment;
    };


    class Function : public Callable{
    private:
        FunctionStmt declaration;
    public:
        Function(FunctionStmt& declaration) : Callable(){
            this->declaration = std::move(declaration);
            arity = this->declaration->params.size();
        }

        virtual LiteralObject call(Interpreter& interpreter, std::vector<LiteralObject>& args) override{
            std::shared_ptr<Environment> env = std::make_shared<Environment>(interpreter.getEnv());
            for(int i=0;i<declaration->params.size();i++){
                env->define(declaration->params.at(i).toString(), args.at(i));
            }
            interpreter.executeBlock(declaration->body, std::make_shared<Environment>(env));
            return nullptr;
        };
    };
}