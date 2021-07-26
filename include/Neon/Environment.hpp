#pragma once
#include <unordered_map>
#include <string>
#include <Neon/Node.hpp>

namespace Ne
{

    namespace Env{
        struct Variable{
            TokenType type;
            LiteralObject obj;
        };
    }

    class Environment
    {
    public:
        Environment() = default;
        Environment(std::shared_ptr<Environment> enclosing);

        void define(const std::string& name, LiteralObject value);
        LiteralObject get(const Token& name);
        void assign(const Token& name, LiteralObject value);
        void clear();
        
        std::shared_ptr<Environment> getParent();
        
        std::shared_ptr<Environment> enclosing = nullptr;

    private:
        std::unordered_map<std::string, LiteralObject> values;
        bool isVarExist(const std::string& name);
        LiteralObject& getReferenceToVar(const Token& name);
    };
}
