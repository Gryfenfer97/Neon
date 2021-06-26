#pragma once
#include <unordered_map>
#include <string>
#include <Node.hpp>

namespace Ne
{

    class Environment
    {
    public:
        Environment() = default;
        Environment(std::shared_ptr<Environment> enclosing);

        void define(const std::string& name, LiteralObject value);
        LiteralObject get(const Token& name);
        void assign(const Token& name, LiteralObject value);
        std::shared_ptr<Environment> enclosing;

    private:
        std::unordered_map<std::string, LiteralObject> values;
        bool isVarExist(const std::string& name);
    };
}
