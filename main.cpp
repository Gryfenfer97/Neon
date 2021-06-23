#include <iostream>
#include <fstream>
#include <vector>
#include <Lexer.hpp>
#include <AstPrinter.hpp>
#include <Parser.hpp>
#include <Interpreter.hpp>

void run(const std::string& code){
    Ne::Lexer lexer{code};
    std::vector<Ne::Token> tokens = lexer.scanTokens();

    // std::cout << "number of tokens : " << tokens.size() << std::endl;
    // for(auto& token : tokens){
    //     std::cout << token.toString() << std::endl;
    // }
    Ne::Parser parser(tokens);
    auto expr = parser.parse();
    std::cout << Ne::toString(expr) << std::endl;

    // Ne::Interpreter interpreter;
    // auto obj = interpreter.evaluate(std::move(expr));
    // std::cout << interpreter.stringify(obj) << std::endl;
}

std::string readFile(std::string_view path){
    constexpr auto read_size = std::size_t{4096};
    auto stream = std::ifstream{path.data()};
    stream.exceptions(std::ios_base::badbit);

    auto out = std::string{};
    auto buf = std::string(read_size, '\0');
    while (stream.read(& buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}


void runFile(const std::string& path){
    run(readFile(path));
}

void runPrompt(){
    for(;;){
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);
        if(line == "exit" || line == "quit") break;
        // std::cout << "line : " << line << std::endl;
        run(line);
    }
}

int main(int argc, char *argv[]){
    if (argc > 2){
        std::cout << "too many arguments";
        return 10;
    }
    else if(argc == 2){
        runFile(argv[0]);
    }
    else{
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