#pragma once
#include <memory>
#include <variant>
#include <vector>

namespace Ne{
    class Interpreter;
    class Callable;
    using CallablePtr = std::shared_ptr<Callable>;

    using LiteralObject = std::variant<std::string, int, double, bool, CallablePtr, nullptr_t>;

    class Callable{
    protected:
        std::size_t arity;
    public:
        virtual LiteralObject call(Interpreter& interpreter, std::vector<LiteralObject>& args){return "kfjbd";};
        std::size_t getArity(){
            return arity;
        }
    };


    
}