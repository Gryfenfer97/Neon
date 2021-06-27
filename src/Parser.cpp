#include <Parser.hpp>
#include <optional>

namespace Ne{
    Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens){
        current = this->tokens.begin();
    }

    std::vector<StmtVariant> Parser::parse(){
        std::vector<StmtVariant> statements;
        while (!isAtEnd()) {
            statements.push_back(declaration());
        }

        return statements; 
    }

    StmtVariant Parser::declaration(){
        if(match({TokenType::VAR})) return varDeclaration();
        return statement();
    }

    StmtVariant Parser::varDeclaration(){
        Token name = consume(TokenType::IDENTIFIER, "Excpect variable name.");
        TokenType type;
        ExprVariant initializer;
        bool explicitType = false;
        if(match({TokenType::COLON})){
            if(match({TokenType::INT, TokenType::DOUBLE, TokenType::STRING, TokenType::BOOL})){
                explicitType = true;
                type = previous().getType();
            }
            else{
                throw std::runtime_error("unrecognized type");
            }
        }

        if(match({TokenType::EQUAL})){
            initializer = expression();
            if(explicitType){
                // We check if the both types are the same
                auto detectedType = std::get<LiteralExpr>(initializer)->getType();
                if(type != detectedType){
                    throw std::runtime_error("Both type does not correspond");
                }
            }
            else{
                type = std::get<LiteralExpr>(initializer)->getType();
            }    
        }
        else{
            if(explicitType){
                switch(type){
                case TokenType::STRING:
                    initializer = createLiteralEV("");
                    break;
                case TokenType::INT:
                    initializer = createLiteralEV(0);
                    break;
                case TokenType::DOUBLE:
                    initializer = createLiteralEV(0.);
                    break;
                case TokenType::BOOL:
                    initializer = createLiteralEV(false);
                    break;
                }
            }
            else{
                initializer = createLiteralEV(nullptr);
                type = TokenType::NIL;
            }
        }
 
        
        consume(TokenType::SEMICOLON, "Expect ';' after declaration.");
        return createVarSV(name, type, std::move(initializer));
    }

    StmtVariant Parser::statement(){
        if(match({TokenType::IF})) return ifStatement();
        if(match({TokenType::PRINT})) return printStatement();
        if(match({TokenType::LEFT_BRACE})) return createBlockSV(block());
        return expressionStatement();
    }

    StmtVariant Parser::ifStatement(){
        consume(TokenType::LEFT_PAREN, "Expect '(' after 'if'.");
        ExprVariant condition = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after condition.");

        StmtVariant thenBranch = statement();
        std::optional<StmtVariant> elseBranch = {};
        if(match({TokenType::ELSE}))
            elseBranch = statement();

        return createIfSV(std::move(condition), std::move(thenBranch), std::move(elseBranch));
    }

    StmtVariant Parser::printStatement(){
        consume(TokenType::LEFT_PAREN, "Expect '(' after 'print'.");
        ExprVariant expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' at the end of 'print'.");
        consume(TokenType::SEMICOLON, "Expect ';' after print statement.");
        return createPrintSV(std::move(expr));
    }

    std::vector<StmtVariant> Parser::block(){
        std::vector<StmtVariant> statements;

        while(!check(TokenType::RIGHT_BRACE) && !isAtEnd()){
            statements.push_back(declaration());
        }
        consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
        return statements;
    }

    StmtVariant Parser::expressionStatement(){
        ExprVariant expr = expression();
        consume(TokenType::SEMICOLON, "Expect ';' after value.");
        return createExprSV(std::move(expr));
    }

    ExprVariant Parser::expression(){
        // return equality();
        return assignment();
    }

    ExprVariant Parser::assignment(){
        ExprVariant expr = orExpr();
        if(match({TokenType::EQUAL})){
            Token equal = previous();
            ExprVariant value = assignment();
            if(std::holds_alternative<VariableExpr>(expr)){
                Token name = std::get<VariableExpr>(expr)->name;
                return createAssignEV(name, std::move(value));
            }
            throw std::runtime_error(equal.toString() + ": Invalid assignment target.");
        }
        return expr;
    }

    ExprVariant Parser::orExpr(){
        ExprVariant expr = andExpr();
        while(match({TokenType::OR})){
            Token op = previous();
            ExprVariant right = andExpr();
            expr = createLogicalEV(std::move(expr), op, std::move(right));
        }
        return expr;
    }

    ExprVariant Parser::andExpr(){
        ExprVariant expr = equality();
        while(match({TokenType::AND})){
            Token op = previous();
            ExprVariant right = equality();
            expr = createLogicalEV(std::move(expr), op, std::move(right));
        }
        return expr;
    }

    ExprVariant Parser::equality(){
        ExprVariant expr = comparison();
        while(match({TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL})){
            Token op = previous();
            ExprVariant right = comparison();
            expr = createBinaryEV(std::move(expr), op, std::move(right));
        }
        return expr;
    }

    bool Parser::match(const std::initializer_list<TokenType>& types){
        for(auto& type : types){
            if(check(type)){
                ++current;
                return true;
            }
        }
        return false;
    }

    bool Parser::check(TokenType type){
        if(isAtEnd()) return false;
        return current->getType() == type;
    }

    bool Parser::isAtEnd(){
        return current->getType() == TokenType::ENDOF;
    }

    Token Parser::previous(){
        return *(current-1);
    }

    Token Parser::advance(){
        if (!isAtEnd()) ++current;
        return previous();
    }

    ExprVariant Parser::comparison(){
        ExprVariant expr = term();
        while(match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})){
            Token op = previous();
            ExprVariant right = term();
            expr = createBinaryEV(std::move(expr), op, std::move(right));
        }
        return expr;
    }

    ExprVariant Parser::term(){
        ExprVariant expr = factor();
        while(match({TokenType::MINUS, TokenType::PLUS})){
            Token op = previous();
            ExprVariant right = factor();
            expr = createBinaryEV(std::move(expr), op, std::move(right));
        }
        return expr;
    }

    ExprVariant Parser::factor(){
        ExprVariant expr = unary();
        while(match({TokenType::SLASH, TokenType::STAR})){
            Token op = previous();
            ExprVariant right = unary();
            expr = createBinaryEV(std::move(expr), op, std::move(right));
        }
        return expr;
    }

    ExprVariant Parser::unary(){
        while(match({TokenType::MINUS, TokenType::BANG})){
            Token op = previous();
            ExprVariant right = unary();
            return createUnaryEV(op, std::move(right));
        }
        return primary();
    }

    ExprVariant Parser::primary(){
        if(match({TokenType::FALSE})) return createLiteralEV(false);
        else if(match({TokenType::TRUE})) return createLiteralEV(true);
        else if(match({TokenType::NIL})) return createLiteralEV("nil");
        else if(match({TokenType::STRING})){
            return createLiteralEV(previous().toString());
        }
        else if(match({TokenType::INT})){
            return createLiteralEV(std::stoi(previous().toString()));
        }
        else if(match({TokenType::DOUBLE})){
            return createLiteralEV(std::stod(previous().toString()));
        }
        else if(match({TokenType::IDENTIFIER})){
            return createVariableEV(previous());
        }
        else if(match({TokenType::LEFT_PAREN})){
            ExprVariant expr = expression();
            consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
            return createGroupingEV(std::move(expr));
        }
        return primary();
    }

    Token Parser::consume(TokenType type, const std::string& message){
        if(check(type)) return *(current++);
        throw std::runtime_error(current->toString() + " " + message);
    }
} // Ne