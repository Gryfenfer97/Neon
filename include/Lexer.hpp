#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace Ne{
    enum class TokenType{
        // Single-character tokens.
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR, COLON,

        // One or two character tokens.
        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        // Literals.
        IDENTIFIER, STRING, NUMBER,

        // Keywords.
        AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
        PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

        ENDOF
    };

    const std::unordered_map<std::string, TokenType> keywords = {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"fun", TokenType::FUN},
        {"for", TokenType::FOR},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE}
    };

    class Token{
    public:
        Token() = default;
        Token(TokenType tokenType, const std::string& lexme, const std::size_t& line){
            m_tokenType = tokenType;
            m_lexme = lexme;
            m_line = line;
        }

        std::string toString(){
            return m_lexme;
        }
    private:
        TokenType m_tokenType;
        std::string m_lexme;
        std::size_t m_line;

    };

    class Lexer{
    public:
        Lexer(const std::string& source);
        std::vector<Token> scanTokens();

    private:
        std::string m_source;
        std::vector<Token> m_tokens;
        int line;

        std::string::iterator start;
        std::string::iterator current;

        void scanToken();
        void addToken(TokenType tokenType, const std::string& value);
        void addToken(TokenType tokenType);
        bool match(char c);
        void string();
        [[nodiscard]] bool isDigit(char c);
        void number();
        void identifier();
        [[nodiscard]] bool isAlpha(char c);
        [[nodiscard]] bool isAlphaNumeric(char c);
    };
}