#include <Lexer.hpp>

using namespace Ne;

Lexer::Lexer(const std::string& source){
    m_source = source;
    start = m_source.begin();
    current = m_source.begin();
}

std::vector<Token> Lexer::scanTokens(){
    while(current != m_source.end()){
        start = current;
        scanToken();
    }
    m_tokens.emplace_back(TokenType::ENDOF, "eof", line);
    return m_tokens;
}

void Lexer::scanToken(){
    switch(*current){
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '+': addToken(TokenType::PLUS); break;
        case ':': addToken(TokenType::COLON); break;
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '"': string(); break;
        default:
            if(isDigit(*current)){
                number();
            }
            else if(isAlpha(*current)){
                identifier();
            }
    }
    ++current;
}

void Lexer::addToken(TokenType tokenType, const std::string& value){
    m_tokens.emplace_back(tokenType, value, line);
}

void Lexer::addToken(TokenType tokenType){
    m_tokens.emplace_back(tokenType, "", line);
}

bool Lexer::match(char c){
    if(current == m_source.end()) return false;
    if(*current != c) return false;
    current++;
    return true;
}

void Lexer::string(){
    current++;
    while(*current != '"' && current != m_source.end()){
        if(*current == '\n') line++;
        current++;
    }
    if(current == m_source.end()){
        std::runtime_error("Unterminated string.");
    }

    std::string value = std::string(start+1, current);
    addToken(TokenType::STRING, value);
}

bool Lexer::isDigit(char c){
    return '0' <= c && c <= '9';
}

void Lexer::number(){
    while(isDigit(*current) && current != m_source.end()){
        ++current;
    }
    if(*current == '.' && isDigit(*(current+1))){
        ++current;
        while(isDigit(*current) && current != m_source.end()) ++current;
    }
    addToken(TokenType::NUMBER, std::string(start, current));
    current--;
}

void Lexer::identifier(){
    while(isAlphaNumeric(*current)) current++; 

    std::string text = std::string(start, current);
    current--;
    TokenType type;
    if(keywords.find(text) == keywords.end()){
        type = TokenType::IDENTIFIER;
    }else{
        type = keywords.at(text);
    }
    addToken(type);
}

bool Lexer::isAlpha(char c){
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

bool Lexer::isAlphaNumeric(char c){
    return isAlpha(c) || isDigit(c);
}