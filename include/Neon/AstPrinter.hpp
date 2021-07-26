#pragma once
#include <Neon/Node.hpp>
#include <type_traits>
#include <string>

namespace Ne{
    [[nodiscard]] std::string toString(const ExprVariant& expr);
    [[nodiscard]] std::string parenthesize(const std::string& name, const ExprVariant& arg1);
    [[nodiscard]] std::string parenthesize(const std::string& name, const ExprVariant& arg1, const ExprVariant& arg2);
}