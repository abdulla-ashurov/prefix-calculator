#include "../include/calculator.hpp"
#include "../include/detail.hpp"

namespace calc
{
    double calculate(const std::string &expr)
    {
        tokens infix = parse(expr);
        tokens prefix = to_prefix(infix);

        return calculate_impl(prefix);
    }

    Token::Token(const std::string &value, const uint8_t type, const uint8_t possible_left_value)
        : value{value}, type{type}, possible_left_value{possible_left_value} {}

    tokens parse(const std::string &expr)
    {
        std::string operand;
        tokens infix;

        for (size_t i = 0; i < expr.length(); i++)
        {
            if (detail::is_number(expr[i]))
                operand.push_back(expr[i]);

            else
            {
                if (!operand.empty())
                {
                    infix.push_back(Token(
                        operand, 
                        detail::define_type(operand), 
                        detail::define_possible_left_value(operand)
                    ));
                    operand.clear();
                }

                infix.push_back(Token(
                    std::string(1, expr[i]), 
                    detail::define_type(operand), 
                    detail::define_possible_left_value(operand)
                ));
            }
        }

        return infix;
    }
}
