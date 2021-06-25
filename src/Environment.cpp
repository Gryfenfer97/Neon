#include <Environment.hpp>

namespace Ne{
    void Environment::define(const std::string& name, LiteralObject value){
        if(values.find(name) != values.end()){
            if(values[name].index() != value.index()) // If they are of two different types
                throw std::runtime_error("invalid conversion");
        }
        values[name] = value;
    }

    LiteralObject Environment::get(const Token& name){
        if(values.find(name.toString()) != values.end()){
            return values[name.toString()];
        }
        throw std::runtime_error("undefined variable '" + name.toString() + "'.");
    }
} // Ne