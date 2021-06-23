#include <Parser.hpp>

namespace Ne{
    Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens){
        current = this->tokens.begin();
    }

    ExprVariant Parser::parse(){
        return expression();
    }

    ExprVariant Parser::expression(){
        return equality();
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
        if(match({TokenType::FALSE})) return createLiteralEV("false");
        else if(match({TokenType::TRUE})) return createLiteralEV("true");
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
        else if(match({TokenType::LEFT_PAREN})){
            ExprVariant expr = expression();
            consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
            return createGroupingEV(std::move(expr));
        }
        return primary();
    }

    Token Parser::consume(TokenType type, const std::string& message){
        if(check(type)) return *(++current);
        throw std::runtime_error(current->toString() + " " + message);
    }
} // Ne