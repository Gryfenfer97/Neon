#include <Neon/Node.hpp>

using namespace Ne;

Expr::Binary::Binary(ExprVariant left, Token op, ExprVariant right) : 
    left(std::move(left)), op(op), right(std::move(right))
{}

Expr::Grouping::Grouping(ExprVariant expression) : expression(std::move(expression))
{}

Expr::Literal::Literal(const LiteralObject& literal) : literal(literal)
{}

TokenType Expr::Literal::getType(){
    switch(literal.index()){
    case 0: // String
        return TokenType::STRING;
    case 1: // Int
        return TokenType::INT;
    case 2: // Double
        return TokenType::DOUBLE;
    case 3: // Bool
        return TokenType::BOOL;
    case 4: // NIL (nullptr_t)
        return TokenType::NIL;
    default:
        throw std::runtime_error("type not found");
    }
}

Expr::Unary::Unary(Token op, ExprVariant right) : 
    op(op), right(std::move(right))
{}

Expr::Variable::Variable(Token name) : 
    name(name)
{}

Expr::Assign::Assign(Token name, ExprVariant value) : 
    name(name), value(std::move(value))
{}

Expr::Logical::Logical(ExprVariant left, Token op, ExprVariant right) : 
    left(std::move(left)), op(op), right(std::move(right))
{}

Expr::Call::Call(ExprVariant callee, Token paren, std::vector<ExprVariant> arguments) :
    callee(std::move(callee)), paren(paren), arguments(std::move(arguments))
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

ExprVariant Ne::createVariableEV(Token name){
    return std::make_unique<Expr::Variable>(name);
}

ExprVariant Ne::createAssignEV(Token name, ExprVariant value){
    return std::make_unique<Expr::Assign>(name, std::move(value));
}

ExprVariant Ne::createLogicalEV(ExprVariant left, Token op, ExprVariant right){
    return std::make_unique<Expr::Logical>(std::move(left), op, std::move(right));
}

ExprVariant Ne::createCallEV(ExprVariant callee, Token paren, std::vector<ExprVariant> arguments){
    return std::make_unique<Expr::Call>(std::move(callee), paren, std::move(arguments));
}

Stmt::Expr::Expr(ExprVariant expr) : expression(std::move(expr))
{}

Stmt::Print::Print(ExprVariant expr) : expression(std::move(expr))
{}

Stmt::Var::Var(Token name, TokenType type, ExprVariant initializer) : name(name), type(type), initializer(std::move(initializer))
{}

Stmt::Block::Block(std::vector<StmtVariant> statements) : statements(std::move(statements))
{}

Stmt::If::If(ExprVariant condition, StmtVariant thenBranch, std::optional<StmtVariant> elseBranch) : 
    condition(std::move(condition)), thenBranch(std::move(thenBranch)), elseBranch(std::move(elseBranch))
{}

Stmt::While::While(ExprVariant condition, StmtVariant body) : 
    condition(std::move(condition)), body(std::move(body))    
{}

Stmt::Function::Function(Token name, std::vector<Token> params, std::vector<StmtVariant> body) : 
    name(name), params(std::move(params)), body(std::move(body))
{}

StmtVariant Ne::createExprSV(ExprVariant expr){
    return std::make_unique<Stmt::Expr>(std::move(expr));
}

StmtVariant Ne::createPrintSV(ExprVariant expr){
    return std::make_unique<Stmt::Print>(std::move(expr));
}

StmtVariant Ne::createVarSV(Token name, TokenType type, ExprVariant initializer){
    return std::make_unique<Stmt::Var>(name, type, std::move(initializer));
}

StmtVariant Ne::createBlockSV(std::vector<StmtVariant> statements){
    return std::make_unique<Stmt::Block>(std::move(statements));
}

StmtVariant Ne::createIfSV(ExprVariant condition, StmtVariant thenBranch, std::optional<StmtVariant> elseBranch){
    return std::make_unique<Stmt::If>(std::move(condition), std::move(thenBranch), std::move(elseBranch));
}

StmtVariant Ne::createWhileSV(ExprVariant condition, StmtVariant body){
    return std::make_unique<Stmt::While>(std::move(condition), std::move(body));
}

StmtVariant Ne::createFunctionSV(Token name, std::vector<Token> params, std::vector<StmtVariant> body){
    return std::make_unique<Stmt::Function>(name, std::move(params), std::move(body));
}


