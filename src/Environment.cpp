#include <Environment.hpp>

namespace Ne{

    Environment::Environment(std::shared_ptr<Environment> enclosing) : enclosing(enclosing)
    {}

    void Environment::define(const std::string& name, LiteralObject value){
        if(!isVarExist(name))
            values[name] = value;
        else
            throw std::runtime_error("error: the variable '" + name + "' already exist.");
    }

    LiteralObject Environment::get(const Token& name){
        if(values.find(name.toString()) != values.end()){
            return values[name.toString()];
        }
        if(enclosing != nullptr) return enclosing->get(name);
        throw std::runtime_error("undefined variable '" + name.toString() + "'.");
    }

    void Environment::assign(const Token& name, LiteralObject value){
        if(isVarExist(name.toString())){
            if(values[name.toString()].index() == value.index())
                values[name.toString()] = value;
            else
                throw std::runtime_error("error: implicit conversion");
        }
        else{
            throw std::runtime_error("Undefined variable '" + name.toString() + "'.");
        }
    }

    bool Environment::isVarExist(const std::string& name){
        if(values.find(name) != values.end()){
            return true;
        }
        if(enclosing != nullptr){
            if(enclosing->isVarExist(name)){
                return true;
            }
        }
        return false;
    }
} // Ne