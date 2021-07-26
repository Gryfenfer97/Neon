#include <Interpreter.hpp>
#include <Builtins/time.hpp>

namespace Ne{
    Interpreter::Interpreter(){
        globals.define("getDateTime", std::make_shared<Builtins::GetDateTime>(Builtins::GetDateTime()));
        environment = globals;
    }

    LiteralObject Interpreter::evaluateExpr(ExprVariant& expr){
        switch(expr.index()){
        case 0: // Binary
            return evaluateBinary(std::get<BinaryExpr>(expr));
        case 1: // Grouping
            return evaluateGrouping(std::get<GroupingExpr>(expr));
        case 2: // Literal
            return evaluateLiteral(std::get<LiteralExpr>(expr));
        case 3: // Unary
            return evaluateUnary(std::get<UnaryExpr>(expr));
        case 4: // Variable
            return evaluateVariable(std::get<VariableExpr>(expr));
        case 5: // Variable
            return evaluateAssign(std::get<AssignExpr>(expr));
        case 6: // Logical
            return evaluateLogical(std::get<LogicalExpr>(expr));
        case 7: // Logical
            return evaluateCall(std::get<CallExpr>(expr));
        default:
            return "";
        }
    }
    
    void Interpreter::evaluateStmts(std::vector<StmtVariant>& statements){
        for(auto& stmt : statements){
            evaluateStmt(stmt);
        }
    }

    void Interpreter::evaluateStmt(StmtVariant& stmt){
        switch(stmt.index()){
            case 0: // Expression
                evaluateExprStmt(std::get<ExprStmt>(stmt));
                break;
            case 1: // Print
                evaluatePrintStmt(std::get<PrintStmt>(stmt));
                break;
            case 2: // Var
                evaluateVarStmt(std::get<VarStmt>(stmt));
                break;
            case 3: // Block
                evaluateBlockStmt(std::get<BlockStmt>(stmt));
                break;
            case 4: // If
                evaluateIfStmt(std::get<IfStmt>(stmt));
                break;
            case 5: // While
                evaluateWhileStmt(std::get<WhileStmt>(stmt));
                break;
            case 6: // Function
                evaluateFunctionStmt(std::get<FunctionStmt>(stmt));
                break;
            }
    }


    LiteralObject Interpreter::evaluateBinary(BinaryExpr& expr){
        BinaryExpr& exprBinary = expr;
        LiteralObject left = evaluateExpr(exprBinary->left);
        LiteralObject right = evaluateExpr(exprBinary->right);
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

        // Comparison        
        case TokenType::LESS:
            if(std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) < std::get<int>(right);
            if(std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
                return std::get<double>(left) < std::get<double>(right);

        case TokenType::LESS_EQUAL:
            if(std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) <= std::get<int>(right);
            if(std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
                return std::get<double>(left) <= std::get<double>(right);
        
        case TokenType::GREATER:
            if(std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) > std::get<int>(right);
            if(std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
                return std::get<double>(left) > std::get<double>(right);

        case TokenType::GREATER_EQUAL:
            if(std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) >= std::get<int>(right);
            if(std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
                return std::get<double>(left) >= std::get<double>(right);
        }
        return "";
    }

    LiteralObject Interpreter::evaluateGrouping(GroupingExpr& expr){
        GroupingExpr& exprGrouping = expr;
        return evaluateExpr(exprGrouping->expression);
    }

    LiteralObject Interpreter::evaluateLiteral(LiteralExpr& expr){
        LiteralExpr& exprLiteral = expr;
        return exprLiteral->literal;
    }

    LiteralObject Interpreter::evaluateUnary(UnaryExpr& expr){
        UnaryExpr& exprUnary = expr;
        LiteralObject right = evaluateExpr(exprUnary->right);
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

    LiteralObject Interpreter::evaluateVariable(VariableExpr& expr){
        return environment.get(expr->name);
    }

    LiteralObject Interpreter::evaluateAssign(AssignExpr& expr){
        LiteralObject value = evaluateExpr(expr->value);
        environment.assign(expr->name, value);
        return value;
    }

    LiteralObject Interpreter::evaluateLogical(LogicalExpr& expr){
        LiteralObject left = evaluateExpr(expr->left);
        LiteralObject right = evaluateExpr(expr->right);
        if(left.index() != right.index())
            throw std::runtime_error("the condition logical op has to be a boolean");
        switch(left.index()){
        case 3: // BOOL
            break;
        default:
            throw std::runtime_error("the condition logical op has to be a boolean");
        }
        switch(expr->op.getType()){
        case TokenType::OR:
            return std::get<3>(left) || std::get<3>(right);
        case TokenType::AND:
            return std::get<3>(left) && std::get<3>(right);
        default:
            throw std::runtime_error("operator not recongized.");
        }
        
    }

    LiteralObject Interpreter::evaluateCall(CallExpr& expr){
        LiteralObject callee = evaluateExpr(expr->callee);
        std::vector<LiteralObject> arguments;
        for(auto& obj : expr->arguments){
            arguments.push_back(evaluateExpr(obj));
        }

        if(!std::holds_alternative<CallablePtr>(callee)){
            throw std::runtime_error("things has to be a callable");
        }

        CallablePtr function = std::get<4>(callee);
        if(arguments.size() != function->getArity()){
            throw std::runtime_error(expr->paren.toString() + " Excpected " + std::to_string(function->getArity()) + " arguments but got " + std::to_string(arguments.size()) + " arguments instead.");
        }
        return function->call(*this, arguments);
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
        case 4: // nil (nullptr_t)
            return "Nil";
        }
        return "";
    }

    void Interpreter::evaluateExprStmt(ExprStmt& stmt){
        evaluateExpr(stmt->expression);
    }

    void Interpreter::evaluatePrintStmt(PrintStmt& stmt){
        LiteralObject value = evaluateExpr(stmt->expression);
        std::cout << stringify(value) << std::endl;
    }

    void Interpreter::evaluateVarStmt(VarStmt& stmt){
        LiteralObject value;
        value = evaluateExpr(stmt->initializer);
        environment.define(stmt->name.toString(), value);
    }

    void Interpreter::evaluateBlockStmt(BlockStmt& stmt){
        // std::shared_ptr<Environment> previous = std::allocate_shared<Environment>(std::allocator<Environment>(), this->environment);
        // this->environment = Environment(previous);
        // executeBlock(stmt->statements, std::make_shared<Environment>(Environment(previous)));
        // this->environment.clear();
        // this->environment = *previous;

        executeBlock(stmt->statements, std::make_shared<Environment>(std::make_shared<Environment>(this->environment)));
        
    }

    void Interpreter::executeBlock(std::vector<StmtVariant>& statements, std::shared_ptr<Environment> env){
        std::shared_ptr<Environment> previous = std::allocate_shared<Environment>(std::allocator<Environment>(), this->environment);
        this->environment = *env;
        evaluateStmts(statements);
        this->environment.clear();
        this->environment = *previous;

        // this->environment = *env;
        // evaluateStmts(statements);
        // this->environment.clear();
    }

    void Interpreter::evaluateIfStmt(IfStmt& stmt){
        LiteralObject condition = evaluateExpr(stmt->condition);
        switch(condition.index()){
        case 3: // BOOL
            break;
        default:
            throw std::runtime_error("the condition has to be a boolean");
        }
        if(std::get<3>(condition)){
            evaluateStmt(stmt->thenBranch);
        }
        else{
            if(stmt->elseBranch.has_value()){
                 evaluateStmt(stmt->elseBranch.value());
            }
        }
    }

    void Interpreter::evaluateWhileStmt(WhileStmt& stmt){
        LiteralObject condition = evaluateExpr(stmt->condition);
        switch(condition.index()){
        case 3: // BOOL
            break;
        default:
            throw std::runtime_error("the condition has to be a boolean in a while loop");
        }
        while(std::get<3>(evaluateExpr(stmt->condition))){
            evaluateStmt(stmt->body);
        }
    }

    void Interpreter::evaluateFunctionStmt(FunctionStmt& stmt){
        // environment.define(stmt->name.toString(), std::make_shared<Function>(stmt));
        this->environment.define("count", std::make_shared<Function>(stmt));
    }
}