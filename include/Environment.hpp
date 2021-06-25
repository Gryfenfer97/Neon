#pragma once
#include <unordered_map>
#include <string>
#include <Node.hpp>

namespace Ne
{

    class Environment
    {
    public:
        void define(const std::string& name, LiteralObject value);
        LiteralObject get(const Token& name);

    private:
        std::unordered_map<std::string, LiteralObject> values;
    };
}
