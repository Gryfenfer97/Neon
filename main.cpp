#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <Lexer.hpp>
#include <AstPrinter.hpp>
#include <Parser.hpp>
#include <Interpreter.hpp>

void run(const std::string &code, Ne::Interpreter& interpreter)
{
    Ne::Lexer lexer{code};
    std::vector<Ne::Token> tokens = lexer.scanTokens();

    // std::cout << "number of tokens : " << tokens.size() << std::endl;
    // for(auto& token : tokens){
    //     std::cout << token.toString() << std::endl;
    // }
    Ne::Parser parser(tokens);
    auto statements = parser.parse();
    // std::cout << Ne::toString(expr) << std::endl;

    
    interpreter.evaluateStmts(statements);
    // std::cout << interpreter.stringify(obj) << std::endl;
}

std::string readFile(std::string path)
{
    std::ifstream file{ path };
    if ( file )
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }
    else 
    {
        throw std::runtime_error("file not found!");
    }
}

void runFile(const std::string &path)
{
    Ne::Interpreter interpreter;
    run(readFile(path), interpreter);
}

void runPrompt()
{
    Ne::Interpreter interpreter;
    for (;;)
    {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);
        if (line == "exit" || line == "quit")
            break;
        // std::cout << "line : " << line << std::endl;
        run(line, interpreter);
    }
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        std::cout << "too many arguments";
        return 10;
    }
    else if (argc == 2)
    {
        runFile(argv[1]);
    }
    else
    {
        runPrompt();
    }

    // auto expr = Ne::createBinaryEV(
    //     Ne::createUnaryEV(
    //         Ne::Token(Ne::TokenType::MINUS, "-", 1),
    //         Ne::createLiteralEV("123")
    //     ),
    //     Ne::Token(Ne::TokenType::STAR, "*",1),
    //     Ne::createGroupingEV(
    //         Ne::createLiteralEV("47.65")
    //     )
    // );
    // std::cout << Ne::toString(expr) << std::endl;

    return 0;
}