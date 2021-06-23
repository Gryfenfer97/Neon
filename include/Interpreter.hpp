#pragma once
#include <Node.hpp>

namespace Ne{
    class Interpreter{
    public:
        LiteralObject evaluateBinary(ExprVariant expr);
        LiteralObject evaluateGrouping(ExprVariant expr);
        LiteralObject evaluateLiteral(ExprVariant expr);
        LiteralObject evaluateUnary(ExprVariant expr);
        std::string stringify(LiteralObject obj);
        LiteralObject evaluate(ExprVariant expr);

    // private:
    };
}