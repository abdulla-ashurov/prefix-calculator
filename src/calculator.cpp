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
                    infix.push_back(Token(operand));
                    operand.clear();
                }
                infix.push_back(Token(expr[i]));
            }
        }

        return infix;
    }

    Token::Token(const std::string &value)
        : value{value}
    {
        type = define_type(value);
        possible_left_value = define_possible_left_value(type);
    }

    Token::Token(const char value)
        : Token(std::string(1, value)) {}
}
